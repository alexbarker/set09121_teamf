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

using namespace std;
using namespace sf;

/*
void Loading_render1() {
	int startAlpha = 0;
	int currentAlpha = 255;
	sf::Time targetTime = sf::seconds(3);
	sf::Clock timer;
	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	static Text t("PICOBOTS", *Resources::get<sf::Font>("RobotoMono-Regular.ttf"));
	t.setPosition(sf::Vector2f((x2 / 2) - 40, (y2 / 2) + 40));
	t.setColor(sf::Color::White);
	while (currentAlpha != 0)
	{
		sf::Time currentTime = timer.getElapsedTime();
		


		if (currentTime >= targetTime)
		{
			return;
		}
		else
		{
			
			currentAlpha--;
		}
		sf::Color fadeColor = t.getFillColor();
		fadeColor.a = currentAlpha;
		t.setFillColor(fadeColor);
		Renderer::queue(&t);
	}
}
*/
void MenuScene::Load() {
  {	
	s2.stop();
	s3.stop();
	s1.playing();
    //auto txt = makeEntity();
    //auto t = txt->addComponent<TextComponent>("Decision");
	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;

	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");

	//Loading_render1();

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

	/*
	auto txtNewGame = makeEntity();
	auto t = txtNewGame->addComponent<TextComponent>("New Game");
	t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
	txtNewGame->setPosition(Vector2f(280.f, 500.f));
	*/
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  /*if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
	  
    Engine::ChangeScene(&stateScene);
  }
  else if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {

	  Engine::ChangeScene(&decisionScene);
  }*/

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
			Engine::ChangeScene(&decisionScene);
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

void MenuScene::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		cout << selectedItemIndex;
		menu[selectedItemIndex].setColor(sf::Color::Green);
	}
}

void MenuScene::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		cout << selectedItemIndex;
		menu[selectedItemIndex].setColor(sf::Color::Green);
	}
}


