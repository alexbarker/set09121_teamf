#include "scene_splash.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "../components/cmp_music.h"
#include "system_renderer.h"
#include "system_resources.h"
#include "../components/cmp_sprite.h"
#include "scene_menu.h"
#include "maths.h"
#include "LevelSystem.h"
#include <SFML/Graphics.hpp>
#include "../add_entity.h"

using namespace std;
using namespace sf;

sf::Sprite sprite91;
sf::Texture tex91;
Vector2f target91;
sf::Vector2u TextureSize91;  //Added to store texture size.
sf::Vector2u WindowSize91;   //Added to store window size.
int a = 0;

sf::Texture roboarmTexture;
sf::IntRect roboSource(0, 0, 400, 300);
sf::Sprite roboarm(roboarmTexture, roboSource);
sf::Texture roboarmTexture2;
sf::IntRect roboSource2(0, 0, -400, 300);
sf::Sprite roboarm2(roboarmTexture2, roboSource2);
sf::Clock clock1;

void MenuScene::SetTitle() {
	tex91 = *Resources::load<Texture>("title.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	TextureSize91 = tex91.getSize();							//Get size of texture.
	WindowSize91 = Engine::GetWindow().getSize();               //Get size of window.
	float ScaleX = (float)WindowSize91.x / TextureSize91.x;
	float ScaleY = (float)WindowSize91.y / TextureSize91.y;     //Calculate scale.
	target91 = { x , y };
	sprite91.setTexture(tex91);
	sprite91.setPosition(WindowSize91.x/2, WindowSize91.y/3);
	//sprite91.setScale(ScaleX/2, ScaleY/2);
	sprite91.setOrigin(TextureSize91.x/2, TextureSize91.y/2);
}

void MenuScene::Load() {
  {
		s2.stop();
		s3.stop();
		s1.playing();
		float x2 = Engine::getWindowSize().x;
		float y2 = Engine::getWindowSize().y;
		SetTitle();

		roboarm.setPosition(x2-400.0f, 200.0f);
		roboarmTexture.loadFromFile("res/img/RoboarmSprite.png");
		roboarm2.setPosition(0, 200.0f);
		roboarmTexture2.loadFromFile("res/img/RoboarmSprite.png");

		font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");

		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Green);
		menu[0].setString("New Game");
		menu[0].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 40 ));

		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Load Game");
		menu[1].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 80));

		menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("High Scores");
		menu[2].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 120));

		menu[3].setFont(font);
		menu[3].setFillColor(sf::Color::White);
		menu[3].setString("Tutorial");
		menu[3].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 160));

		menu[4].setFont(font);
		menu[4].setFillColor(sf::Color::White);
		menu[4].setString("Settings");
		menu[4].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 200));

		menu[5].setFont(font);
		menu[5].setFillColor(sf::Color::White);
		menu[5].setString("Quit");
		menu[5].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 240));

		selectedItemIndex = 0;

	//std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {	
	Scene::Update(dt);

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
		a = 0;
		UnLoad();
		Load();
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Up)) { 
		MoveUp(); 
		std::this_thread::sleep_for(std::chrono::milliseconds(170));
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::Down)) { 
		MoveDown(); 
		std::this_thread::sleep_for(std::chrono::milliseconds(170));
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) { 
		switch (GetPressedItem())
		{
		case 0:
			Engine::ChangeScene(&level1);
			break;
		case 1:
			Engine::ChangeScene(&level1);
			break;
		case 2:
			Engine::ChangeScene(&highscores);
			break;
		case 3:
			Engine::ChangeScene(&tutorial);
			break;
		case 4:
			Engine::ChangeScene(&settings);
			break;
		case 5:
			Engine::GetWindow().close();
			break;
		}
	}
}

void MenuScene::Render() {
	Scene::Render();

	if (clock1.getElapsedTime().asSeconds() > 0.2f) {
		if (roboSource.left == 6000) {
			roboSource.left = 0;
			roboSource2.left = 0;
			if (clock1.getElapsedTime().asSeconds() > 0.2f) { AddEntity::makeFakePlayer2(this, Vector2f(0.f, 450.f), Vector2f(70.f, 950.f), 2.0f); }
			if (clock1.getElapsedTime().asSeconds() > 0.2f) { AddEntity::makeFakePlayer1(this, Vector2f(Engine::getWindowSize().x - 25.f, 450.f), Vector2f(Engine::getWindowSize().x - 70.f, 450.f), 2.0f); }
		}
		else {

			roboSource.left += 400;
			roboarm.setTextureRect(roboSource);
			roboSource2.left += 400;
			roboarm2.setTextureRect(roboSource2);
			clock1.restart();
		}
	}

	if (a <= 250) {
		roboarm.setColor(sf::Color(255, 255, 255, a));
		roboarm2.setColor(sf::Color(255, 255, 255, a));
		sprite91.setColor(sf::Color(255, 255, 255, a));
		a++;
		Renderer::queue(&roboarm);
		Renderer::queue(&roboarm2);
		Renderer::queue(&sprite91);
	}
	else {
		roboarm.setColor(sf::Color(255, 255, 255, 255));
		roboarm2.setColor(sf::Color(255, 255, 255, 255));
		sprite91.setColor(sf::Color(255, 255, 255, 255));
		Renderer::queue(&roboarm);
		Renderer::queue(&roboarm2);
		Renderer::queue(&sprite91);
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			Renderer::queue(&menu[i]);
		}
	}
}

void MenuScene::UnLoad() { 
    float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	Scene::UnLoad();
}

void MenuScene::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Green);
	}
}

void MenuScene::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Green);
	}
}


