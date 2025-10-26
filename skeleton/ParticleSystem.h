#pragma once
#include<list>

class Particle;
class ParticleGen;
class ParticleSystem
{
public:
	ParticleSystem();
	void update(double t);

	void addForce();

protected:
	void clearForces();
	void cleanParticles();
	void generateParticles();
	std::list<Particle*> _particles; // lista de particulas del sistema
	std::list<ParticleGen*> _generators; // lista de generadores de particulas

	// lista de fuerzas que se aplican a todas las particulas de ese sistema

};

