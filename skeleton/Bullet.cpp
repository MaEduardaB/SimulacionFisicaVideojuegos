#include "Bullet.h"

Bullet::Bullet(Vector3 pos, Vector3 vel, Vector3 ace, double mass) : Particle(pos, vel, ace, INTEGRATETYPES::EULER)
{
}

Bullet::~Bullet()
{
	Particle::~Particle();
}
