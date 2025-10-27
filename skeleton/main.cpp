#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"

#include <iostream>
#include <chrono>
#include <thread>

std::string display_text = "This is a test";

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;


std::vector<Scene*> _scenes;
int current_scene = 0;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	RegisterRenderItem(new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(0.0, 0.0, 0.0), Vector4(1, 1, 1, 1)));

	RegisterRenderItem(new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(0.0, 10.0, 0.0), Vector4(0, 1, 0, 1)));

	RegisterRenderItem(new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(10.0, 0.0, 0.0), Vector4(1, 0, 0, 1)));

	RegisterRenderItem(new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(0.0, 0.0, 10.0), Vector4(0, 0, 1, 1)));

	Scene1* scene = new Scene1();

	Scene2* scene2 = new Scene2();
	Scene3* scene3 = new Scene3();
	_scenes.push_back(scene);
	_scenes.push_back(scene2);
	_scenes.push_back(scene3);

	current_scene = 0;
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);

	_scenes[current_scene]->update(t);
	gScene->fetchResults(true);


	std::this_thread::sleep_for(std::chrono::microseconds(10));
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	gFoundation->release();

	DeregisterAllRenderItem();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'P':
	{
		//std::cout << "Creando\n";
		_scenes[current_scene]->create();
		break;
	}
	default:
		if (key >= '0' && key <= '9') //cuando estamos en el estado de dos escenas no cambiamos de escena
		{
			int scene_index = key - '0';
			if (scene_index < _scenes.size()) {
				std::cout << "Cambiando a escena " << scene_index << "\n";
				_scenes[current_scene]->exit();
				current_scene = scene_index;
				_scenes[current_scene]->enter();
			}
			
		}
			break;
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}