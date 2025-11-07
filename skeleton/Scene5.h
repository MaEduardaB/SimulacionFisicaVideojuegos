#pragma once
#include "Scene.h"
#include "core.hpp"

namespace Snippets { class Camera; }

class ParticleSystem;
class Scene5:
    public Scene
{
public:
	Scene5(Snippets::Camera* cam);
	~Scene5() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void keyPressed(unsigned char key) override;

protected:
	Snippets::Camera* _cam;
};

