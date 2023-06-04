
#include "LowRenderer/Light/Spot.h"


SpotLight::SpotLight(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Vector3& position, const Vector3& direction, const float constant, const float linear,
    const float quadratic, const float cutOff, const float outerCutOff, int ID)
{
    diffuseColor = diffuse;
    ambientColor = ambient;
    specularColor = specular;
    this->position = position;
    this->direction = direction;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    this->cutOff = cutOff;
    this->outerCutOff = outerCutOff;
    this->ID = ID;

};
void SpotLight::SetSpotLight(Shader* shader)
{
    shader->setVec3("spotLights[" + std::to_string(ID) + "].position", position);
    shader->setVec3("spotLights[" + std::to_string(ID) + "].direction", direction);
    shader->setVec3("spotLights[" + std::to_string(ID) + "].ambient", ambientColor);
    shader->setVec3("spotLights[" + std::to_string(ID) + "].diffuse", diffuseColor);
    shader->setVec3("spotLights[" + std::to_string(ID) + "].specular", specularColor);
    shader->setFloat("spotLights[" + std::to_string(ID) + "].constant", constant);
    shader->setFloat("spotLights[" + std::to_string(ID) + "].linear", linear);
    shader->setFloat("spotLights[" + std::to_string(ID) + "].quadratic", quadratic);
    shader->setFloat("spotLights[" + std::to_string(ID) + "].cutOff", cos(ToRadians * cutOff));
    shader->setFloat("spotLights[" + std::to_string(ID) + "].outerCutOff", cos(ToRadians * outerCutOff));
}