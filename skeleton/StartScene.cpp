#include "StartScene.h"
#include "RenderUtils.hpp"
#include "SceneManager.h"
#include <iostream>

StartScene::StartScene()
{
    display_text = "Scene 1: Press 'p' para iniciar.";;
}

StartScene::~StartScene() {}

void StartScene::enter() {
    std::cout << "[StartScene] Escena de inicio cargada\n";
}

void StartScene::update(double) {
}

void StartScene::render() const
{
}

void StartScene::exit() {}

void StartScene::keyPressed(unsigned char key) {
    if (key == 'p' || key == 'P') {
        std::cout << "Cambiando a GameScene\n";
        SceneManager::instance().change_to_scene(SCENE_TYPE::GAME);
    }
}
