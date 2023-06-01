#pragma once

#include "LowRenderer/Light.h"

class DirectionalLight : public Light
{
public:
	int ID;

	void SetDirectionalLight(Shader* shader, const Vector3& direction)
	{
		shader->setVec3("dirLight[ID].direction", direction);
		shader->setVec3("dirLight[ID].ambient", ambientColor);
		shader->setVec3("dirLight[ID].diffuse", diffuseColor);
		shader->setVec3("dirLight[ID].specular", specularColor);
	}
};