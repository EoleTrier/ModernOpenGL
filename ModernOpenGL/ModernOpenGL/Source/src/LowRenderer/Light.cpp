#include "LowRenderer/Light.h"

Light::Light(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular)
{
    diffuseColor = diffuse;
    ambientColor = ambient;
    specularColor = specular;
}



