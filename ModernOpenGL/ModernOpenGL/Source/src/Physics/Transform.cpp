#include "Physics/Transform.h"

Transform::Transform()
{
}

Transform::Transform(const Matrix4x4& localModel)
{
    this->localModel = localModel;
}


void Transform::UpdateSelfAndChilds()
{
    localModel = Matrix4x4::TRS(rotation, position, scaling);

    if (parent)
        globalModel = parent->globalModel * localModel;
    else
        globalModel = localModel;

    for (int i = 0; i < childs.size(); i++)
    {
        childs[i]->UpdateSelfAndChilds();
    }
}

void Transform::AddChild(Transform* const t)
{
    this->childs.push_back(t);
    if (t->parent)
        t->parent->RemoveChild(t);
    t->parent = this;
}

void Transform::RemoveChild(Transform* const t)
{
    std::erase(childs, t);
}
