#include "BouyancyForceGenerator.h"
#include "Particle.h"

BouyancyForceGenerator::BouyancyForceGenerator(float h, float v, float d, float posWater):
	_height(h), _volume(v), _liquid_density(d), _posWater(posWater)
{	
}

void BouyancyForceGenerator::updateForce(Particle* p)
{
	if(p)
		p->addForce(calculateForce(p));
}

Vector3 BouyancyForceGenerator::calculateForce(Particle* p)
{
	if (!p) return Vector3(0,0,0);

	float h = p->getTransform().p.y;
	float h0 = _posWater;

	Vector3 force(0,0,0);
	float immersed = 0;
	if(h-h0 > _height * 0.5f){
		immersed = 0.0f;
	}else if( h0 -h > _height * 0.5f){
		immersed = 1.0f;
	}else {
		immersed = (h0 - h) / _height + 0.5f;
	}

	if (immersed < 0.0f) immersed = 0.0f;
    if (immersed > 1.0f) immersed = 1.0f;

	force = Vector3(0 , _liquid_density * _volume * immersed * 9.8, 0);
	return force;
}
