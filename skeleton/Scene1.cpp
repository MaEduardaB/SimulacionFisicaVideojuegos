#include "Scene1.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "ForceRegestry.h"
#include "Entity.h"
#include "GravityForce.h"
#include "SceneManager.h"
#include "Constants.h"

#include "RenderUtils.hpp"
#include "core.hpp"

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene1::Scene1(Snippets::Camera* cam) : _gObjects()
{
	display_text = "Scene 1: Press 'p' to create particles.";
	_cam = cam;
	_force_registry = nullptr;
	_gravity = nullptr;
}

Scene1::~Scene1()
{

	_gObjects.clear();
	delete _force_registry;
	_force_registry = nullptr;

	delete _gravity;
	_gravity = nullptr;
    _cam = nullptr;

	DeregisterAllRenderItem();

}

void Scene1::update(double t)
{
	for (int i = 0; i < _gObjects.size(); ++i) {
		_gravity->updateForce(_gObjects[i]);
		_gObjects[i]->integrate(t);
	}

}

void Scene1::render() const
{
}

void Scene1::exit()
{
	//for (auto e : _gObjects) {
	//	delete e;
	//}
	//_gObjects.clear();

	delete _force_registry;
	_force_registry = nullptr;

	delete _gravity;
	_gravity = nullptr;
	DeregisterAllRenderItem();
}

void Scene1::enter()
{
	_force_registry = new ForceRegestry();
	_gravity = new GravityForce();
	_cam->setDir(physx::PxVec3(-0.6f,-0.2f,-0.7f));
	_cam->setEye(physx::PxVec3(50.0f, 50.0f, 50.0f));
	//_cam->moveTo(physx::PxTransform(physx::PxVec3(0.0f, 5.0f, 20.0f)));
}

void Scene1::keyPressed(unsigned char key)
{
	if(key == 'G' || key == 'g') {
		SceneManager::instance().change_to_scene(SCENE_TYPE::MAIN_MENU);
	}
	else if (key == 'p' || key == 'P') {
		//std::cout << "Creadno\n";
		PARTICLES prop;
			prop._velocity = Vector3(5,10,0);
			prop._aceleration =  Vector3(0,0,0);
			prop._transform = Vector3(0,0,0);
			prop._mass = 1.0;
			prop._damping = 0.99;
			prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;

		Particle* part = new Particle(prop);
		_gObjects.push_back(part);

		_force_registry->add(part, _gravity	);
	}
}