#pragma once

#include "Core/Maths/Vector3.h"
#include "Core/Maths/Vector4.h"
#include "Ressources/Shader.h"

class Light
{
public:
	Light() {};
	
	Vector3 diffuseColor;
	Vector3 ambientColor;
	Vector3 specularColor;
};