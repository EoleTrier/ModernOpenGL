#pragma once

#include "LowRenderer/Light.h"

class DirectionalLight : Light
{
	void SetDirectionalLight(Shader* shader, const Vector3& direction)
	{
		shader->setVec3("dirLight.direction", direction);
		shader->setVec3("dirLight.ambient", ambientColor);
		shader->setVec3("dirLight.diffuse", diffuseColor);
		shader->setVec3("dirLight.specular", specularColor);
	}

};