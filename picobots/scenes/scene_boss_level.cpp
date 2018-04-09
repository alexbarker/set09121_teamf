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

void BossLevelScene::Load() {
}

void BossLevelScene::UnLoad() {
	Scene::UnLoad();
}

void BossLevelScene::Update(const double& dt) {
	Scene::Update(dt);
}

void BossLevelScene::Render() {
	Scene::Render();
}