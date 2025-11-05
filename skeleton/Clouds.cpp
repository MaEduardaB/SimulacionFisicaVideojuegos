#include "Clouds.h"
#include "RenderUtils.hpp"

Clouds::Clouds(Vector3 pos, Vector4 _color, float size) : _pos(pos)
{
    RenderItem* central = new RenderItem(
        CreateShape(physx::PxSphereGeometry(size)),
        new physx::PxTransform(pos),
        _color);
    RegisterRenderItem(central);
    _items.push_back(central);

    RenderItem* der = new RenderItem(
        CreateShape(physx::PxSphereGeometry(size * 0.7f)),
        new physx::PxTransform(pos + Vector3(10, 0, 0)),
        _color);
    RegisterRenderItem(der);
    _items.push_back(der);

    RenderItem* izq = new RenderItem(
        CreateShape(physx::PxSphereGeometry(size * 0.7f)),
        new physx::PxTransform(pos + Vector3(-10, 0, 0)),
        _color);
    RegisterRenderItem(izq);
    _items.push_back(izq);
}

Clouds::~Clouds()
{
    for (auto* item : _items)
        DeregisterRenderItem(item);
}

void Clouds::updatePosition()
{
    if (_items.empty()) return;

    delete _items[0]->transform;
    _items[0]->transform = new physx::PxTransform(physx::PxVec3(_pos.x, _pos.y, _pos.z));

    if (_items.size() > 1) {
        delete _items[1]->transform;
        _items[1]->transform = new physx::PxTransform(physx::PxVec3(_pos.x + 10, _pos.y, _pos.z));
    }

    if (_items.size() > 2) {
        delete _items[2]->transform;
        _items[2]->transform = new physx::PxTransform(physx::PxVec3(_pos.x - 10, _pos.y, _pos.z));
    }
}
