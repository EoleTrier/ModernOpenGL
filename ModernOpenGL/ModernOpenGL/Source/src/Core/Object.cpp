#include "Core/Object.h"

Object::Object()
{
	tranform = Transform(Matrix4x4::identity());

	tranform.Scaling = 1;
	tranform.object = this;
}

Object::Object(const Transform& t)
{
	tranform = t;

	tranform.Scaling = 1;
	tranform.object = this;
}