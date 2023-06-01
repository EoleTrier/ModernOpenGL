#pragma once

#include "LowRenderer/Light.h"
#include "LowRenderer/Camera.h"

class SpotLight : Light
{
    void SetSpotLight(Shader* shader, const Vector3& position, const Vector3& direction, const float constant, const float linear,
        const float quadratic, const float cutOff, const float outerCutOff)
    {
        shader->setVec3("spotLight.position", position);
        shader->setVec3("spotLight.direction", direction);
        shader->setVec3("spotLight.ambient", ambientColor);
        shader->setVec3("spotLight.diffuse", diffuseColor);
        shader->setVec3("spotLight.specular", specularColor);
        shader->setFloat("spotLight.constant", constant);
        shader->setFloat("spotLight.linear", linear);
        shader->setFloat("spotLight.quadratic", quadratic);
        shader->setFloat("spotLight.cutOff", cos(ToRadians * cutOff));
        shader->setFloat("spotLight.outerCutOff", cos(ToRadians * outerCutOff));
    }
};