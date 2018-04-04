#pragma once
#include "engine.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include "SFML/Graphics.hpp"
#include "../components/cmp_music.h"

#define MAX_NUMBER_OF_ITEMS 5

class MenuScene : public Scene 
{
public:

  void Load() override;
  void UnLoad() override;
  void Update(const double& dt) override;
  void Render() override;

  void MoveUp();
  void MoveDown();
  int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

