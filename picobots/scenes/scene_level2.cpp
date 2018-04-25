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
#include "scene_level2.h"
#include "../add_entity.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

sf::Sprite backgroundSprite2a;
sf::Texture backgroungTexture2a;
sf::Vector2u backgroundSize2a;  //Added to store texture size.
sf::Vector2u windowSize2a;   //Added to store window size.
sf::Sprite titleSprite2b;
sf::Texture titleTexture2b;
sf::Vector2u titleSize2b;
sf::Vector2u windowSize2b;
int fadeCounter2 = 0;


void Level2Scene::SetTitle() {
	titleTexture2b = *Resources::load<Texture>("title.png");
	float x1a = Engine::GetWindow().getSize().x;
	float y1a = Engine::GetWindow().getSize().y;
	titleSize2b = titleTexture2b.getSize(); //Get size of texture.
	windowSize2b = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleXa = (float)windowSize2b.x / titleSize2b.x;
	float ScaleYa = (float)windowSize2b.y / titleSize2b.y;     //Calculate scale.
	titleSprite2b.setTexture(titleTexture2b);
	titleSprite2b.setPosition(windowSize2b.x / 9.2, windowSize2b.y / 12.5);
	titleSprite2b.setScale(ScaleXa / 6, ScaleYa / 6);
	titleSprite2b.setOrigin(titleSize2b.x / 2, titleSize2b.y / 2);
}

void Level2Scene::SetBackground() {
	backgroungTexture2a = *Resources::load<Texture>("main1.png");
	float xb = Engine::GetWindow().getSize().x;
	float yb = Engine::GetWindow().getSize().y;
	backgroundSize2a = backgroungTexture2a.getSize(); //Get size of texture.
	windowSize2a = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleXb = (float)windowSize2a.x / backgroundSize2a.x;
	float ScaleYb = (float)windowSize2a.y / backgroundSize2a.y;     //Calculate scale.
	backgroundSprite2a.setTexture(backgroungTexture2a);
	backgroundSprite2a.setPosition(0, 0);
	backgroundSprite2a.setScale(ScaleXb, ScaleYb);
	backgroundSprite2a.setOrigin(0, 0);
}

void Level2Scene::Load() {
	s2.playing();

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/level2.txt", temp);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * temp);
	ls::setOffset(Vector2f(x2 / 4.72, ho));

	SetBackground();
	SetTitle();

	player = AddEntity::makePlayer(this, Vector2f(x2/2, y2/2));

	AddEntity::makeWalls(this);
}

void Level2Scene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level2Scene::Update(const double& dt) {

	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::END) {
		Engine::ChangeScene((Scene*)&level3);
	}

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

void Level2Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();

	if (fadeCounter2 <= 250) {
		titleSprite2b.setColor(sf::Color(255, 255, 255, fadeCounter2));
		fadeCounter2--;
		Renderer::queue(&backgroundSprite2a);
		Renderer::queue(&titleSprite2b);
	}
	else {
		fadeCounter2 = 0;
		Renderer::queue(&backgroundSprite2a);
		Renderer::queue(&titleSprite2b);
	}
}
