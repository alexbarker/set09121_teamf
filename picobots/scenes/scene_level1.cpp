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
#include "system_renderer.h"

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
sf::Vector2u TextureSize78;  //Added to store texture size.
sf::Vector2u WindowSize78;   //Added to store window size.
Vector2f target79;
sf::Vector2u TextureSize79;  //Added to store texture size.
sf::Vector2u WindowSize79;   //Added to store window size.
int c = 0;
sf::Clock clock2;

sf::Texture playerBotTex;
sf::IntRect playerSource(0, 0, 206, 207);
sf::Sprite playerBotSprite(playerBotTex, playerSource);
float rotation = 0;

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

	SetBackground();
	SetTitle();

	playerBotSprite.setPosition(400.f, 400.0f);
	playerBotTex.loadFromFile("res/img/PlayerSpritesheet.png");
	//playerBotTex.setSmooth(true);
	playerBotSprite.setTexture(playerBotTex);

	auto player = makeEntity();
	player->addTag("player");
	player->setPosition(Vector2f(x2 / 2, y2 / 2));
	auto s = player->addComponent<SpriteComponent>();
	s->setSprite(playerBotSprite);
	player->addComponent<BasicMovementComponent>();
	playerBotSprite.setScale(0.2, 0.2);
}

void Level1Scene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {
	Scene::Update(dt);
	if (clock2.getElapsedTime().asSeconds() > 0.04f) {
		if (playerSource.left == 2884) {
			playerSource.left = 0;
		}
		else {
			playerSource.left += 206;
			playerBotSprite.setTextureRect(playerSource);
			clock2.restart();
		}
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

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		s1.play1(0, true);
		Engine::ChangeScene(&menu);
	}
}

void Level1Scene::Render() {
	Scene::Render();
	Renderer::queue(&playerBotSprite);

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
