#pragma once

#include <string>
#include <glad/glad.h>

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexSrc, const char* fragmentSrc);

	void use() const;

	// Utility functions to set uniforms
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};