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
#include "scene_level3.h"
#include "../add_entity.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

sf::Sprite backgroundSprite3a;
sf::Texture backgroungTexture3a;
sf::Vector2u backgroundSize3a;  //Added to store texture size.
sf::Vector2u windowSize3a;   //Added to store window size.
sf::Sprite titleSprite3b;
sf::Texture titleTexture3b;
sf::Vector2u titleSize3b;
sf::Vector2u windowSize3b;
int fadeCounter3 = 0;

void Level3Scene::SetTitle() {
	titleTexture3b = *Resources::load<Texture>("title.png");
	float x1 = Engine::GetWindow().getSize().x;
	float y1 = Engine::GetWindow().getSize().y;
	titleSize3b = titleTexture3b.getSize(); //Get size of texture.
	windowSize3b = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize3b.x / titleSize3b.x;
	float ScaleY = (float)windowSize3b.y / titleSize3b.y;     //Calculate scale.
	titleSprite3b.setTexture(titleTexture3b);
	titleSprite3b.setPosition(windowSize3b.x / 9.2, windowSize3b.y / 12.5);
	titleSprite3b.setScale(ScaleX / 6, ScaleY / 6);
	titleSprite3b.setOrigin(titleSize3b.x / 2, titleSize3b.y / 2);
}

void Level3Scene::SetBackground() {
	backgroungTexture3a = *Resources::load<Texture>("mainfullscreen.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	backgroundSize3a = backgroungTexture3a.getSize(); //Get size of texture.
	windowSize3a = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize3a.x / backgroundSize3a.x;
	float ScaleY = (float)windowSize3a.y / backgroundSize3a.y;     //Calculate scale.
	backgroundSprite3a.setTexture(backgroungTexture3a);
	backgroundSprite3a.setPosition(0, 0);
	backgroundSprite3a.setScale(ScaleX, ScaleY);
	backgroundSprite3a.setOrigin(0, 0);
}

void Level3Scene::Load() {
	s2.playing();

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/level3.txt", temp);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * temp);
	ls::setOffset(Vector2f(x2 / 4.72, ho));

	SetBackground();
	SetTitle();

	player = AddEntity::makePlayer(this, Vector2f(x2 / 2, y2 / 2));

	AddEntity::makeWalls(this);
}

void Level3Scene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level3Scene::Update(const double& dt) {

	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::END) {
		Engine::ChangeScene((Scene*)&level4);
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

void Level3Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();

	if (fadeCounter3 <= 250) {
		titleSprite3b.setColor(sf::Color(255, 255, 255, fadeCounter3));
		fadeCounter3--;
		Renderer::queue(&backgroundSprite3a);
		Renderer::queue(&titleSprite3b);
	}
	else {
		fadeCounter3 = 0;
		Renderer::queue(&backgroundSprite3a);
		Renderer::queue(&titleSprite3b);
	}
}
