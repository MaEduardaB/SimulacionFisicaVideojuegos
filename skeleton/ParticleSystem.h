#pragma once
#include<list>

class Particle;
class ParticleGen;
class ParticleSystem
{
public:

	void update(double t);

protected:


private:

	std::list<Particle*> _particles;
	std::list<ParticleGen*> _generators;

};

