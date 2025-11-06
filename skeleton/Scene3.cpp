#include "Scene3.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "UniformGen.h"
#include "ParticleGen.h"
#include "FireworkGen.h"
#include "ForceRegestry.h"
#include "RainGen.h"
#include "FogGen.h"
#include "WindForce.h"
#include "TorbellinoForce.h"

#include "core.hpp"
#include "RenderUtils.hpp"

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene3::Scene3(Snippets::Camera* cam){
    _particleSystems = std::list<ParticleSystem*>();
    _force_registry = new ForceRegestry();
    _cam = cam;
}

Scene3::~Scene3()
{
    for (auto* ps : _particleSystems)
        delete ps;

    _particleSystems.clear();

    delete _force_registry;
    _force_registry = nullptr;
}

void Scene3::exit()
{
    for (auto* ps : _particleSystems)
        delete ps;

    _particleSystems.clear();

    delete _force_registry;
    _force_registry = nullptr;
}

void Scene3::update(double t)
{
    for (auto pS : _particleSystems)
    {
        pS->update(t);
    }
}

void Scene3::render() const
{

}


void Scene3::enter()
{
    // Crear sistema de particulas con generador uniforme y gaussiano
    std::cout << "Creando ParticleSystem\n";

    _particleSystems.push_back(new ParticleSystem());

    std::mt19937 mt(std::random_device{}());
    // FogGen* fogGen = new FogGen(mt, Vector3(0, 0, 0), Vector3(0, 10, 0), 5.0, 1.0, 500, 15.0f);
    // _particleSystems.front()->addGenerator(fogGen);
    
    // FireworkGen* fg = new FireworkGen(mt, Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0, 1.0, 20);
    // _particleSystem->addGenerator(fg);

    //_particleSystem->createWind(Vector3(20.0f, 0.0f, 0.0f), Vector3(0.0f, 00.0f, 0.0f), Vector3(140.0f, 140.0f, 140.0f), 0.8, 0.8);
    
    //_particleSystem->createTorbellino(Vector3(0, 0, 0), 50.0f, 10.0f);

    RainGen* rg = new RainGen(mt, Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0, 1.0, 30);
    
    _particleSystems.front()->addGenerator(rg);

    // GaussianGen* gg = new GaussianGen(mt, Vector3(5, 10, 0), Vector3(0, 0, 0), 2.0, 1.0, 10);
    // UniformGen* ug = new UniformGen(mt, Vector3(5, 5, 0), Vector3(1, 1, 0), 3.0, 0.8, 5);

    // _particleSystem->addGenerator(gg);
    // _particleSystem->addGenerator(ug);

    _particleSystems.front()->createParticles();
    _particleSystems.front()->createGravity();


    //RegisterRenderItem(new RenderItem(CreateShape(PxSphereGeometry(20)), new PxTransform(0.0, 20.0, 10.0), Vector4(0, 0, 1, 0.2)));
}

void Scene3::keyPressed(unsigned char key)
{
    _particleSystems.front()->createParticles();
    //_particleSystem->createExplosion(Vector3(0,40,0), 5000,20,1,10);
}