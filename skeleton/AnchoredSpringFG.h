#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringFG :
    public SpringForceGenerator
{
public:
    AnchoredSpringFG(double k, double resting_length, const Vector3& _anchorPos);
    ~AnchoredSpringFG();
    
    void updateForce(Particle* p) override;
    Vector3 calculateForce(Particle* p) override;
    inline void setK(double k) { _k = k; };
};

