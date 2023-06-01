#pragma once

#include "LowRenderer/Light.h"

class PointLight : public Light
{
public:
    int ID;

    void SetPointLight(Shader* shader, const Vector3& position, const float constant, const float linear, const float quadratic)
    {
        shader->setVec3("pointLights[ID].position", position);
        shader->setVec3("pointLights[ID].ambient", ambientColor);
        shader->setVec3("pointLights[ID].diffuse", diffuseColor);
        shader->setVec3("pointLights[ID].specular", specularColor);
        shader->setFloat("pointLights[ID].constant", constant);
        shader->setFloat("pointLights[ID].linear", linear);
        shader->setFloat("pointLights[ID].quadratic", quadratic);
    }
};