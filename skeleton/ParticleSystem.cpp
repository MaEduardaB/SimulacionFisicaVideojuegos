#include "ParticleSystem.h"
#include "ParticleGen.h"
#include "Particle.h"

ParticleSystem::ParticleSystem() : _particles(), _generators()
{
}

ParticleSystem::~ParticleSystem()
{
	for (auto p : _particles)
		delete p;
	_particles.clear();
}

void ParticleSystem::update(double t)
{
	for (auto it = _particles.begin(); it != _particles.end(); )
	{
		Particle* p = *it;
		if (p != nullptr) {
			p->integrate(t);

			if (p->getElim()) {
				p->triggerDeath(*this);

				it = _particles.erase(it);
				delete p;
			}
			else {
				++it;
			}
		}
	}


}

void ParticleSystem::addGenerator(ParticleGen* gen)
{
	if (gen)
		_generators.push_back(gen);
}

void ParticleSystem::addForce()
{
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

void ParticleSystem::clearForces()
{
}

void ParticleSystem::addParticle(Particle* p)
{
    if (p)
        _particles.push_back(p);
}

const std::list<Particle*>& ParticleSystem::getParticles() const
{
	return _particles;
}