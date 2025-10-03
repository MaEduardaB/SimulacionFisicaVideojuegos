#pragma once

#include <PxPhysicsAPI.h>
#include "core.hpp"

class RenderItem;

class Entity
{
public:
	Entity(Vector3 pos);
	//virtual void render() const = 0;
	virtual void integrate(double t) {};

protected:

	physx::PxTransform _transform;
	RenderItem* _render;
};

