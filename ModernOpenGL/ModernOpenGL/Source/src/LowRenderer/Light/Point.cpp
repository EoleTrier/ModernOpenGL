
#include "LowRenderer/Light/Point.h"

PointLight::PointLight(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Vector3& position, const float constant, const float linear, const float quadratic, int ID)
{
    diffuseColor = diffuse;
    ambientColor = ambient;
    specularColor = specular;
    this->position = position;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    this->ID = ID;
}

void PointLight::SetPointLight(Shader* shader)
{
    shader->setVec3("pointLights[" + std::to_string(ID) + "].position", position);
    shader->setVec3("pointLights[" + std::to_string(ID) + "].ambient", ambientColor);
    shader->setVec3("pointLights[" + std::to_string(ID) + "].diffuse", diffuseColor);
    shader->setVec3("pointLights[" + std::to_string(ID) + "].specular", specularColor);
    shader->setFloat("pointLights[" + std::to_string(ID) + "].constant", constant);
    shader->setFloat("pointLights[" + std::to_string(ID) + "].linear", linear);
    shader->setFloat("pointLights[" + std::to_string(ID) + "].quadratic", quadratic);
}