#pragma once

#include "LowRenderer/Light.h"

class PointLight : public Light
{
public:
    PointLight(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, int ID)
    {
        diffuseColor = diffuse;
        ambientColor = ambient;
        specularColor = specular;
        this->ID = ID;
    };
    void SetPointLight(Shader* shader, const Vector3& position, const float constant, const float linear, const float quadratic)
    {
        shader->setVec3("pointLights[" + std::to_string(ID) + "].position", position);
        shader->setVec3("pointLights[" + std::to_string(ID) + "].ambient", ambientColor);
        shader->setVec3("pointLights[" + std::to_string(ID) + "].diffuse", diffuseColor);
        shader->setVec3("pointLights[" + std::to_string(ID) + "].specular", specularColor);
        shader->setFloat("pointLights[" + std::to_string(ID) + "].constant", constant);
        shader->setFloat("pointLights[" + std::to_string(ID) + "].linear", linear);
        shader->setFloat("pointLights[" + std::to_string(ID) + "].quadratic", quadratic);
    }
private:
    int ID;

};