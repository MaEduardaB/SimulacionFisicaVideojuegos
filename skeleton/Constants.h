#pragma once

#include "core.hpp"
#include <PxPhysicsAPI.h>

class RenderItem;

constexpr float GlobalGravity = -9.8f;

enum class PARTICLE_TYPE { NORMAL, FIREWORK, SPARK, FOG, RAIN };

enum INTEGRATETYPES {
    EULER,
    EULER_SEMI_IMPILICITO,
    VERLET
};

struct PARTICLES {
    Vector3 _transform;

    Vector3 _velocity;
    Vector3 _aceleration;

    INTEGRATETYPES _type;
    PARTICLE_TYPE _p_type;
    
    double _lifeTime;
    double _mass;
    double _damping;
    float _size = 0.5f;
};