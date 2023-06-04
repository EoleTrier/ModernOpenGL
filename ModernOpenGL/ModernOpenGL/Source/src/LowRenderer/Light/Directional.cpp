
#include "LowRenderer/Light/Directional.h"


DirectionalLight::DirectionalLight(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Vector3& direction, int ID)
{
	diffuseColor = diffuse;
	ambientColor = ambient;
	specularColor = specular;
	this->direction = direction;
	this->ID = ID;
};
void DirectionalLight::SetDirectionalLight(Shader* shader)
{
	shader->setVec3("dirLight[" + std::to_string(ID) + "].direction", direction);
	shader->setVec3("dirLight[" + std::to_string(ID) + "].ambient", ambientColor);
	shader->setVec3("dirLight[" + std::to_string(ID) + "].diffuse", diffuseColor);
	shader->setVec3("dirLight[" + std::to_string(ID) + "].specular", specularColor);
}