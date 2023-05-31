#pragma once

#include "Core/Maths/Vector4.h"

class Light
{
public:
	Light() {};

	Vector4 diffuseColor;
	Vector4 ambientColor;
	Vector4 specularColor;
};