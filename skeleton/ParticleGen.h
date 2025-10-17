#pragma once
#include <random>

#include <PxPhysicsAPI.h>
#include "core.hpp"

#include<list>

class Particle;

class ParticleGen
{
public:
	ParticleGen();
	ParticleGen(std::mt19937 mt,
				Vector3 vel,
				Vector3 pos,
				double duration,
				double prob_Gen,
				int n_particles);

	virtual std::list<Particle*> generateP() = 0;
	virtual void clearP() = 0;

	void setPosition(Vector3);
	const Vector3& getPosition() const;

	void setVelocity(Vector3);
	const Vector3& getVelocity() const;

	void setDuration(double);
	double getDuration() const;

	void setNParticles(int);
	int getNParticles() const;

protected:
	std::mt19937 _mt;
	Vector3 _vel;
	Vector3 _pos;
	double _dur;
	double _prob_Gen;
	int _n_particles;
};

