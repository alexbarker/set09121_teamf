#pragma once
#include "engine.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include "../components/cmp_music.h"

class MenuScene : public Scene {
public:

  MenuScene() = default;
  ~MenuScene() override = default;

  void Load() override;

  void Update(const double& dt) override;
};
