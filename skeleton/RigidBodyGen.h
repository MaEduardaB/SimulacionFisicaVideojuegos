#pragma once
#include <random>
#include <list>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "Constants.h"

class RigidBodyGen
{
public:
    RigidBodyGen();
    RigidBodyGen(std::mt19937 mt,
                 Vector3 vel,
                 Vector3 pos,
                 double duration,
                 double prob_Gen,
                 int n_rigidBodies);

    virtual std::list<RIGID_BODY_PROPS> generateProps() = 0;
    virtual void clearRigidBodies() = 0;

    void setPosition(Vector3);
    const Vector3& getPosition() const;

    void setVelocity(Vector3);
    const Vector3& getVelocity() const;

    void setDuration(double);
    double getDuration() const;

    void setNRigidBodies(int);
    int getNRigidBodies() const;

protected:
    std::mt19937 _mt;
    Vector3 _vel;
    Vector3 _pos;
    double _dur;
    double _prob_Gen;
    int _n_rigidBodies;
};