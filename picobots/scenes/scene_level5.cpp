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
#include "scene_level5.h"
#include "../add_entity.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

sf::Sprite backgroundSprite5a;
sf::Texture backgroungTexture5a;
sf::Vector2u backgroundSize5a;  //Added to store texture size.
sf::Vector2u windowSize5a;   //Added to store window size.
sf::Sprite titleSprite5b;
sf::Texture titleTexture5b;
sf::Vector2u titleSize5b;
sf::Vector2u windowSize5b;
int fadeCounter5 = 0;

void Level5Scene::SetTitle() {
	titleTexture5b = *Resources::load<Texture>("title.png");
	float x1 = Engine::GetWindow().getSize().x;
	float y1 = Engine::GetWindow().getSize().y;
	titleSize5b = titleTexture5b.getSize(); //Get size of texture.
	windowSize5b = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize5b.x / titleSize5b.x;
	float ScaleY = (float)windowSize5b.y / titleSize5b.y;     //Calculate scale.
	titleSprite5b.setTexture(titleTexture5b);
	titleSprite5b.setPosition(windowSize5b.x / 9.2, windowSize5b.y / 12.5);
	titleSprite5b.setScale(ScaleX / 6, ScaleY / 6);
	titleSprite5b.setOrigin(titleSize5b.x / 2, titleSize5b.y / 2);
}

void Level5Scene::SetBackground() {
	backgroungTexture5a = *Resources::load<Texture>("mainfullscreen.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	backgroundSize5a = backgroungTexture5a.getSize(); //Get size of texture.
	windowSize5a = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize5a.x / backgroundSize5a.x;
	float ScaleY = (float)windowSize5a.y / backgroundSize5a.y;     //Calculate scale.
	backgroundSprite5a.setTexture(backgroungTexture5a);
	backgroundSprite5a.setPosition(0, 0);
	backgroundSprite5a.setScale(ScaleX, ScaleY);
	backgroundSprite5a.setOrigin(0, 0);
}

void Level5Scene::Load() {
	s2.playing();

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/level5.txt", temp);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * temp);
	ls::setOffset(Vector2f(x2 / 4.72, ho));

	SetBackground();
	SetTitle();

	player = AddEntity::makePlayer(this, Vector2f(x2 / 2, y2 / 2));

	AddEntity::makeWalls(this);
}

void Level5Scene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level5Scene::Update(const double& dt) {

	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::END) {
		Engine::ChangeScene((Scene*)&level6);
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

void Level5Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();

	if (fadeCounter5 <= 250) {
		titleSprite5b.setColor(sf::Color(255, 255, 255, fadeCounter5));
		fadeCounter5--;
		Renderer::queue(&backgroundSprite5a);
		Renderer::queue(&titleSprite5b);
	}
	else {
		fadeCounter5 = 0;
		Renderer::queue(&backgroundSprite5a);
		Renderer::queue(&titleSprite5b);
	}
}
