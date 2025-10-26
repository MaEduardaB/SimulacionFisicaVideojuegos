#include "Scene3.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "UniformGen.h"


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

    _particleSystem = new ParticleSystem();
}

void Scene3::create()
{

}