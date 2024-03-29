#pragma once

#include "LowRenderer/Light.h"

class PointLight : public Light
{
public:
    int id;
    Vector3 position;
    float constant;
    float linear;
    float quadratic;

    PointLight(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Vector3& position, const float constant, const float linear, const float quadratic, int id);
    void SetPointLight(Shader* shader);
   
};