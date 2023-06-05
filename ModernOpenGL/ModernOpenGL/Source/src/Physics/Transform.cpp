#include "Physics/Transform.h"

Transform::Transform(const Matrix4x4& localModel)
{
    LocalModel = localModel;
}


void Transform::UpdateSelfAndChilds()
{
    LocalModel = Matrix4x4::TRS(Rotation, Position, Scaling);

    if (Parent)
        GlobalModel = Parent->GlobalModel * LocalModel;
    else
        GlobalModel = LocalModel;

    for (int i = 0; i < Childs.size(); i++)
    {
        Childs[i]->UpdateSelfAndChilds();
    }
}

void Transform::AddChild(Transform* const t)
{
    this->Childs.push_back(t);
    if (t->Parent)
        t->Parent->RemoveChild(t);
    t->Parent = this;
}

void Transform::RemoveChild(Transform* const t)
{
    std::erase(Childs, t);
}
