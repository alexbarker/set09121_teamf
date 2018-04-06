#include "scene_decision.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_basic_movement.h"
#include "../components/cmp_state_machine.h"
#include "../steering_states.h"
#include "../steering_decisions.h"
#include <LevelSystem.h>
#include <random>
#include <chrono>
#include <SFML/Audio.hpp>
#include "../components/cmp_music.h"
#include "scene_splash.h"
#include "../game.h"
#include "system_renderer.h"
#include <system_resources.h>

using namespace std;
using namespace std::chrono;
using namespace sf;

MusicPlayer s2;
sf::Sprite sprite4;
sf::Texture tex4;
Vector2f target4;
sf::Vector2u TextureSize4;  //Added to store texture size.
sf::Vector2u WindowSize4;   //Added to store window size.

void DecisionScene::SetBackground() {
	tex4 = *Resources::load<Texture>("main1.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	TextureSize4 = tex4.getSize(); //Get size of texture.
	WindowSize4 = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)WindowSize4.x / TextureSize4.x;
	float ScaleY = (float)WindowSize4.y / TextureSize4.y;     //Calculate scale.
	target4 = { x , y };
	sprite4.setTexture(tex4);
	sprite4.setPosition(0, 0);
	sprite4.setScale(ScaleX, ScaleY);
	sprite4.setOrigin(0, 0);
}

void DecisionScene::Load()
{
	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	//cout << "(a" << x2 << "-" << y2 << ")";
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();
	SetBackground();

	s1.stop();
	s2.play2(1, true);
	auto player = makeEntity();
	player->addTag("player");
	player->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y / 2));
	auto s = player->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(20.0f);
	s->getShape().setFillColor(Color::Blue);
	player->addComponent<BasicMovementComponent>();

	random_device dev;
	default_random_engine engine(dev());
	uniform_real_distribution<float> x_dist(0, Engine::GetWindow().getSize().x);
	uniform_real_distribution<float> y_dist(0, Engine::GetWindow().getSize().y);

	for (size_t n = 0; n < 100; ++n)
	{
		auto enemy = makeEntity();
		enemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
		auto s = enemy->addComponent<ShapeComponent>();
		s->setShape<CircleShape>(10.0f);
		s->getShape().setFillColor(Color::Blue);

		auto sm = enemy->addComponent<StateMachineComponent>();
		sm->addState("stationary", make_shared<StationaryState>());
		sm->addState("seek", make_shared<SeekState>(enemy, player));
		sm->addState("flee", make_shared<FleeState>(enemy, player));

		auto decision = make_shared<DistanceDecision>(
			player,
			50.0f,
			make_shared<FleeDecision>(),
			make_shared<DistanceDecision>(
				player,
				100.0f,
				make_shared<RandomDecision>(
					make_shared<SeekDecision>(),
					make_shared<StationaryDecision>()),
				make_shared<SeekDecision>()
				)
			);
		enemy->addComponent<DecisionTreeComponent>(decision);
	}
}

void DecisionScene::UnLoad() { 
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	Scene::UnLoad(); }

void DecisionScene::Update(const double& dt) { 
	Event event;
	while (Engine::GetWindow().pollEvent(event)) {
		if (event.type == sf::Event::Resized) {
			UnLoad();
			Engine::GetWindow().setSize(sf::Vector2u(event.size.width, event.size.height));
			Engine::GetWindow().display();	
			Load();
		}
	}
	Scene::Update(dt);	

	if (sf::Keyboard::isKeyPressed(Keyboard::R)) {
		UnLoad();
		Load();
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		s1.play1(0, true);
		Engine::ChangeScene(&menu);
	}	
}

void DecisionScene::Render() { 
	Renderer::queue(&sprite4);
	Scene::Render(); }
