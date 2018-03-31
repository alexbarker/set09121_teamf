#include "engine.h"
#include "../game.h"
#include "scene_splash.h"
#include "../components/cmp_text.h"
#include "../scenes/scene_menu.h"
#include "../components/cmp_music.h"
#include <LevelSystem.h>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
MusicPlayer s1;

void SplashScene::Load(){
	
	s1.play1(0, true);
	{
		s1.playing();
	
	auto txt = makeEntity();
	auto t = txt->addComponent<TextComponent>(
		"Splash Screen");
	}

	setLoaded(true);
	s1.playing();
	std::this_thread::sleep_for(std::chrono::milliseconds(8000));
	Engine::ChangeScene(&menu);
}

void SplashScene::UnLoad() { Scene::UnLoad(); }

void SplashScene::Update(const double& dt) { 
	
	Scene::Update(dt); 
}

void SplashScene::Render() { Scene::Render(); }
