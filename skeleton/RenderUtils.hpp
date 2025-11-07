#ifndef __RENDER_UTILS_H__
#define __RENDER_UTILS_H__

#include "PxPhysicsAPI.h"
#include "core.hpp"
#include <string>
#include <gl/GL.h>

class RenderItem;
void RegisterRenderItem(const RenderItem* _item);
void DeregisterRenderItem(const RenderItem* _item);
void DeregisterAllRenderItem();

GLuint LoadTexture(const std::string& filename);
class RenderItem
{
public:
	RenderItem(physx::PxShape* _shape, const physx::PxTransform* _trans, const Vector4& _color, const std::string& texPath = "") :
		shape(_shape), transform(_trans), actor(NULL), color(_color), texturePath(texPath), textureID(0), references(1)
	{
		shape->acquireReference();
		if (!texturePath.empty())
			textureID = LoadTexture(texturePath);
		RegisterRenderItem(this);
	}

	RenderItem(physx::PxShape* _shape, const Vector4& _color, const std::string& texPath = "") :
		shape(_shape), transform(NULL), actor(NULL), color(_color), texturePath(texPath), textureID(0), references(1)
	{
		shape->acquireReference();
		if (!texturePath.empty())
			textureID = LoadTexture(texturePath);
		RegisterRenderItem(this);
	}

	RenderItem(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color, const std::string& texPath = "") :
		shape(_shape), transform(NULL), actor(_actor), color(_color), texturePath(texPath), textureID(0), references(1)
	{
		shape->acquireReference();
		if (!texturePath.empty())
			textureID = LoadTexture(texturePath);
		RegisterRenderItem(this);
	}

	RenderItem() : shape(NULL), transform(NULL), references(1) {}

	void addReference()
	{
		++references;
	}

	void release()
	{
		--references;
		if (references == 0)
		{
			DeregisterRenderItem(this);
			if (textureID != 0)
				glDeleteTextures(1, &textureID);
			shape->release();
			delete this;
		}
	}

public:
	physx::PxShape* shape;
	const physx::PxTransform* transform;
	const physx::PxRigidActor* actor;
	Vector4 color;

	std::string texturePath;
	GLuint textureID;

	unsigned references;

	bool visible = true;

    void setVisible(bool v) { visible = v; }
    bool isVisible() const { return visible; }
};

double GetLastTime();
Camera* GetCamera();

physx::PxShape* CreateShape(const physx::PxGeometry& geo, const physx::PxMaterial* mat = nullptr);

#endif