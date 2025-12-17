#ifndef __CORE_HPP__
#define __CORE_HPP__

#include "../common/Common/Print.h"
#include "../common/Common/PVD.h"
#include "../common/Utils/Utils.h"

#include "Render/Render.h"
#include "Render/Camera.h"
#include <PxPhysicsAPI.h>
#include <vector>

using namespace Snippets;

typedef physx::PxVec3 Vector3;
typedef physx::PxVec4 Vector4;

extern physx::PxPhysics* gPhysics;
extern physx::PxScene* gScene;
extern physx::PxMaterial* gMaterial;

#endif