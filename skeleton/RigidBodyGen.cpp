#include "RigidBodyGen.h"
#include "RenderUtils.hpp"
#include "Constants.h"

// variables globales de PhysX (definidas en main.cpp)
extern physx::PxScene* gScene;
extern physx::PxPhysics* gPhysics;
extern physx::PxMaterial* gMaterial; 

RigidBodyGen::RigidBodyGen()
	: _mt(), _vel(), _pos(), _dur(0.0), _prob_Gen(0.0), _n_rigidBodies(1)
{
}

RigidBodyGen::RigidBodyGen(std::mt19937 mt,
						 Vector3 vel,
						 Vector3 pos,
						 double duration,
						 double prob_Gen,
						 int n_particles)
	: _mt(mt), _vel(vel), _pos(pos), _dur(duration), _prob_Gen(prob_Gen), _n_rigidBodies(n_particles)
{
}



std::list<RIGID_BODY_PROPS> RigidBodyGen::generateProps()
{
	std::list<RIGID_BODY_PROPS> props;
    for (int i = 0; i < _n_rigidBodies; ++i) {
        RIGID_BODY_PROPS p;
        p._transform = _pos + Vector3((rand() % 10 - 5) * 1.0f, 0, (rand() % 10 - 5) * 1.0f);
        p._velocity = _vel + Vector3((rand() % 20 - 10) * 1.0f, (rand() % 20 - 10) * 1.0f, (rand() % 20 - 10) * 1.0f);
        p._mass = 1.0 + (rand() % 5) * 0.5;
        
        p._sizeX = 0.5f + (rand() % 5) * 0.1f; 
        p._shapeType = (rand() % 2 == 0) ? "SPHERE" : "BOX";
        p._isDynamic = true;
        p._materialType = rand() % 3;  


        p._inertia = Vector3(0, 0, 0);  
        props.push_back(p);
    }
    return props;
}

void RigidBodyGen::setPosition(Vector3 pos)
{
	_pos = pos;
}

const Vector3& RigidBodyGen::getPosition() const
{
	return _pos;
}


void RigidBodyGen::setDuration(double dur)
{
	_dur = dur;
}

double RigidBodyGen::getDuration() const
{
	return _dur;
}


void RigidBodyGen::setNRigidBodies(int num)
{
	_n_rigidBodies = num;
}

int RigidBodyGen::getNRigidBodies() const
{
	return _n_rigidBodies;
}
