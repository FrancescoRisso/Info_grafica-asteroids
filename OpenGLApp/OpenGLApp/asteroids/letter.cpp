#include "letter.hpp"


using namespace Asteroids;

Letter::Letter() {}


staticVariablesInitialize_cpp(Letter);
std::map<char, unsigned int> Letter::charToId;


void Letter::addCharacterTexture(char c, const char* path) {
	char buf[100];

	int id = addTexture(path);
	if(id != -1) Letter::charToId[c] = id;
}


void Letter::Init(glm::vec2 pos, float angle) {
	this->pos = glm::vec2(0);
	this->speed = glm::vec2(0);
	this->angle = 0;


	// clang-format off
	float tmpPoints[numTriangles_Letter * 3 * 2 * 2] = {
		(float) 0,			(float) 0,		0.0f,	1.0f,
		(float) 0,			(float) -1, 	0.0f,	0.0f,
		(float) 5/8,		(float) 0, 		1.0f,	1.0f,

		(float) 0,			(float) -1,		0.0f,	0.0f,
		(float) 5/8,		(float) 0,		1.0f,	1.0f,
		(float) 5/8,		(float) -1,		1.0f,	0.0f,
	};
	// clang-format on

	addCharacterTexture('0', "./resources/fonts/minecraft/0.png");
	addCharacterTexture('1', "./resources/fonts/minecraft/1.png");
	addCharacterTexture('2', "./resources/fonts/minecraft/2.png");
	addCharacterTexture('3', "./resources/fonts/minecraft/3.png");
	addCharacterTexture('4', "./resources/fonts/minecraft/4.png");
	addCharacterTexture('5', "./resources/fonts/minecraft/5.png");
	addCharacterTexture('6', "./resources/fonts/minecraft/6.png");
	addCharacterTexture('7', "./resources/fonts/minecraft/7.png");
	addCharacterTexture('8', "./resources/fonts/minecraft/8.png");
	addCharacterTexture('9', "./resources/fonts/minecraft/9.png");

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

	// addCharacterTexture('A', "./resources/fonts/minecraft/A_uppercase.png");
	// addCharacterTexture('B', "./resources/fonts/minecraft/B_uppercase.png");
	// addCharacterTexture('C', "./resources/fonts/minecraft/C_uppercase.png");
	// addCharacterTexture('D', "./resources/fonts/minecraft/D_uppercase.png");
	// addCharacterTexture('E', "./resources/fonts/minecraft/E_uppercase.png");
	// addCharacterTexture('F', "./resources/fonts/minecraft/F_uppercase.png");
	// addCharacterTexture('G', "./resources/fonts/minecraft/G_uppercase.png");
	// addCharacterTexture('H', "./resources/fonts/minecraft/H_uppercase.png");
	// addCharacterTexture('I', "./resources/fonts/minecraft/I_uppercase.png");
	// addCharacterTexture('J', "./resources/fonts/minecraft/J_uppercase.png");
	// addCharacterTexture('K', "./resources/fonts/minecraft/K_uppercase.png");
	// addCharacterTexture('L', "./resources/fonts/minecraft/L_uppercase.png");
	// addCharacterTexture('M', "./resources/fonts/minecraft/M_uppercase.png");
	// addCharacterTexture('N', "./resources/fonts/minecraft/N_uppercase.png");
	// addCharacterTexture('O', "./resources/fonts/minecraft/O_uppercase.png");
	// addCharacterTexture('P', "./resources/fonts/minecraft/P_uppercase.png");
	// addCharacterTexture('Q', "./resources/fonts/minecraft/Q_uppercase.png");
	// addCharacterTexture('R', "./resources/fonts/minecraft/R_uppercase.png");
	// addCharacterTexture('S', "./resources/fonts/minecraft/S_uppercase.png");
	// addCharacterTexture('T', "./resources/fonts/minecraft/T_uppercase.png");
	// addCharacterTexture('U', "./resources/fonts/minecraft/U_uppercase.png");
	// addCharacterTexture('V', "./resources/fonts/minecraft/V_uppercase.png");
	// addCharacterTexture('W', "./resources/fonts/minecraft/W_uppercase.png");
	// addCharacterTexture('X', "./resources/fonts/minecraft/X_uppercase.png");
	// addCharacterTexture('Y', "./resources/fonts/minecraft/Y_uppercase.png");
	// addCharacterTexture('Z', "./resources/fonts/minecraft/Z_uppercase.png");

	initGL(tmpPoints);
}


void Letter::setCharacter(char c) {
	useTexture(Letter::charToId[c]);
}
