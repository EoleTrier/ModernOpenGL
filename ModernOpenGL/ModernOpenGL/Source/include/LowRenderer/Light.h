#pragma once

#include "Core/Maths/Vector3.h"
#include "Core/Maths/Vector4.h"
#include "Ressources/Shader.h"

class Light
{
public:
	Light() {};
	Light(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Vector3& viewPos, const float materialShininess);
	
	Vector3 diffuseColor;
	Vector3 ambientColor;
	Vector3 specularColor;

};