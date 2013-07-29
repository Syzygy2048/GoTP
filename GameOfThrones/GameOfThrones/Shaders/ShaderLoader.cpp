#include "ShaderLoader.h"
#include <fstream>
#include <iostream>

ShaderLoader::ShaderLoader(void)
{
}


GLuint ShaderLoader::loadShaders(std::vector<std::string> shaderPaths)
{
	GLuint programID = glCreateProgram();

	//for error handling
	GLint result = GL_FALSE;
	int logLength;
	
	for(const std::string shaderPath : shaderPaths){
		GLuint shaderID;
		if(shaderPath.find("Fragment") != std::string::npos)
			shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		else if(shaderPath.find("TesselationControl") != std::string::npos)
			shaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
		else if(shaderPath.find("TesselationEval") != std::string::npos)
			shaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
		else
			shaderID = glCreateShader(GL_VERTEX_SHADER);
		std::string shaderCode;
		std::ifstream codeStream(shaderPath, std::ios::in);
		if(codeStream.is_open())
		{
			std::string line = "";
			while(getline(codeStream, line))
				shaderCode += "\n" + line;
			codeStream.close();
		}

		std::cerr << "compiling shader: " << shaderPath << std::endl; 
		char const * sourcePointer = shaderCode.c_str();
		glShaderSource(shaderID, 1, &sourcePointer , NULL);
		glCompileShader(shaderID);
 
		// Check Shader
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> shaderErrorMessage(logLength);			//got that from a tutorial... i guess it's just a lazy way to initialize an array that needs to be of a specific size because it's later filled by glGetShaderInfoLog
		glGetShaderInfoLog(shaderID, logLength, NULL, shaderErrorMessage.data());
		//for(char c : shaderErrorMessage)
		//	std::cerr << "	shader compile error: " << c << std::endl;
		
		glAttachShader(programID, shaderID);
	}
	glLinkProgram(programID);
	
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> programErrorMessage(std::max(logLength, int(1)) );
    glGetProgramInfoLog(programID, logLength, NULL, &programErrorMessage[0]);
//	for(char c : programErrorMessage)
	//	std::cerr << "	program creation error: " << c << std::endl;
	return programID;
}

ShaderLoader::~ShaderLoader(void)
{
}
