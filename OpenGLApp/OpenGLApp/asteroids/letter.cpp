#include "letter.hpp"


using namespace Asteroids;

Letter::Letter() {}


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


void Letter::Init(glm::vec2 pos, float angle) {
	this->pos = glm::vec2(0);
	this->speed = glm::vec2(0);
	this->angle = 0;


	// clang-format off
	float tmpPoints[numTriangles_Letter * 3 * 2 * 2] = {
		(float) 0,			(float) 0,		0.0f,	1.0f,
		(float) 0,			(float) -1, 	0.0f,	0.0f,
		(float) 5/10,		(float) 0, 		1.0f,	1.0f,

		(float) 0,			(float) -1,		0.0f,	0.0f,
		(float) 5/10,		(float) 0,		1.0f,	1.0f,
		(float) 5/10,		(float) -1,		1.0f,	0.0f,
	};
	// clang-format on

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

	// addCharacterTexture('a', "./resources/fonts/minecraft/a_lowercase.png");
	// addCharacterTexture('b', "./resources/fonts/minecraft/b_lowercase.png");
	// addCharacterTexture('c', "./resources/fonts/minecraft/c_lowercase.png");
	// addCharacterTexture('d', "./resources/fonts/minecraft/d_lowercase.png");
	// addCharacterTexture('e', "./resources/fonts/minecraft/e_lowercase.png");
	// addCharacterTexture('f', "./resources/fonts/minecraft/f_lowercase.png");
	// addCharacterTexture('g', "./resources/fonts/minecraft/g_lowercase.png");
	// addCharacterTexture('h', "./resources/fonts/minecraft/h_lowercase.png");
	// addCharacterTexture('i', "./resources/fonts/minecraft/i_lowercase.png");
	// addCharacterTexture('j', "./resources/fonts/minecraft/j_lowercase.png");
	// addCharacterTexture('k', "./resources/fonts/minecraft/k_lowercase.png");
	// addCharacterTexture('l', "./resources/fonts/minecraft/l_lowercase.png");
	// addCharacterTexture('m', "./resources/fonts/minecraft/m_lowercase.png");
	// addCharacterTexture('n', "./resources/fonts/minecraft/n_lowercase.png");
	// addCharacterTexture('o', "./resources/fonts/minecraft/o_lowercase.png");
	// addCharacterTexture('p', "./resources/fonts/minecraft/p_lowercase.png");
	// addCharacterTexture('q', "./resources/fonts/minecraft/q_lowercase.png");
	// addCharacterTexture('r', "./resources/fonts/minecraft/r_lowercase.png");
	// addCharacterTexture('s', "./resources/fonts/minecraft/s_lowercase.png");
	// addCharacterTexture('t', "./resources/fonts/minecraft/t_lowercase.png");
	// addCharacterTexture('u', "./resources/fonts/minecraft/u_lowercase.png");
	// addCharacterTexture('v', "./resources/fonts/minecraft/v_lowercase.png");
	// addCharacterTexture('w', "./resources/fonts/minecraft/w_lowercase.png");
	// addCharacterTexture('x', "./resources/fonts/minecraft/x_lowercase.png");
	// addCharacterTexture('y', "./resources/fonts/minecraft/y_lowercase.png");
	// addCharacterTexture('z', "./resources/fonts/minecraft/z_lowercase.png");

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
}


void Letter::setCharacter(char c) {
	useTexture(Letter::charToId[c]);
}
