#include "letter.hpp"


using namespace Asteroids;

Letter::Letter() : thisColor(0), basePos(0) {}


staticVariablesInitialize_cpp(Letter);
std::map<char, unsigned int> Letter::charToId;
std::map<char, unsigned char> Letter::letterWidth;


void Letter::addCharacterTexture(char c, const char* path, unsigned char width) {
	char buf[100];

	int id = addTexture(path);
	if(id != -1) {
		Letter::charToId[c] = id;
		letterWidth[c] = width;
	}
}


void Letter::Init(glm::vec2 pos, char letter, horizAligns horizontalAlignment, vertAligns verticalAlignment, glm::vec3 color, float height) {
	this->pos = scaleVectorReverse(pos);
	this->speed = glm::vec2(0);
	this->angle = 0;
	shiftAmount = 0;

	float top = 0.5;
	float bottom = -top;
	float left = 0.5 * letterAspectRatio;
	float right = -left;

	// clang-format off
	float tmpPoints[numTriangles_Letter * 3 * 2 * 2] = {
		right,		top,		0.0f,	1.0f,
		right,		bottom, 	0.0f,	0.0f,
		left,		top, 		1.0f,	1.0f,

		right,		bottom,		0.0f,	0.0f,
		left,		top,		1.0f,	1.0f,
		left,		bottom,		1.0f,	0.0f,
	};
	// clang-format on

	glm::vec2 delta = glm::vec2(0, height / 2);
	delta = scaleVectorReverse(delta);

	switch(verticalAlignment) {
		case alignTop: this->pos -= delta; break;
		case alignBottom: this->pos += delta; break;
	}

	switch(horizontalAlignment) {
		case alignRight: this->pos -= scaleVectorReverse(glm::vec2(letterAspectRatio * height / 2, 0)); break;
		case alignLeft: this->pos += scaleVectorReverse(glm::vec2(letterAspectRatio * height / 2, 0)); break;
	}

	basePos = this->pos;

	thisColor = color;
	scale = height;

	addCharacterTexture('0', "./resources/fonts/minecraft/0.png", 5);
	addCharacterTexture('1', "./resources/fonts/minecraft/1.png", 5);
	addCharacterTexture('2', "./resources/fonts/minecraft/2.png", 5);
	addCharacterTexture('3', "./resources/fonts/minecraft/3.png", 5);
	addCharacterTexture('4', "./resources/fonts/minecraft/4.png", 5);
	addCharacterTexture('5', "./resources/fonts/minecraft/5.png", 5);
	addCharacterTexture('6', "./resources/fonts/minecraft/6.png", 5);
	addCharacterTexture('7', "./resources/fonts/minecraft/7.png", 5);
	addCharacterTexture('8', "./resources/fonts/minecraft/8.png", 5);
	addCharacterTexture('9', "./resources/fonts/minecraft/9.png", 5);

	addCharacterTexture('a', "./resources/fonts/minecraft/a_lowercase.png", 5);
	addCharacterTexture('b', "./resources/fonts/minecraft/b_lowercase.png", 5);
	addCharacterTexture('c', "./resources/fonts/minecraft/c_lowercase.png", 5);
	addCharacterTexture('d', "./resources/fonts/minecraft/d_lowercase.png", 5);
	addCharacterTexture('e', "./resources/fonts/minecraft/e_lowercase.png", 5);
	addCharacterTexture('f', "./resources/fonts/minecraft/f_lowercase.png", 4);
	addCharacterTexture('g', "./resources/fonts/minecraft/g_lowercase.png", 5);
	addCharacterTexture('h', "./resources/fonts/minecraft/h_lowercase.png", 5);
	addCharacterTexture('i', "./resources/fonts/minecraft/i_lowercase.png", 1);
	addCharacterTexture('j', "./resources/fonts/minecraft/j_lowercase.png", 5);
	addCharacterTexture('k', "./resources/fonts/minecraft/k_lowercase.png", 5);
	addCharacterTexture('l', "./resources/fonts/minecraft/l_lowercase.png", 2);
	addCharacterTexture('m', "./resources/fonts/minecraft/m_lowercase.png", 5);
	addCharacterTexture('n', "./resources/fonts/minecraft/n_lowercase.png", 5);
	addCharacterTexture('o', "./resources/fonts/minecraft/o_lowercase.png", 5);
	addCharacterTexture('p', "./resources/fonts/minecraft/p_lowercase.png", 5);
	addCharacterTexture('q', "./resources/fonts/minecraft/q_lowercase.png", 5);
	addCharacterTexture('r', "./resources/fonts/minecraft/r_lowercase.png", 5);
	addCharacterTexture('s', "./resources/fonts/minecraft/s_lowercase.png", 5);
	addCharacterTexture('t', "./resources/fonts/minecraft/t_lowercase.png", 3);
	addCharacterTexture('u', "./resources/fonts/minecraft/u_lowercase.png", 5);
	addCharacterTexture('v', "./resources/fonts/minecraft/v_lowercase.png", 5);
	addCharacterTexture('w', "./resources/fonts/minecraft/w_lowercase.png", 5);
	addCharacterTexture('x', "./resources/fonts/minecraft/x_lowercase.png", 5);
	addCharacterTexture('y', "./resources/fonts/minecraft/y_lowercase.png", 5);
	addCharacterTexture('z', "./resources/fonts/minecraft/z_lowercase.png", 5);

	addCharacterTexture('A', "./resources/fonts/minecraft/A_uppercase.png", 5);
	addCharacterTexture('B', "./resources/fonts/minecraft/B_uppercase.png", 5);
	addCharacterTexture('C', "./resources/fonts/minecraft/C_uppercase.png", 5);
	addCharacterTexture('D', "./resources/fonts/minecraft/D_uppercase.png", 5);
	addCharacterTexture('E', "./resources/fonts/minecraft/E_uppercase.png", 5);
	addCharacterTexture('F', "./resources/fonts/minecraft/F_uppercase.png", 5);
	addCharacterTexture('G', "./resources/fonts/minecraft/G_uppercase.png", 5);
	addCharacterTexture('H', "./resources/fonts/minecraft/H_uppercase.png", 5);
	addCharacterTexture('I', "./resources/fonts/minecraft/I_uppercase.png", 5);
	addCharacterTexture('J', "./resources/fonts/minecraft/J_uppercase.png", 5);
	addCharacterTexture('K', "./resources/fonts/minecraft/K_uppercase.png", 5);
	addCharacterTexture('L', "./resources/fonts/minecraft/L_uppercase.png", 5);
	addCharacterTexture('M', "./resources/fonts/minecraft/M_uppercase.png", 5);
	addCharacterTexture('N', "./resources/fonts/minecraft/N_uppercase.png", 5);
	addCharacterTexture('O', "./resources/fonts/minecraft/O_uppercase.png", 5);
	addCharacterTexture('P', "./resources/fonts/minecraft/P_uppercase.png", 5);
	addCharacterTexture('Q', "./resources/fonts/minecraft/Q_uppercase.png", 5);
	addCharacterTexture('R', "./resources/fonts/minecraft/R_uppercase.png", 5);
	addCharacterTexture('S', "./resources/fonts/minecraft/S_uppercase.png", 5);
	addCharacterTexture('T', "./resources/fonts/minecraft/T_uppercase.png", 5);
	addCharacterTexture('U', "./resources/fonts/minecraft/U_uppercase.png", 5);
	addCharacterTexture('V', "./resources/fonts/minecraft/V_uppercase.png", 5);
	addCharacterTexture('W', "./resources/fonts/minecraft/W_uppercase.png", 5);
	addCharacterTexture('X', "./resources/fonts/minecraft/X_uppercase.png", 5);
	addCharacterTexture('Y', "./resources/fonts/minecraft/Y_uppercase.png", 5);
	addCharacterTexture('Z', "./resources/fonts/minecraft/Z_uppercase.png", 5);

	initGL(tmpPoints);

	setCharacter(letter);
}


void Letter::setCharacter(char c) {
	useTexture(Letter::charToId[c]);
	letter = c;
}

unsigned int Letter::getWidth() const {
	return (unsigned int) Letter::letterWidth[letter];
}


void Letter::shiftByPixel(float amount) {
	shiftAmount = amount;
	updateTransform();
}


void Letter::extraUpdateTransform() {
	pos = basePos + scaleVector(glm::vec2(shiftAmount * scale * letterAspectRatio / numPixelsHorizontal, 0));
}
