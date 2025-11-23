#include "Scene6.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "UniformGen.h"
#include "Particle.h"
#include "ParticleGen.h"
#include "ForceRegestry.h"
#include "SpringForceGenerator.h"
#include "SceneManager.h"
#include "Constants.h"
#include "core.hpp"
#include "RenderUtils.hpp"

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene6::Scene6(Snippets::Camera* cam){
	display_text = "Scene 5: Press 'p' to create rain with explosions.";
    _cam = cam;
    _force_registry = nullptr;
    _particleSystems = std::list<ParticleSystem*>();
}

Scene6::~Scene6()
{
    for (auto* ps : _particleSystems)
        delete ps;

    _particleSystems.clear();

    delete _force_registry;
    _force_registry = nullptr;
}

void Scene6::exit()
{
    for (auto* ps : _particleSystems)
        delete ps;

    _particleSystems.clear();

    delete _force_registry;
    _force_registry = nullptr;
}

void Scene6::update(double t)
{
    for (auto pS : _particleSystems)
    {
        pS->update(t);
    }
}

void Scene6::render() const
{

}


void Scene6::enter()
{
	_cam->setDir(physx::PxVec3(-0.6f,-0.2f,-0.7f));
	_cam->setEye(physx::PxVec3(50.0f, 50.0f, 50.0f));

    _particleSystems = std::list<ParticleSystem*>();
    _force_registry = new ForceRegestry();

    Particle*
    // Crear sistema de particulas con generador uniforme y gaussiano
    //std::cout << "Creando ParticleSystem\n";

    _particleSystems.push_back(new ParticleSystem());

    
}  

void Scene6::keyPressed(unsigned char key)
{
    if(key == 'G' || key == 'g') {
		SceneManager::instance().change_to_scene(SCENE_TYPE::MAIN_MENU);
	}
	else if (key == 'p' || key == 'P') {
        for (auto* ps : _particleSystems) {
            if (ps) {
                ps->createParticles();
                ps->createExplosion(Vector3(0, 40, 0), 5000, 20, 1, 10);
            }
        }
    }
}