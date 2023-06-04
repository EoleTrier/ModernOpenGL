#include "Physics/Transform.h"

void Transform::updateSelfAndChild()
{
    LocalModel = Matrix4x4::TRS(Rotation, Position, Scaling);
    if (Parent != nullptr)
        LocalModel = LocalModel * Parent->GlobalModel;

    for (int i = 0; i < Childs.size(); i++)
    {
        Childs[i]->updateSelfAndChild();
    }
}