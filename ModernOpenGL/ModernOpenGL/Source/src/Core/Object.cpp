#include "Core/Object.h"

Object::Object()
{
	tranform = Transform(Matrix4x4::Identity());

	tranform.scaling = 1;
	tranform.object = this;
}

Object::Object(const Transform& t)
{
	tranform = t;

	tranform.scaling = 1;
	tranform.object = this;
}