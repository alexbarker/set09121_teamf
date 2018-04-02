#include "engine.h"
#include "../game.h"
#include "scene_splash.h"
#include "../components/cmp_text.h"
#include "../scenes/scene_menu.h"
#include "../components/cmp_music.h"
#include <LevelSystem.h>
#include <SFML/Audio.hpp>
#include "../components/cmp_sprite.h"
#include <SFML/Graphics/Sprite.hpp>
#include <system_renderer.h>
#include <system_resources.h>

using namespace std;
using namespace sf;
MusicPlayer s1;
sf::Sprite sprite;
sf::Texture tex;
Vector2f target;
sf::Vector2u TextureSize;  //Added to store texture size.
sf::Vector2u WindowSize;   //Added to store window size.

void SplashScene::Load(){
	
	s1.play1(0, true);
	{
		s1.playing();
		tex = *Resources::load<Texture>("splash3.png");
		float x = Engine::GetWindow().getSize().x;
		float y = Engine::GetWindow().getSize().y;
		TextureSize = tex.getSize(); //Get size of texture.
		WindowSize = Engine::GetWindow().getSize();             //Get size of window.
		float ScaleX = (float)WindowSize.x / TextureSize.x;
		float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.
		target = { x , y };
		sprite.setTexture(tex);
		sprite.setPosition(0, 0);
		sprite.setScale(ScaleX, ScaleY);
		sprite.setOrigin(0, 0);	
		setLoaded(true);
		s1.playing();
		std::this_thread::sleep_for(std::chrono::milliseconds(4000));
		s1.playing();
		tex = *Resources::load<Texture>("splash4.png");
		float x2 = Engine::GetWindow().getSize().x;
		float y2 = Engine::GetWindow().getSize().y;
		TextureSize = tex.getSize(); //Get size of texture.
		WindowSize = Engine::GetWindow().getSize();             //Get size of window.
		float ScaleX1 = (float)WindowSize.x / TextureSize.x;
		float ScaleY1 = (float)WindowSize.y / TextureSize.y;     //Calculate scale.
		target = { x2 , y2 };
		sprite.setTexture(tex);
		sprite.setPosition(0, 0);
		sprite.setScale(ScaleX1, ScaleY1);
		sprite.setOrigin(0, 0);	
		setLoaded(true);
		s1.playing();
		std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	}

	setLoaded(true);
	s1.playing();
	//std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	Engine::ChangeScene(&menu);
}

void SplashScene::UnLoad() { Scene::UnLoad(); }

void SplashScene::Update(const double& dt) { 
	
	Scene::Update(dt); 
}

void SplashScene::Render() { 
	Renderer::queue(&sprite);
	Scene::Render(); 
}
