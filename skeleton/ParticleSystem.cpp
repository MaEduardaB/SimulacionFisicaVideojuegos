#include "ParticleSystem.h"
#include "ParticleGen.h"
#include "Particle.h"

ParticleSystem::ParticleSystem() : _particles(), _generators()
{
}

void ParticleSystem::update(double t)
{
	for (auto it = _particles.begin(); it != _particles.end(); )
	{
		Particle* p = *it;
		if (p != nullptr) {
			p->integrate(t);

			if (p->getElim()) {
				it = _particles.erase(it);
				delete p;
			}
			else {
				++it;
			}
		}
	}
}

void ParticleSystem::cleanParticles()
{
	for (auto it = _generators.begin(); it != _generators.end(); ++it)
	{
		ParticleGen* gen = *it;                   
		if (gen != nullptr) {
			std::list<Particle*> newParticles = gen->generateP(); 
			_particles.insert(_particles.end(), newParticles.begin(), newParticles.end());
		}
	}
}

void ParticleSystem::generateParticles()
{
	for (auto it = _generators.begin(); it != _generators.end(); ++it)
	{
		ParticleGen* gen = *it;
		if (gen != nullptr) 
			gen->clearP();
		
	}
}
