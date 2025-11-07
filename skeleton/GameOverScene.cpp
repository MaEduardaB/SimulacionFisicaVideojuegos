#include "GameOverScene.h"
#include "RenderUtils.hpp"
#include "SceneManager.h"
#include "Constants.h"
#include <iostream>

GameOverScene::GameOverScene()
{
    display_text = "Has perdido, preciona p para reiniciar";;
}

GameOverScene::~GameOverScene() {}

void GameOverScene::enter() {
    std::cout << "[GameOverScene] Escena de inicio cargada\n";
}

void GameOverScene::update(double) {
}

void GameOverScene::render() const
{
}

void GameOverScene::exit() {}

void GameOverScene::keyPressed(unsigned char key) {
    if(key == 'G' || key == 'g') {
		SceneManager::instance().change_to_scene(SCENE_TYPE::MAIN_MENU);
	}else if (key == 'p' || key == 'P') {
        std::cout << "Cambiando a GameScene\n";
        SceneManager::instance().change_to_scene(SCENE_TYPE::GAME);
    }
}
