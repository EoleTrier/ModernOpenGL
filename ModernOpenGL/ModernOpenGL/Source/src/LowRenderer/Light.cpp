#include "LowRenderer/Light.h"

Light::Light(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Vector3& viewPos, 
    const float materialShininess)
{
    diffuseColor = diffuse;
    ambientColor = ambient;
    specularColor = specular;
}



