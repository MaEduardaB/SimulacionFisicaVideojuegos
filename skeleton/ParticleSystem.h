#pragma once
#include<list>

class Particle;
class ParticleGen;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void addGenerator(ParticleGen* gen);
	void addForce();
	void cleanParticles();
	void clearForces();
	void addParticle(Particle* p);
	const std::list<Particle*>& getParticles() const;
protected:
	std::list<Particle*> _particles; // lista de particulas del sistema
	std::list<ParticleGen*> _generators; // lista de generadores de particulas

	// lista de fuerzas que se aplican a todas las particulas de ese sistema
	std::list<Particle*> _newParticles;

};

