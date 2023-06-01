#pragma once

#include "LowRenderer/Light.h"

class PointLight : Light
{
    void SetPointLight(Shader* shader, const Vector3& position, const float constant, const float linear, const float quadratic)
    {
        shader->setVec3("pointLights[3].position", position);
        shader->setVec3("pointLights[3].ambient", ambientColor);
        shader->setVec3("pointLights[3].diffuse", diffuseColor);
        shader->setVec3("pointLights[3].specular", specularColor);
        shader->setFloat("pointLights[3].constant", constant);
        shader->setFloat("pointLights[3].linear", linear);
        shader->setFloat("pointLights[3].quadratic", quadratic);
    }
};