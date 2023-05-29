#include "LowRenderer/Mesh.h"


Mesh::Mesh(const Model& model, const Shader& shader, const Texture& texture)
{
	*mModel = model;
	*mShader = shader;
	*mTexture = texture;
	Draw();
}

void Mesh::Draw()
{
    glGenVertexArrays(1, &mModel->VAO);

    glGenBuffers(1, &mModel->VBO);
    glBindVertexArray(mModel->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mModel->VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mModel->vertices.size(), mModel->vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureUV));
    glEnableVertexAttribArray(2);    
    
    glBindVertexArray(0);
}