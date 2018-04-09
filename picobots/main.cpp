#include "engine.h"
#include "game.h"
#include "scenes/scene_splash.h"
#include <SFML/Audio.hpp>

using namespace std;

SplashScene splash;
MenuScene menu;
StateScene stateScene;		//tbd
DecisionScene decisionScene;//tbd
Level1Scene level1;
BossLevelScene bosslevel;
SettingsScene settings;
GameOverScene gameover;
EndGameScene endgame;
HighScoresScene highscores;
TutorialScene tutorial;
LoadScene load;

int main() {

	Engine::Start(1504, 846, "Picobots", &splash);
}
