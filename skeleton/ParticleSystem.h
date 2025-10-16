#pragma once
#include<list>

class Particle;
class ParticleGen;
class ParticleSystem
{
public:
	ParticleSystem();
	void update(double t);

protected:

	void cleanParticles();
	void generateParticles();
	std::list<Particle*> _particles;
	std::list<ParticleGen*> _generators;

};

