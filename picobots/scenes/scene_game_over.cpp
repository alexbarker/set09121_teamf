#include "engine.h"
#include "../game.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../components/cmp_music.h"


using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void GameOverScene::Load() {
}

void GameOverScene::UnLoad() {
	Scene::UnLoad();
}

void GameOverScene::Update(const double& dt) {
	Scene::Update(dt);
}

void GameOverScene::Render() {
	Scene::Render();
}
