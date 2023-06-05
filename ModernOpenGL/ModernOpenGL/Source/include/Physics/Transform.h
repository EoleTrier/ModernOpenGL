#pragma once
#include "Core/Maths/Matrix4x4.h"

class Object;

class Transform
{
public:
    Transform() {};
    Transform(const Matrix4x4& localModel);
    Object* object;
    Transform* Parent;
    std::vector<Transform*> Childs;
	Matrix4x4 LocalModel;
	Matrix4x4 GlobalModel;
    Vector3 Position;
    Vector3 Rotation;
    Vector3 Scaling;

    void UpdateSelfAndChilds();
    void AddChild(Transform* const t);
    void RemoveChild(Transform* const t);
};