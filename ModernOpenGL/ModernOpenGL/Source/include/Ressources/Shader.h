#pragma once

#include <string>
#include "Core/Maths/Vector2.h"
#include "Core/Maths/Matrix4x4.h"
#include "Resource.h"

class Shader : public Resource
{
public:
    Shader();
    void SetVertexAndFragmentShader(const char* vertexPath, const char* fragmentPath);
    void SetViewPos(const Vector3& viewPos);

    void Use();
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, const Vector2& value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, const Vector3& value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, const Vector4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat4(const std::string& name, const Matrix4x4& mat) const;
   
private:
    unsigned int mID;
    void CheckCompileErrors(unsigned int shader, std::string type);
};

