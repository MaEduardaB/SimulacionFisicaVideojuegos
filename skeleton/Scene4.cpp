#include "Scene4.h"
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

Scene4::Scene4() : _particleSystem(nullptr)
{
}

Scene4::~Scene4()
{
	delete _particleSystem;
}


void Scene4::update(double t)
{
	_particleSystem->update(t);
}

void Scene4::render() const
{

}

void Scene4::exit()
{
    delete _particleSystem;
    _particleSystem = nullptr;
}

void Scene4::enter()
{
    // Crear sistema de particulas con generador uniforme y gaussiano
    std::cout << "Creando ParticleSystem\n";

    _particleSystem = new ParticleSystem();

    std::mt19937 mt(std::random_device{}());
    //FogGen* fogGen = new FogGen(mt, Vector3(0, 0, 0), Vector3(0, 10, 0), 5.0, 1.0, 50, 5.0f);
    //_particleSystem->addGenerator(fogGen);
    FireworkGen* fg = new FireworkGen(mt, Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0, 1.0, 20);
    _particleSystem->addGenerator(fg);
    // GaussianGen* gg = new GaussianGen(mt, Vector3(5, 10, 0), Vector3(0, 0, 0), 2.0, 1.0, 10);
    // UniformGen* ug = new UniformGen(mt, Vector3(5, 5, 0), Vector3(1, 1, 0), 3.0, 0.8, 5);

    // _particleSystem->addGenerator(gg);
    // _particleSystem->addGenerator(ug);

    _particleSystem->createParticles(); 
}

void Scene4::keyPressed(unsigned char key)
{
    _particleSystem->createParticles();
}