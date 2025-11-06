#pragma once
#include "Scene.h"
#include <string>

class StartScene : public Scene {
public:
    StartScene();
    ~StartScene() override;

    void enter() override;
    void update(double t) override;
    void render() const override;
    void exit() override;
    void keyPressed(unsigned char key) override;
};
