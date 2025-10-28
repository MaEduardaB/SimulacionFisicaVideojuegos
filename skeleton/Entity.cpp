#include "Entity.h"
#include "RenderUtils.hpp"


Entity::Entity(Vector3 pos, Vector4 color, float size) : _transform({ pos.x, pos.y, pos.z })
{
	_render = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), &_transform, color);

	RegisterRenderItem(_render);
}

Entity::~Entity()
{
	DeregisterRenderItem(_render);
}

void Entity::setColor(const Vector4 &color)
{
	_render->color = color;
}
