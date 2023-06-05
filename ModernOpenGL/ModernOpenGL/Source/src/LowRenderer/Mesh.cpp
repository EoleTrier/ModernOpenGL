#include "LowRenderer/Mesh.h"
#include "Ressources/Model.h"

Mesh::Mesh(Model* const model, Shader* const shader, Texture* const texture)
{
	mModel = model;
	mShader = shader;
	mTexture = texture;
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


    mModel->mesh = this;
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &mModel->VAO);
    glDeleteBuffers(1, &mModel->VBO);
}

void Mesh::Draw(Camera& cam, const Matrix4x4& localModel)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture->ID);

    mShader->use();

    Matrix4x4 model = localModel;
    Matrix4x4 view = cam.GetViewMatrix();
    Matrix4x4 projection = Matrix4x4::PerspectiveProjection(cam.Zoom * ToRadians, 800.f / 600.f, 0.1f, 1000.f);

    mShader->setMat4("model", model);
    mShader->setMat4("view", view);
    mShader->setMat4("projection", projection);

    glBindVertexArray(mModel->VAO);
    glDrawArrays(GL_TRIANGLES, 0, mModel->vertices.size());
    
}
