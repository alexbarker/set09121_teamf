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

using namespace std;
using namespace sf;
//sf::Sprite sprite5;
//sf::Texture tex5;
//Vector2f target5;
//sf::Vector2u TextureSize5;  //Added to store texture size.
//sf::Vector2u WindowSize5;   //Added to store window size.

void MenuScene::Load() {
  {	/*
		tex5 = *Resources::load<Texture>("splash3.png");
		float x = Engine::GetWindow().getSize().x;
		float y = Engine::GetWindow().getSize().y;
		TextureSize5 = tex5.getSize(); //Get size of texture.
		WindowSize5 = Engine::GetWindow().getSize();             //Get size of window.
		float ScaleX = (float)WindowSize5.x / TextureSize5.x;
		float ScaleY = (float)WindowSize5.y / TextureSize5.y;     //Calculate scale.
		target5 = { x , y };
		sprite5.setTexture(tex5);
		sprite5.setPosition(0, 0);
		sprite5.setScale(ScaleX, ScaleY);
		sprite5.setOrigin(0, 0);*/
		s2.stop();
		s3.stop();
		s1.playing();
		float x2 = Engine::getWindowSize().x;
		float y2 = Engine::getWindowSize().y;
		//cout << "(a" << x2 << "-" << y2 << ")";

	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Green);
	menu[0].setString("New Game");
	menu[0].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 40 ));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Load Game");
	menu[1].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 80));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Tutorial");
	menu[2].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 120));

	menu[3].setFont(font);
	menu[3].setColor(sf::Color::White);
	menu[3].setString("Settings");
	menu[3].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 160));

	menu[4].setFont(font);
	menu[4].setColor(sf::Color::White);
	menu[4].setString("Quit");
	menu[4].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 200));

	selectedItemIndex = 0;

	//std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
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
			Engine::ChangeScene(&stateScene);
			break;
		case 1:
			Engine::ChangeScene(&decisionScene);
			break;
		case 2:
			Engine::ChangeScene(&decisionScene);
			break;
		case 3:
			Engine::ChangeScene(&decisionScene);
			break;
		case 4:
			Engine::GetWindow().close();
			break;
		}
	}
  Scene::Update(dt);
}

void MenuScene::Render() {

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		Renderer::queue(&menu[i]);
	}
	Scene::Render();
}

void MenuScene::UnLoad() { 
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	Scene::UnLoad(); }

void MenuScene::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Green);
	}
}

void MenuScene::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Green);
	}
}


