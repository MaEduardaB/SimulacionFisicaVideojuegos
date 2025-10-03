#pragma once
#include <vector>
class Particle;
class Scene
{
public:

	Scene() {};
	virtual ~Scene() {};
	virtual void update(double t) = 0;
	virtual void render() const = 0;
	virtual void exit() = 0;
	virtual void enter() = 0;

};

