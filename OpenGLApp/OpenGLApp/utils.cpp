#include "utils.hpp"

#include <iostream>
using namespace std;

float angleBetween(glm::vec2 a, glm::vec2 b, glm::vec2 origin) {
	glm::vec2 da = glm::normalize(scaleVectorReverse(a - origin));
	glm::vec2 db = glm::normalize(scaleVectorReverse(b - origin));

	float sina = -da.y;
	float cosa = da.x;
	float sinb = -db.y;
	float cosb = db.x;

	float sin = sina * cosb - cosa * sinb;
	float cos = cosa * cosb + sina * sinb;

	if(cos < 0) return glm::atan(sin / cos) + (float) glm::radians(180.0);
	return glm::atan(sin / cos);
}

float angleBetweenVerticalDir(glm::vec2 a) {
	return angleBetween(a, YaxisVersor, glm::vec2(0));
}

glm::vec2 scaleVector(glm::vec2 vector) {
	if(SCR_WIDTH > SCR_HEIGHT)
		vector.x *= (float) SCR_HEIGHT / (float) SCR_WIDTH;
	else
		vector.y *= (float) SCR_WIDTH / (float) SCR_HEIGHT;

	return vector;
}

glm::vec2 scaleVectorReverse(glm::vec2 vector) {
	if(SCR_WIDTH > SCR_HEIGHT)
		vector.x /= (float) SCR_HEIGHT / (float) SCR_WIDTH;
	else
		vector.y /= (float) SCR_WIDTH / (float) SCR_HEIGHT;

	return vector;
}

glm::vec2 mouse2graphicCoords(glm::vec2 mouseCoords, glm::vec2 screenSize) {
	glm::vec2 res;

	res.x = 2 * mouseCoords.x / screenSize.x - 1;
	res.y = 1 - 2 * mouseCoords.y / screenSize.y;

	return res;
}
