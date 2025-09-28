#pragma once
#include <vector>
class Entity;
class Scene
{
public:

	Scene();
	virtual ~Scene() = 0;
	virtual void update(double t) = 0;
	virtual void render() const = 0;
	virtual void exit() = 0;
	virtual void enter() = 0;

protected:
	std::vector<Entity*> gObjects;
};

