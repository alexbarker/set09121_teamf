#include "engine.h"
#include "game.h"
#include "scenes/scene_splash.h"
#include <SFML/Audio.hpp>

using namespace std;

SplashScene splash;
MenuScene menu;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
Level4Scene level4;
Level5Scene level5;
Level6Scene level6;
Level7Scene level7;
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
