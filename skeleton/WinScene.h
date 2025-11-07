#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "FireworkGen.h"
#include <string>

namespace Snippets { class Camera; }

class ParticleSystem;
class FireworkGen;
class WinScene : public Scene
{
public:
    WinScene(Snippets::Camera* cam);
    ~WinScene() override;

    void enter() override;
    void update(double t) override;
    void render() const override;
    void exit() override;
    void keyPressed(unsigned char key) override;

protected:
    std::string display_text;
    ParticleSystem* _particleSystem;
    FireworkGen* _fireworkGen;      

	Snippets::Camera* _cam;

    double _timer = 0.0;
    double _interval = 1.0;
};