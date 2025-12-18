#pragma once

#include "core.hpp"
#include <PxPhysicsAPI.h>
#include <string>

class RenderItem;

constexpr float GlobalGravity = -9.8f;
constexpr float RightLimit = 280.0f;
constexpr float LeftLimit = -280.0f;
constexpr float lateralForce = 1200.0f;
enum class PARTICLE_TYPE { NORMAL, FIREWORK, SPARK, FOG, RAIN };

enum INTEGRATETYPES {
    EULER,
    EULER_SEMI_IMPILICITO,
    VERLET
};

struct RIGID_BODY_PROPS {
    Vector3 _transform;
    Vector3 _velocity;
    Vector4 color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    double _mass;
    float _sizeX = 0.5f;
    float _sizeY = 0.5f;
    float _sizeZ = 0.5f;
    std::string _shapeType = "SPHERE";
    bool _isDynamic = true;
    int _materialType = 0;
    Vector3 _inertia = Vector3(0, 0, 0);
    double _lifeTime;
};

struct Obstacle {
    Vector3 position;
    Vector3 size;
    Vector4 color;
};

struct WindZone {
    Vector3 windVelocity;
    Vector3 areaCenter;
    Vector3 areaHalfSize;
    Vector4 color;
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
    std::string _shapeType = "SPHERE";

};

enum class SCENE_TYPE {
    MAIN_MENU,
    GAME,
    GAME_OVER,
    WIN,
    SCENE1,
    SCENE2,
    SCENE3,
    SCENE4,
    SCENE5,
    SCENE6,
    SCENE7
};