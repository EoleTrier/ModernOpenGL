#pragma once
#include "Core/Maths/Matrix4x4.h"

class Object;

class Transform
{
public:
    Transform();
    Transform(const Matrix4x4& localModel);
    Object* object;
    Transform* parent;
    std::vector<Transform*> childs;
	Matrix4x4 localModel;
	Matrix4x4 globalModel;
    Vector3 position;
    Vector3 rotation;
    Vector3 scaling;

    void UpdateSelfAndChilds();
    void AddChild(Transform* const t);
    void RemoveChild(Transform* const t);
};