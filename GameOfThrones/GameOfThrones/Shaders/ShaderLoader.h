#ifndef _SHADER_LOADER_
#define _SHADER_LOADER_

#include <string>
#include <GL\glew.h>
#include <vector>

class ShaderLoader
{
public:
	ShaderLoader(void);
	~ShaderLoader(void);	

	static GLuint loadShaders(std::vector<std::string> shaderPaths);

private:

};

#endif