#pragma once
#include "Core/Maths/Matrix4x4.h"
#include "Ressources/Texture.h"
#include "LowRenderer/Camera.h"
#include "Ressources/Shader.h"

class Model;

class Mesh : public Resource
{
public:
	Mesh();
	~Mesh();

	void SetAttributesAndInit(Model* const model, Shader* const shader, Texture* const texture);
	void Draw(Camera& cam, const Matrix4x4& localModel);

private:
	Model* mModel;
	Shader* mShader;
	Texture* mTexture;
};