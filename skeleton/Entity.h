#pragma once

#include <PxPhysicsAPI.h>
#include "core.hpp"

class RenderItem;

class Entity
{
public:
	Entity(Vector3 pos, Vector4 _color, float size = 0.5f);
	~Entity();
	//virtual void render() const = 0;
	virtual void integrate(double t) {};
	void setColor(const Vector4& color);
	physx::PxTransform getTransform() const { return _transform; }
	void setTransform(physx::PxTransform _n) { _transform = _n; }
protected:
	physx::PxTransform _transform;
	RenderItem* _render;
};

