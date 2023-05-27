#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "Core/Maths/Vector2.h"
#include "Core/Maths/Matrix4x4.h"
#include "Resource.h"

class Shader : public Resource
{
public:
    unsigned int ID;
    Shader() {};
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const Vector2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const Vector3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const Vector4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat4(const std::string& name, const Matrix4x4& mat) const;
   
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif