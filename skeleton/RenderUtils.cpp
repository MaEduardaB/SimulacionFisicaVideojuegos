#define WIN32_LEAN_AND_MEAN   // evita conflictos de Windows.h
#include <Windows.h>

#include <gl/GL.h>      
#include <gl/GLU.h>
#ifndef GLuint
typedef unsigned int GLuint;
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <vector>
#include <filesystem>

#include "core.hpp"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"


using namespace physx;

GLuint LoadTexture(const std::string& filename)
{
	int width, height, channels;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	std::cout << "[DEBUG] Directorio actual: " << std::filesystem::current_path() << std::endl;
	if (!data)
	{
		std::cerr << "Error cargando textura: " << filename << std::endl;
		return 0;
	}

	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	std::cout << "Textura cargada: " << filename << " (" << width << "x" << height << ")\n";
	return texID;
}

extern void initPhysics(bool interactive);
extern void stepPhysics(bool interactive, double t);	
extern void cleanupPhysics(bool interactive);
extern void keyPress(unsigned char key, const PxTransform& camera);
extern PxPhysics* gPhysics;
extern PxMaterial* gMaterial;

std::vector<const RenderItem*> gRenderItems;

double PCFreq = 0.0;
__int64 CounterStart = 0;
__int64 CounterLast = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		return;

	PCFreq = double(li.QuadPart) /*/ 1000.0*/;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
	CounterLast = CounterStart;
}

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	double t = double(li.QuadPart - CounterLast) / PCFreq;
	CounterLast = li.QuadPart;
	return t;
}

namespace
{
	Camera*	sCamera;

void motionCallback(int x, int y)
{
	sCamera->handleMotion(x, y);
}

void keyboardCallback(unsigned char key, int x, int y)
{
	if(key==27)
		exit(0);

	if(!sCamera->handleKey(key, x, y))
		keyPress(key, sCamera->getTransform());
}

void mouseCallback(int button, int state, int x, int y)
{
	sCamera->handleMouse(button, state, x, y);
}

void idleCallback()
{
	glutPostRedisplay();
}

float stepTime = 0.0f;
//#define FIXED_STEP

void renderCallback()
{
	double t = GetCounter();
#ifdef FIXED_STEP
	if (t < (1.0f / 30.0f))
	{
		fprintf(stderr, "Time: %f\n", stepTime);
		stepTime += t;
	}
	else
		stepTime = 1.0f / 30.0f;

	if (stepTime >= (1.0f / 30.0f))
	{
		stepPhysics(true, stepTime);
		stepTime = 0.0f;
	}
#else
	stepPhysics(true, t);
#endif

	startRender(sCamera->getEye(), sCamera->getDir());

	//fprintf(stderr, "Num Render Items: %d\n", static_cast<int>(gRenderItems.size()));
	for (auto it = gRenderItems.begin(); it != gRenderItems.end(); ++it)
	{
		const RenderItem* obj = (*it);
		if (!obj->isVisible()) continue; 
		
		auto objTransform = obj->transform;
		if (!objTransform)
		{
			auto actor = obj->actor;
			if (actor)
			{
				renderShape(*obj->shape, actor->getGlobalPose(), obj->color, obj->textureID);

				continue;
			}
		}
		renderShape(*obj->shape, objTransform ? *objTransform : physx::PxTransform(PxIdentity), obj->color);
	}

	//PxScene* scene;
	//PxGetPhysics().getScenes(&scene, 1);
	//PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
	//if (nbActors)
	//{
	//	std::vector<PxRigidActor*> actors(nbActors);
	//	scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);
	//	renderActors(&actors[0], static_cast<PxU32>(actors.size()), true, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	//}

	finishRender();
}

void exitCallback(void)
{
	delete sCamera;
	cleanupPhysics(true);
}
}

void renderLoop()
{
	StartCounter();
	sCamera = new Camera(PxVec3(50.0f, 50.0f, 50.0f), PxVec3(-0.6f,-0.2f,-0.7f));

	setupDefaultWindow("Simulacion Fisica Videojuegos");
	setupDefaultRenderState();

	glutIdleFunc(idleCallback);
	glutDisplayFunc(renderCallback);
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(motionCallback);
	motionCallback(0,0);

	atexit(exitCallback);

	initPhysics(true);
	glutMainLoop();
}

void RegisterRenderItem(const RenderItem* _item)
{
	if (!_item) {
		std::cerr << "Error: Intento de registrar RenderItem nulo" << std::endl;
		return;
	}

	// Verificar que no esté ya registrado
	auto it = find(gRenderItems.begin(), gRenderItems.end(), _item);
	if (it != gRenderItems.end()) {
		std::cerr << "Warning: RenderItem ya está registrado" << std::endl;
		return;
	}

	gRenderItems.push_back(_item);
}

void DeregisterRenderItem(const RenderItem* _item)
{
	if (_item) {
		auto it = find(gRenderItems.begin(), gRenderItems.end(), _item);
		gRenderItems.erase(it);
	}
	
}



void DeregisterAllRenderItem()
{
	gRenderItems.clear();
}

double GetLastTime()
{
	double t = double(CounterLast - CounterStart) / PCFreq;
	return t;
}

Camera* GetCamera()
{
	return sCamera;
}

PxShape* CreateShape(const PxGeometry& geo, const PxMaterial* mat)
{
	if (mat == nullptr)
		mat = gMaterial; // Default material

	PxShape* shape = gPhysics->createShape(geo, *mat);
	return shape;
}

void DebugRenderItems()
{
	std::cout << "=== DEBUG RENDERITEMS ===" << std::endl;
	std::cout << "Total RenderItems: " << gRenderItems.size() << std::endl;

	for (size_t i = 0; i < gRenderItems.size(); ++i) {
		const RenderItem* item = gRenderItems[i];
		std::cout << "  Item " << i << " [" << item << "]: ";

		if (item->actor) {
			std::cout << "Actor: " << item->actor;
			try {
				PxTransform pose = item->actor->getGlobalPose();
				std::cout << " Pos: (" << pose.p.x << ", " << pose.p.y << ", " << pose.p.z << ")";
			}
			catch (...) {
				std::cout << " ERROR al obtener pose";
			}
		}
		else if (item->transform) {
			std::cout << "Transform directo";
		}
		else {
			std::cout << "Sin transform ni actor";
		}

		std::cout << std::endl;
	}

	std::cout << "=========================" << std::endl;
}