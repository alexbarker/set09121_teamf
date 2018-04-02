#include "engine.h"
#include "game.h"
#include "scenes/scene_splash.h"
#include <SFML/Audio.hpp>

using namespace std;

SplashScene splash;
MenuScene menu;
StateScene stateScene;
DecisionScene decisionScene;

int main() {

	Engine::Start(1280, 720, "Picobots", &splash);	
}
