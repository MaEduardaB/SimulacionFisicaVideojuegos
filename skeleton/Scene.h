#pragma once
#include <list>
#include <string>
class ParticleSystem;
class ForceRegestry;
class Scene
{
public:

	Scene() {};
	virtual ~Scene() {};
	virtual void update(double t) = 0;
	virtual void keyPressed(unsigned char key) = 0;
	virtual void render() const = 0;
	virtual void exit() = 0;
	virtual void enter() = 0;

	std::string get_display_text() const { return display_text; }

protected:
	std::list<ParticleSystem*> _particleSystems;
	ForceRegestry* _force_registry;

	std::string display_text = " ";
};

