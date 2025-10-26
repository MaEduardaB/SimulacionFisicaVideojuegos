#include "Entity.h"
#include "RenderUtils.hpp"


Entity::Entity(Vector3 pos) : _transform({ pos.x, pos.y, pos.z })
{
	_render = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5)), &_transform, Vector4(0, 0, 1, 1));

	RegisterRenderItem(_render);
}

Entity::~Entity()
{
	DeregisterRenderItem(_render);
}
