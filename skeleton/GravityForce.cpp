#include "GravityForce.h"
#include "Constants.h"
#include "Particle.h"

GravityForce::GravityForce(){
    _force = Vector3(0.0f, _gravity, 0.0f);
}

void GravityForce::updateForce(Particle *p)
{      
    if(p)
        p->addForce(calculateForce(p));   
}

Vector3 GravityForce::calculateForce(Particle *p)
{
    return _force * static_cast<float>(p->getMass());
}
