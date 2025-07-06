#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Shader {
public:
    unsigned int ID;

    // Loads vertex & fragment shaders from file paths
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
};
