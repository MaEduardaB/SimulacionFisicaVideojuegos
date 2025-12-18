#include "UniformRigidGen.h"
#include <cstdlib>

UniformRigidGen::UniformRigidGen(std::mt19937 mt,
                                 Vector3 vel,
                                 Vector3 pos,
                                 double duration,
                                 double prob_Gen,
                                 int n_rigidBodies)
    : RigidBodyGen(mt, vel, pos, duration, prob_Gen, n_rigidBodies)
{
}

std::list<RIGID_BODY_PROPS> UniformRigidGen::generateProps() {
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
        p._lifeTime = 10000.0;
        props.push_back(p);
    }
    return props;
}
