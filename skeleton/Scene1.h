#pragma once
#include "Scene.h"
class Scene1 :
    public Scene
{
public:
	Scene1();
	~Scene1() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void create() override;

protected:

	std::vector<Particle*> _gObjects;
};

