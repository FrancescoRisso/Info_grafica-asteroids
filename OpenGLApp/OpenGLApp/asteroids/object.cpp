#include "object.hpp"

using namespace Asteroids;

Object::Object() : pos(0), speed(0), transform(0) {}

void Object::updateTransform() {
	transform = glm::mat4((float) 1);
	glm::vec2 scale = scaleVector(glm::vec2(1));

	transform = glm::scale(transform, glm::vec3(scale, 1));

	transform = glm::translate(transform, glm::vec3(pos / scale, 0));
	transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
}

void Object::Move() {
	pos += deltaTime * speed;

	if(!canExitTheScreen()) limitMovementToScreen();
	updateTransform();
}

void Object::limitMovementToScreen() {
	glm::vec2 scaledRadius(radius());

	scaledRadius = scaleVector(scaledRadius);

	if(pos.x + scaledRadius.x > 1) pos.x = 1 - scaledRadius.x;
	if(pos.x - scaledRadius.x < -1) pos.x = scaledRadius.x - 1;
	if(pos.y + scaledRadius.y > 1) pos.y = 1 - scaledRadius.y;
	if(pos.y - scaledRadius.y < -1) pos.y = scaledRadius.y - 1;
}

bool Object::isOutOfScreen() {
	glm::vec2 tmpVector(0);

	tmpVector.x = pos.x + radius();
	tmpVector.y = pos.y + radius();
	tmpVector = scaleVector(tmpVector);
	if(tmpVector.x < -1 || tmpVector.y < -1) return true;

	tmpVector.x = pos.x - radius();
	tmpVector.y = pos.y - radius();
	tmpVector = scaleVector(tmpVector);
	if(tmpVector.x > 1 || tmpVector.y > 1) return true;

	return false;
}


glm::vec2 Object::findRadiusTowards(glm::vec2 p) {
	return radius() * scaleVector(glm::normalize(scaleVectorReverse(p - pos)));
}


float Object::findDistanceFrom(glm::vec2 p) {
	glm::vec2 radiusTow = findRadiusTowards(p);
	glm::vec2 delta = scaleVectorReverse(pos + radiusTow - p);
	glm::vec2 deltaWithoutRadius = pos - p;

	if(glm::all(glm::isnan(delta))) return -1;

	if(glm::length(deltaWithoutRadius) < glm::length(radiusTow)) return -1;

	return glm::length(delta);
}


bool Object::collidesWith(Object* o) {
	glm::vec2 vecTowardsOther = findRadiusTowards(o->pos);
	float dist = o->findDistanceFrom(pos + vecTowardsOther);
	return dist <= 0;
}


void Object::addTexture(const char* filePath) {
	unsigned int texture;

	if(textureIsPresent(filePath)) return;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);  // tell stb_image.h to flip loaded texture's on the y-axis.

	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if(data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;

	stbi_image_free(data);

	getShader().setInt("texture", 0);

	addTextureID(texture, filePath);
}


void Object::Draw() const {
	getShader().use();
	getShader().setMat4("model", transform);

	if(getTextures().size() != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, chosenTexture);
	} else
		getShader().setVec3("objectColor", color());

	glBindVertexArray(getVAO());
	glDrawArrays(GL_TRIANGLES, 0, 3 * numTriangles());
}

void Object::initGL(float points[]) {
	bool hasTextures = getTextures().size() != 0;
	int numPoints = 3 * numTriangles();
	int valuesPerPoint = hasTextures ? 4 : 2;

	unsigned int VAO, VBO;

	if(getTextures().size() > 0) chosenTexture = getTextures()[rand() % getTextures().size()];

	if(!shaderIsSet()) {
		switch(shaderChoice()) {
			case shader_monochromatic: setShader(Shader("./resources/shaders/shader.vs", "./resources/shaders/shader.fs")); break;
			case shader_withTexture: setShader(Shader("./resources/shaders/texture.vs", "./resources/shaders/texture.fs")); break;
		}

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		setVAO(VAO);
		setVBO(VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numPoints * valuesPerPoint, points, GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, valuesPerPoint * sizeof(float), (void*) 0);
		glEnableVertexAttribArray(0);

		if(hasTextures) {
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
	}

	updateTransform();
}


void Object::useSameTextureAs(Object* other) {
	if(getVAO() != other->getVAO()) return;

	chosenTexture = other->chosenTexture;
}
