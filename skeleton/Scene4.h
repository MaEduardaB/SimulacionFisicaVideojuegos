#pragma once
#include "Scene.h"
class ParticleSystem;
namespace Snippets { class Camera; }

class Scene4 :
    public Scene
{
public:
	Scene4(Snippets::Camera* cam);
	~Scene4() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void keyPressed(unsigned char key) override;

protected:
	Snippets::Camera* _cam;
};

