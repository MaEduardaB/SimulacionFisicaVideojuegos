#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"

class RenderItem;
class Clouds {
public:
    Clouds(Vector3 pos, Vector4 _color, float size);
    ~Clouds();

    void move(const Vector3& delta) { _pos += delta; updatePosition(); }
    Vector3 getPos() const { return _pos; }

    void setPos(const Vector3& _n) { _pos = _n; };
private:
    void updatePosition();

    Vector3 _pos;
    std::vector<RenderItem*> _items;
};
