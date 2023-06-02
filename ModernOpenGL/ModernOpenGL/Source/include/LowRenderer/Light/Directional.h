#pragma once

#include "LowRenderer/Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, int ID)
	{
		diffuseColor = diffuse;
		ambientColor = ambient;
		specularColor = specular;
		this->ID = ID;
	};
	void SetDirectionalLight(Shader* shader, const Vector3& direction)
	{
		shader->setVec3("dirLight[" + std::to_string(ID) + "].direction", direction);
		shader->setVec3("dirLight[" + std::to_string(ID) + "].ambient", ambientColor);
		shader->setVec3("dirLight[" + std::to_string(ID) + "].diffuse", diffuseColor);
		shader->setVec3("dirLight[" + std::to_string(ID) + "].specular", specularColor);
	}
private:
	int ID;

};