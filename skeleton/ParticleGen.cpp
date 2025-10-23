#include "ParticleGen.h"
#include "Constants.h"
#include "Particle.h"

ParticleGen::ParticleGen()
	: _mt(), _vel(), _pos(), _dur(0.0), _prob_Gen(0.0), _n_particles(1)
{
}

ParticleGen::ParticleGen(std::mt19937 mt,
						 Vector3 vel,
						 Vector3 pos,
						 double duration,
						 double prob_Gen,
						 int n_particles)
	: _mt(mt), _vel(vel), _pos(pos), _dur(duration), _prob_Gen(prob_Gen), _n_particles(n_particles)
{
}



std::list<Particle *> ParticleGen::generateP()
{
	std::list<Particle*> p;
    // para n particulas, prob Gen
	
	int n = 1;

	for (int i = 0; i < n; ++i) {
		PARTICLES prop;
		prop._velocity = Vector3();
		prop._aceleration = Vector3();
		prop._transform = Vector3();
		prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;

		Particle* par = new Particle(prop);
		p.push_back(par);
	}

	// pos = pos + _d(_mt)*distPos
	// vel = vel + _d(_mt)*distVel
	// dur = dur + _d(_mt)*distdur
	// clona PModel y asigna pos, vel, dur


	_n_particles = n;
    
    return p;
}

void ParticleGen::setPosition(Vector3 pos)
{
	_pos = pos;
}

const Vector3& ParticleGen::getPosition() const
{
	return _pos;
}


void ParticleGen::setDuration(double dur)
{
	_dur = dur;
}

double ParticleGen::getDuration() const
{
	return _dur;
}


void ParticleGen::setNParticles(int num)
{
	_n_particles = num;
}

int ParticleGen::getNParticles() const
{
	return _n_particles;
}
