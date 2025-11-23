#pragma once
#include "Scene.h"
#include "core.hpp"

namespace Snippets { class Camera; }

class ParticleSystem;
class Scene6:
    public Scene
{
public:
	Scene6(Snippets::Camera* cam);
	~Scene6() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void keyPressed(unsigned char key) override;

protected:
	Snippets::Camera* _cam;
};

