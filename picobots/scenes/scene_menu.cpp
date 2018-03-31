#include "scene_splash.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "../components/cmp_music.h"

using namespace std;
using namespace sf;

void MenuScene::Load() {
  {	
	s2.stop();
	s3.stop();
	s1.playing();
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Decision demos\nPress 1 for state machines\nPress 2 for decision trees");
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
	  
    Engine::ChangeScene(&stateScene);
  }
  else if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {

	  Engine::ChangeScene(&decisionScene);
  }
  Scene::Update(dt);
}


