#pragma once

#include "core.hpp"
#include <PxPhysicsAPI.h>

class RenderItem;

constexpr float GlobalGravity = -9.8f;

enum INTEGRATETYPES {
    EULER,
    EULER_SEMI_IMPILICITO,
    VERLET
};

struct PARTICLES {

    Vector3 _velocity;
    Vector3 _aceleration;

    Vector3 _transform;

    INTEGRATETYPES _type;

    double _lifeTIme;
    double _mass;
    double _damping;
};