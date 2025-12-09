#include "Scene6.h"
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

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene6::Scene6(Snippets::Camera* cam) : _gObjects()
{
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
    _force_registry->updateForces();

    for (int i = 0; i < _gObjects.size(); ++i) {
		_gObjects[i]->integrate(t);
	}

	//_gravity->updateForce(_gObjects[0]);

}

void Scene6::render() const
{

}


void Scene6::enter()
{
	_cam->setDir(physx::PxVec3(0, 0,-1.0f));
	_cam->setEye(physx::PxVec3(0, 50.0f, 180));

    _particleSystems = std::list<ParticleSystem*>();
    _force_registry = new ForceRegestry();

    PARTICLES prop;
			prop._velocity = Vector3(5,10,0);
			prop._aceleration =  Vector3(0,0,0);
			prop._transform = Vector3(0,20,0);
			prop._mass = 1.0;
			prop._damping = 0.99;
			prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;
            prop._p_type = PARTICLE_TYPE::SPARK;
            prop._size = 1.0f;
    prop._shapeType = "SPHERE";

    Particle* p1 = new Particle(prop);
	
    prop._velocity = Vector3(0,-10,5);

    prop._mass = 2.0;
    prop._transform = Vector3(0,30,0);
    Particle* p2 = new Particle(prop);

    SpringForceGenerator* spring = new SpringForceGenerator(p2, 1.0, 10.0);
    _force_registry->add(p1, spring);

    SpringForceGenerator* spring2 = new SpringForceGenerator(p1, 1.0, 10.0);
    _force_registry->add(p2, spring2);

    prop._shapeType = "SPHERE";
    prop._transform = Vector3(0,50,0);

    Particle* p3 = new Particle(prop);
    AnchoredSpringFG* anchoredSpring = new AnchoredSpringFG(1, 10, Vector3(0,70,0));
    _force_registry->add(p3, anchoredSpring);
   
   
    prop._velocity = Vector3(0,0,0);
    prop._shapeType = "BOX";
    prop._mass = 1.0;
    prop._transform = Vector3(0,10,0);
    prop._size = 1.0f;
    prop._damping = 0.98f;  
    Particle* p4 = new Particle(prop);

    RenderItem* water = new RenderItem(
        CreateShape(PxBoxGeometry(40, 20, 40), false),
        new PxTransform(PxVec3(0,-20,0)),
        Vector4(0.2f, 0.3f, 1.0f, 0.7f)
    );
    

    BouyancyForceGenerator* bouncy = new BouyancyForceGenerator(1, 1, 1000, 0);
    _force_registry->add(p4, bouncy);
    
	_gravity = new GravityForce();
    
    _force_registry->add(p4, _gravity);


    _gObjects.push_back(p1);
    _gObjects.push_back(p2);
    _gObjects.push_back(p3);
    _gObjects.push_back(p4);


    
    //_force_registry->add(p1, _gravity);
    // _force_registry->add(p2, _gravity);
}  

void Scene6::keyPressed(unsigned char key)
{
    if(key == 'G' || key == 'g') {
		SceneManager::instance().change_to_scene(SCENE_TYPE::MAIN_MENU);
	}
	else if (key == 'p' || key == 'P') {
        // for (auto* ps : _particleSystems) {
        //     if (ps) {
        //         ps->createParticles();
        //         ps->createExplosion(Vector3(0, 40, 0), 5000, 20, 1, 10);
        //     }
        // }
    }
}