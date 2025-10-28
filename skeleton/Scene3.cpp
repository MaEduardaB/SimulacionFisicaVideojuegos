#include "Scene3.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "UniformGen.h"
#include "ParticleGen.h"
#include "FireworkGen.h"
#include "FogGen.h"


#include "core.hpp"
#include "RenderUtils.hpp"

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene3::Scene3() : _particleSystem(nullptr)
{
}

Scene3::~Scene3()
{
	delete _particleSystem;
}

void Scene3::update(double t)
{
	_particleSystem->update(t);
}

void Scene3::render() const
{

}

void Scene3::exit()
{
    delete _particleSystem;
    _particleSystem = nullptr;
}

void Scene3::enter()
{
    // Crear sistema de particulas con generador uniforme y gaussiano
    std::cout << "Creando ParticleSystem\n";

    _particleSystem = new ParticleSystem();

    std::mt19937 mt(std::random_device{}());
    FogGen* fogGen = new FogGen(mt, Vector3(0, 0, 0), Vector3(0, 10, 0), 5.0, 1.0, 50, 5.0f);
    _particleSystem->addGenerator(fogGen);
    // FireworkGen* fg = new FireworkGen(mt, Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0, 1.0, 20);
    // _particleSystem->addGenerator(fg);
    // GaussianGen* gg = new GaussianGen(mt, Vector3(5, 10, 0), Vector3(0, 0, 0), 2.0, 1.0, 10);
    // UniformGen* ug = new UniformGen(mt, Vector3(5, 5, 0), Vector3(1, 1, 0), 3.0, 0.8, 5);

    // _particleSystem->addGenerator(gg);
    // _particleSystem->addGenerator(ug);

    _particleSystem->cleanParticles(); 
}

void Scene3::create()
{
    _particleSystem->cleanParticles();
}