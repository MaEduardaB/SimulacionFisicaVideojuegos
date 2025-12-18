#include "WindLineGen.h"
#include "Constants.h"
#include "Particle.h"
#include "ParticleSystem.h"

WindLineGen::WindLineGen()
    : ParticleGen(), _u(0, 1), _start(Vector3(0, 0, 0)), _end(Vector3(0, 0, 0))
{
}

WindLineGen::WindLineGen(std::mt19937 mt, Vector3 start, Vector3 end, Vector3 windVelocity, double prob_Gen, int n_particles)
    : ParticleGen(mt, windVelocity, Vector3(0, 0, 0), 0.0, prob_Gen, n_particles), _start(start), _end(end), _u(0, 1)
{
    float length = (_end - _start).magnitude();
    float speed = windVelocity.magnitude();
    if (speed > 0) {
        _dur = length / speed * 0.7f;
    } else {
        _dur = 2.0;
    }
}

std::list<Particle*> WindLineGen::generateP()
{
    std::list<Particle*> particles;

    if (_u(_mt) > _prob_Gen)
        return particles;

    Vector3 direction = _end - _start;
    float length = direction.normalize();

    for (int i = 0; i < _n_particles; ++i)
    {
        float t = _u(_mt);
        Vector3 pos = _start + direction * (t * length);

        PARTICLES prop;
        prop._transform = pos;
        prop._velocity = _vel; // wind velocity
        prop._aceleration = Vector3(0.0f, 0.0f, 0.0f);
        prop._mass = 1.0f;
        prop._damping = 0.99f;
        prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;
        prop._p_type = PARTICLE_TYPE::NORMAL;
        prop._size = 5.0f;

        Particle* p = new Particle(prop);
        p->setTime(_dur);

        particles.push_back(p);
    }

    return particles;
}