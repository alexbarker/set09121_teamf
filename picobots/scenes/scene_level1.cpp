#include "engine.h"
#include "../game.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <system_resources.h>
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../components/cmp_music.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_basic_movement.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_physics.h"
#include "system_renderer.h"
#include "scene_level1.h"
#include "../add_entity.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

sf::Sprite sprite77;
sf::Texture tex77;
Vector2f target77;
sf::Vector2u TextureSize77;  //Added to store texture size.
sf::Vector2u WindowSize77;   //Added to store window size.
sf::Sprite sprite78;
sf::Texture tex78;
Vector2f target78;
sf::Vector2u TextureSize78;  
sf::Vector2u WindowSize78;   
Vector2f target79;
sf::Vector2u TextureSize79;  
sf::Vector2u WindowSize79;  
int c = 0;
sf::Clock clock2;
Vector2f view_center;

void Level1Scene::SetTitle() {
	tex78 = *Resources::load<Texture>("title.png");
	float x1 = Engine::GetWindow().getSize().x;
	float y1 = Engine::GetWindow().getSize().y;
	TextureSize78 = tex78.getSize(); //Get size of texture.
	WindowSize78 = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)WindowSize78.x / TextureSize78.x;
	float ScaleY = (float)WindowSize78.y / TextureSize78.y;     //Calculate scale.
	target78 = { x1 , y1 };
	sprite78.setTexture(tex78);
	sprite78.setPosition(WindowSize78.x / 9.2, WindowSize78.y / 12.5);
	sprite78.setScale(ScaleX / 6, ScaleY / 6);
	sprite78.setOrigin(TextureSize78.x / 2, TextureSize78.y / 2);
}

void Level1Scene::SetBackground() {
	tex77 = *Resources::load<Texture>("main1.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	TextureSize77 = tex77.getSize(); //Get size of texture.
	WindowSize77 = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)WindowSize77.x / TextureSize77.x;
	float ScaleY = (float)WindowSize77.y / TextureSize77.y;     //Calculate scale.
	target77 = { x , y };
	sprite77.setTexture(tex77);
	sprite77.setPosition(0, 0);
	sprite77.setScale(ScaleX, ScaleY);
	sprite77.setOrigin(0, 0);
}

void Level1Scene::Load() {
	s1.stop();
	s2.play2(1, true);

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	ls::loadLevelFile("res/testLevel.txt", 20.0f);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 20.f);
	ls::setOffset(Vector2f(328, ho));

	SetBackground();
	SetTitle();

	player = AddEntity::makePlayer(this, Vector2f(800.f,500.f));

	AddEntity::makeWalls(this);

	view_center = player->getPosition();
}

void Level1Scene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

	
	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::END) {
		Engine::ChangeScene((Scene*)&level1);
	}
	else if (!player->isAlive()) {
		Engine::ChangeScene((Scene*)&level1);
	}
	
	/*
	if (ls::getTileAt(player->getPosition()) == ls::END) {
		Engine::ChangeScene((Scene*)&level1);
	}*/
	/*
	if (ls::getTileAt(player->getPosition()) == ls::WALL) {
		auto physics = player->addComponent<PhysicsComponent>(true, sf::Vector2f(51.533333333333333333333333333333f, 52.f));
		physics->setGravityScale(0);
		//physics->impulse(sf::Vector2f(7.5f, 0));
		physics->dampen(sf::Vector2f(0.f, 0));
		player.reset();
	}*/

	/*
	//View view1(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	/*
	float view_player_distance = sqrt(((player->getPosition().x - view_center.x) * (player->getPosition().x - view_center.x)) + ((player->getPosition().y - view_center.y) * (player->getPosition().y - view_center.y)));
	if (view_player_distance > 40.f)
		view_center += (player->getPosition() - view_center) *(float)dt * 4.f;
	view1.setCenter(view_center);
	*/

	Event event;
	while (Engine::GetWindow().pollEvent(event)) {
		if (event.type == sf::Event::Resized) {
			UnLoad();
			Engine::GetWindow().setSize(sf::Vector2u(event.size.width, event.size.height));
			Engine::GetWindow().display();
			Load();
		}
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::R)) {
		UnLoad();
		Load();
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
		s1.play1(0, true);
		Engine::ChangeScene(&menu);
	}
	Scene::Update(dt);
}

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();

	if (c <= 250) {
		sprite78.setColor(sf::Color(255, 255, 255, c));
		c--;
		Renderer::queue(&sprite77);
		Renderer::queue(&sprite78);
	}
	else {
		c = 0;	
		Renderer::queue(&sprite77);
		Renderer::queue(&sprite78);		
	}
}
