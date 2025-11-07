#include "Bullet.h"
#include <iostream>

Bullet::Bullet(Vector3 pos, Vector3 dir, double massReal, double velReal, double velSim)
    : Particle({
        pos,
        dir * velSim,
        Vector3(0, 0, 0),
        INTEGRATETYPES::EULER_SEMI_IMPILICITO,
        PARTICLE_TYPE::NORMAL,
        massReal * (velReal * velReal) / (velSim * velSim),
        5.0f,
        0.99f
        })
{
    _mass = massReal * (velReal * velReal) / (velSim * velSim);
    _massReal = massReal;
    std::cout << "masa real = " << _massReal << " masa sim = " << _mass << "\n";
}
