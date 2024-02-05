#ifndef _OBJECT_STATIC_VARIABLES_DEF_H
#define _OBJECT_STATIC_VARIABLES_DEF_H


// Insert this in the .cpp file, to give an initialization to all static variables
#define staticVariablesInitialize_cpp(className)      \
	unsigned int className::VAO;                      \
	unsigned int className::VBO;                      \
	Shader className::shader;                         \
	std::vector<unsigned int> className::textures;    \
	std::vector<const char*> className::textureFiles; \
	bool className::shaderSet;                        \
	bool className::VaoVboSet


// Insert this in the .hpp file, to define all static variables and the respective methods
#define staticVariablesAndFunctionDefinitions_hpp(className) \
	staticVAO_VBO(className);                                \
	staticShader(className);                                 \
	staticTextures(className)


#define staticVAO_VBO(className)             \
	static unsigned int VAO;                 \
	static unsigned int VBO;                 \
	static bool VaoVboSet;                   \
                                             \
	bool VaoVboAreSet() const override {     \
		return className::VaoVboSet;         \
	}                                        \
                                             \
	unsigned int getVAO() const override {   \
		return className::VAO;               \
	}                                        \
                                             \
	void setVAO(unsigned int VAO) override { \
		className::VAO = VAO;                \
		className::VaoVboSet = true;         \
	}                                        \
                                             \
	unsigned int getVBO() const override {   \
		return className::VBO;               \
	}                                        \
                                             \
	void setVBO(unsigned int VBO) override { \
		className::VBO = VBO;                \
		className::VaoVboSet = true;         \
	}


#define staticShader(className)         \
	static Shader shader;               \
	static bool shaderSet;              \
	bool shaderIsSet() const override { \
		return className::shaderSet;    \
	}                                   \
                                        \
	Shader getShader() const override { \
		return className::shader;       \
	}                                   \
                                        \
	void setShader(Shader s) override { \
		className::shader = s;          \
		className::shaderSet = true;    \
	}


#define staticTextures(className)                                       \
	static std::vector<unsigned int> textures;                          \
	static std::vector<const char*> textureFiles;                       \
                                                                        \
	std::vector<unsigned int> getTextures() const override {            \
		return className::textures;                                     \
	}                                                                   \
                                                                        \
	void addTextureID(unsigned int id, const char* filePath) override { \
		className::textures.push_back(id);                              \
		className::textureFiles.push_back(filePath);                    \
	}                                                                   \
                                                                        \
	bool textureIsPresent(const char* filePath) const override {        \
		for(int i = 0; i < className::textureFiles.size(); i++)         \
			if(className::textureFiles[i] == filePath) return true;     \
		return false;                                                   \
	}


#endif
