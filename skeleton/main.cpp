#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
#include "StartScene.h"
#include "GameOverScene.h"
#include "WinScene.h"
#include "SceneManager.h"
#include "GameScene.h"

#include <iostream>
#include <chrono>
#include <thread>

std::string display_text = "porra";

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

Camera* _cam;

void update_display_text(const std::string& text)
{
	display_text = text;
}

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
	_cam = GetCamera();
	// RegisterRenderItem(new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(0.0, 0.0, 0.0), Vector4(1, 1, 1, 1)));

	// RegisterRenderItem(new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(0.0, 10.0, 0.0), Vector4(0, 1, 0, 1)));

	// RegisterRenderItem(new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(10.0, 0.0, 0.0), Vector4(1, 0, 0, 1)));

	// RegisterRenderItem(new RenderItem(CreateShape(PxSphereGeometry(1)), new PxTransform(0.0, 0.0, 10.0), Vector4(0, 0, 1, 1)));

	SceneManager& sm = SceneManager::instance();
	sm.add_scene(new StartScene());
	sm.add_scene(new GameScene(_cam));
	sm.add_scene(new GameOverScene());
	sm.add_scene(new WinScene(_cam));
	sm.add_scene(new Scene1(_cam));
	sm.add_scene(new Scene2(_cam));
	sm.add_scene(new Scene3(_cam));
	sm.add_scene(new Scene4(_cam));
	sm.add_scene(new Scene5(_cam));
	sm.add_scene(new Scene6(_cam));
	sm.change_to_scene(SCENE_TYPE::MAIN_MENU);
	update_display_text(SceneManager::instance().get_display_text());
}



// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);

	SceneManager::instance().update(t);
	gScene->fetchResults(true);
	
	update_display_text(SceneManager::instance().get_display_text());


	std::this_thread::sleep_for(std::chrono::microseconds(10));
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gScene->release();
	gDispatcher->release();
	gPhysics->release();

	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();			   
	gFoundation->release();

	SceneManager::instance().clear_scenes();
	DeregisterAllRenderItem();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	SceneManager::instance().key_input(key);
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