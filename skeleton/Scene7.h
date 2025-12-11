#pragma once
#include "Scene.h"
#include "core.hpp"

namespace Snippets { class Camera; }

class ForceGenerator;
class GravityForce;
class RigidBodySystem;

class Particle;
class Scene7:
    public Scene
{
public:
	Scene7(Snippets::Camera* cam);
	~Scene7() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void keyPressed(unsigned char key) override;

protected:
	Snippets::Camera* _cam;
	GravityForce* _gravity;
	RigidBodySystem* _rigidBodySystem;
	std::vector<Particle*> _gObjects;

	std::vector<ForceGenerator*> _rigidForces;
};

