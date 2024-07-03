#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setUniform(const std::string& name, bool value1);
	void setUniform(const std::string& name, int value1);
	void setUniform(const std::string& name, float value1);
	void setUniform(const std::string& name, float value1, float value2);
	void setUniform(const std::string& name, float value1, float value2, float value3);
};