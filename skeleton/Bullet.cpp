#include "Bullet.h"

#include <PxPhysicsAPI.h>
#include <iostream>
#include <cmath>


Bullet::Bullet(Vector3 pos, Vector3 dir, double massReal, double velReal, double velSim, Vector3 gravedad) : 
    Particle(pos, dir* velSim, gravedad, INTEGRATETYPES::EULER_SEMI_IMPILICITO)
{
	_massReal = massReal;

	_mass = massReal * (velReal * velReal) / (velSim * velSim);


	std::cout << "Masa real: " << _massReal << " | Masa simulada: " << _mass << "\n";
}

Bullet::~Bullet()
{
	Particle::~Particle();
}

void Bullet::integrate(double t)
{
    physx::PxTransform lastTransform = _transform;

    // Fuerza = masa * gravedad
    Vector3 fuerza = _aceleration * _mass;
    Vector3 aceleracionReal = fuerza / _mass;

    switch (_type) {
    case EULER:
        _transform.p = _transform.p + t * _velocity;
        _velocity += t * aceleracionReal;
        break;
    case EULER_SEMI_IMPILICITO:
        _velocity += t * aceleracionReal;
        _transform.p = _transform.p + t * _velocity;
        break;
    case VERLET:
        if (_transform_ant == _transform) {
            _transform.p = _transform.p + t * _velocity;
            _velocity += t * aceleracionReal;
        }
        else {
            _transform.p = 2 * _transform.p - _transform_ant.p + pow(t, 2) * aceleracionReal;
        }
        break;
    }

    damp(t);
    _transform_ant = lastTransform;
}
