#pragma once

#include "LowRenderer/Light.h"
#include "LowRenderer/Camera.h"

class SpotLight : public Light
{
public:
    int id;
    Vector3 position;
    Vector3 direction;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;

    SpotLight(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Vector3& position, const Vector3& direction, const float constant, const float linear,
        const float quadratic, const float cutOff, const float outerCutOff, int id);
    void SetSpotLight(Shader* shader);
};