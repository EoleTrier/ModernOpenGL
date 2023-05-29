#pragma once
#include "Core/Maths/Matrix4x4.h"
#include "Ressources/Model.h"
#include "Ressources/Texture.h"

class Mesh : Resource
{
private:
	Mesh(const Model& model, const Shader& shader, const Texture& texture);
	Model* mModel;
	Shader* mShader;
	Texture* mTexture;
	void Draw();

};