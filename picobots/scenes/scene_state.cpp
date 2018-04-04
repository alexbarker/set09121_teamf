#include "scene_state.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_basic_movement.h"
#include "../components/cmp_state_machine.h"
#include "../enemy_states.h"
#include <LevelSystem.h>
#include "../game.h"
#include "../components/cmp_music.h"
#include <system_resources.h>

using namespace std;
using namespace sf;

MusicPlayer s3;
sf::Sprite sprite9;
sf::Texture tex9;
Vector2f target9;
sf::Vector2u TextureSize9;  //Added to store texture size.
sf::Vector2u WindowSize9;   //Added to store window size.

void StateScene::Load()
{
	tex9 = *Resources::load<Texture>("main1.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	TextureSize9 = tex9.getSize(); //Get size of texture.
	WindowSize9 = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)WindowSize9.x / TextureSize9.x;
	float ScaleY = (float)WindowSize9.y / TextureSize9.y;     //Calculate scale.
	target9 = { x , y };
	sprite9.setTexture(tex9);
	sprite9.setPosition(0, 0);
	sprite9.setScale(ScaleX, ScaleY);
	sprite9.setOrigin(0, 0);
	s1.stop();
	s3.play3(2, true);
	auto player = makeEntity();
	player->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y / 2));
	auto s = player->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(10.0f);
	s->getShape().setFillColor(Color::Red);
	player->addComponent<BasicMovementComponent>();

	auto enemy = makeEntity();
	enemy->setPosition(Vector2f(250.0f, 250.0f));
	s = enemy->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(10.0f);
	s->getShape().setFillColor(Color::Blue);

	auto sm = enemy->addComponent<StateMachineComponent>();
	sm->addState("normal", make_shared<NormalState>(player));
	sm->addState("near", make_shared<NearState>(player));
	sm->changeState("normal");

}

void StateScene::UnLoad() { Scene::UnLoad(); }

void StateScene::Update(const double& dt)
{
	if (sf::Keyboard::isKeyPressed(Keyboard::R)) {
		UnLoad();
		Load();
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		s1.play1(0, true);
		Engine::ChangeScene(&menu);
	}
	Scene::Update(dt);
}

void StateScene::Render()
{
	Scene::Render();
}