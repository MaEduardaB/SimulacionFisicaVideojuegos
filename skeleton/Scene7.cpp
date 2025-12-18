#include "Scene7.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "UniformGen.h"
#include "Particle.h"
#include "ParticleGen.h"
#include "ForceRegestry.h"
#include "GravityForce.h"
#include "SpringForceGenerator.h"
#include "BouyancyForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "SceneManager.h"
#include "Constants.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include "RigidBodySystem.h"
#include "RigidBodyGen.h"
#include "UniformRigidGen.h"
#include "core.hpp" 
#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene7::Scene7(Snippets::Camera* cam) : _cam(cam), _rigidBodySystem(nullptr)
{
	display_text = "Scene 7: Press 'p' to create rigidBodies.";
}

Scene7::~Scene7()
{
    delete _rigidBodySystem;
    _rigidBodySystem = nullptr;
}

void Scene7::exit()
{
    // delete _rigidBodySystem;
    // _rigidBodySystem = nullptr;

    // _particleSystems.clear();
    DeregisterAllRenderItem();
}

void Scene7::update(double t)
{
    if (_rigidBodySystem) {
        _rigidBodySystem->update(t);
    }
}

void Scene7::render() const
{

}


void Scene7::enter()
{
	_cam->setDir(physx::PxVec3(0, 0,-1.0f));
	_cam->setEye(physx::PxVec3(0, 50.0f, 180));

    _rigidBodySystem = new RigidBodySystem();
    gScene->setGravity(physx::PxVec3(0.0f, 0.0f, 0.0f));

    // Suelo
    RIGID_BODY_PROPS groundProps;
    groundProps._transform = Vector3(0, -10, 0);
    groundProps._shapeType = "BOX";
    groundProps._sizeX = 50.0f;
    groundProps._sizeY = 1.0f;
    groundProps._sizeZ = 50.0f;
    groundProps._isDynamic = false;
    _rigidBodySystem->createRigidBody(groundProps);

    std::mt19937 mt(0);
    UniformRigidGen* gen = new UniformRigidGen(mt, Vector3(0, 0, 0), Vector3(0, 40, 0), 0, 1.0, 10);
    _rigidBodySystem->addGenerator(gen);
}  


void Scene7::keyPressed(unsigned char key)
{
    if(key == 'G' || key == 'g') {
		SceneManager::instance().change_to_scene(SCENE_TYPE::MAIN_MENU);
	}
	else if (key == 'p' || key == 'P') {
        _rigidBodySystem->createRigidBodies();
    }
}