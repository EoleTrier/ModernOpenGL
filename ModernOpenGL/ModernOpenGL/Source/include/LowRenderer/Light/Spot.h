#pragma once

#include "LowRenderer/Light.h"
#include "LowRenderer/Camera.h"

class SpotLight : public Light
{
public:
    int ID;

    void SetSpotLight(Shader* shader, const Vector3& position, const Vector3& direction, const float constant, const float linear,
        const float quadratic, const float cutOff, const float outerCutOff)
    {
        shader->setVec3("spotLights[0].position", position);
        shader->setVec3("spotLights[0].direction", direction);
        shader->setVec3("spotLights[0].ambient", ambientColor);
        shader->setVec3("spotLights[0].diffuse", diffuseColor);
        shader->setVec3("spotLights[0].specular", specularColor);
        shader->setFloat("spotLights[0].constant", constant);
        shader->setFloat("spotLights[0].linear", linear);
        shader->setFloat("spotLights[0].quadratic", quadratic);
        shader->setFloat("spotLights[0].cutOff", cos(ToRadians * cutOff));
        shader->setFloat("spotLights[0].outerCutOff", cos(ToRadians * outerCutOff));
    }
};