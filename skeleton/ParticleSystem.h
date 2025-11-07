#pragma once
#include <list>
#include <memory>
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"

class Particle;
class ParticleGen;
class ForceRegestry;
class GravityForce;
class WindForce;
class WindForceM;
class TorbellinoForce;
class ExplosionsForce;

class ParticleSystem
{
public:
    ParticleSystem();
    ~ParticleSystem();

    void update(double t);
    void addGenerator(ParticleGen* gen);
    void createParticles();
    void addParticle(Particle* p, bool applyGravity = true);
    const std::list<std::unique_ptr<Particle>>& getParticles() const;

    void createGravity();

    void createWind(const Vector3& windVelocity,
                    const Vector3& areaCenter,
                    const Vector3& areaHalfSize,
                    float k1 = 1.0f,
                    float k2 = 0.0f);

    void createWindM(const Vector3& windVelocity,
                     const Vector3& areaCenter,
                     const Vector3& areaHalfSize,
                     float airDensity = 1.225f,
                     float area = 80.0f,
                     float dragCoeff = 0.5f,
                     const Vector3& normal = Vector3(0,0,1));

    void createTorbellino(const Vector3& center, float radio, float intensidad);
    void createExplosion(const Vector3& center, float K, float radius,
                         float decaimento, float expansionVel = 0.0f);

    void updateExplosions(float dt);

protected:
    void registerAllForces(Particle* p);
    void registerAllForcesList(const std::list<Particle*>& plist);

    std::list<std::unique_ptr<Particle>> _particles;
    std::list<ParticleGen*> _generators;

    std::unique_ptr<GravityForce> _gravityForce;

    std::vector<std::unique_ptr<WindForce>> _windForces;
    std::vector<std::unique_ptr<WindForceM>> _windMForces;

    std::unique_ptr<TorbellinoForce> _torbellinoForce;
    std::list<std::unique_ptr<ExplosionsForce>> _explosions;

    ForceRegestry* _force_registry;
};
