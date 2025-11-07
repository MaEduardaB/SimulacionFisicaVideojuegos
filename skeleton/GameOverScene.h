#pragma once
#include "Scene.h"
#include <string>

class GameOverScene : public Scene {
public:
    GameOverScene();
    ~GameOverScene() override;

    void enter() override;
    void update(double t) override;
    void render() const override;
    void exit() override;
    void keyPressed(unsigned char key) override;
};
