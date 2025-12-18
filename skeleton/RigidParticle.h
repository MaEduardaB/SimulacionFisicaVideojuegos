#pragma once
#include "core.hpp"
#include <PxPhysicsAPI.h>
#include "Constants.h"
class RenderItem;
class RigidParticle {
public:
    RigidParticle(const RIGID_BODY_PROPS& props, physx::PxMaterial* mat = nullptr);
    ~RigidParticle();

    void integrate(double t);
    void addForce(const Vector3& force);
    void addTorque(const Vector3& torque);

    Vector3 getPosition() const;
    Vector3 getVelocity() const;
    physx::PxRigidActor* getRigidBody() const { return _rb; }
    bool isDynamic() const;
    double getMass() const { return _mass; }
    double getLifeTime() const { return _lifeTime; }
    bool isAlive() const { return _lifeTime > 0; }
    float getSize() const { return _size; }
    const std::string& getShapeType() const { return _shapeType; }

private:
    physx::PxRigidActor* _rb;
    RenderItem* _renderItem;

    double _mass;
    double _lifeTime;
    float _size;
    std::string _shapeType;
};