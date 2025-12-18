#include "Scene5.h"
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
#include "SceneManager.h"
#include "Constants.h"
#include "core.hpp"
#include "RenderUtils.hpp"

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene5::Scene5(Snippets::Camera* cam){
	display_text = "Scene 5: Press 'p' to create rain with explosions.";
    _cam = cam;
    _force_registry = nullptr;
}

Scene5::~Scene5()
{
    if(_particleSystems.size() > 0)
        for (auto* ps : _particleSystems)
            delete ps;

    _particleSystems.clear();

    if(_force_registry){
        delete _force_registry;
        _force_registry = nullptr;
    }
   
}

void Scene5::exit()
{
    for (auto* ps : _particleSystems)
        delete ps;

    _particleSystems.clear();

    delete _force_registry;
    _force_registry = nullptr;
}

void Scene5::update(double t)
{
    for (auto pS : _particleSystems)
    {
        pS->update(t);
    }
}

void Scene5::render() const
{

}


void Scene5::enter()
{
	_cam->setDir(physx::PxVec3(-0.6f,-0.2f,-0.7f));
	_cam->setEye(physx::PxVec3(50.0f, 50.0f, 50.0f));

    _particleSystems = std::list<ParticleSystem*>();
    _force_registry = new ForceRegestry();

    // Crear sistema de particulas con generador uniforme y gaussiano
    //std::cout << "Creando ParticleSystem\n";

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

void Scene5::keyPressed(unsigned char key)
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