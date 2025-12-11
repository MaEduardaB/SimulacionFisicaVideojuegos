#pragma once
#include "RigidBodyGen.h"

class UniformRigidGen : public RigidBodyGen
{
public:
    UniformRigidGen(std::mt19937 mt, Vector3 vel, Vector3 pos, double duration, double prob_Gen, int n_rigidBodies);

    std::list<RIGID_BODY_PROPS> generateProps() override;
    void clearRigidBodies() override;
};