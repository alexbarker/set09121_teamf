#include "add_entity.h"
#include "animation.h"
#include "steering.h"
#include "steering_states.h"
#include "steering_decisions.h"
#include "components/cmp_state_machine.h"
#include "components/cmp_path_follow.h"
#include "components/cmp_enemy_ai.h"
#include "components/cmp_decision_tree.h"
#include "components/cmp_ai_steering.h"
#include "components/cmp_basic_movement.h"
#include "components/cmp_actor_movement.h"
#include "components/cmp_sprite.h"
#include "system_resources.h"
#include "components/cmp_physics.h"
#include "components/cmp_player_physics.h"
#include <LevelSystem.h>
#include <SFML/Graphics/Transformable.hpp>

using namespace sf;
using namespace std;

std::shared_ptr<Entity> AddEntity::makePlayer(Scene* scene, const Vector2f& pos) {
	auto player = scene->makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->addTag("player");

	auto animation = player->addComponent<AnimationComponent>(Vector2f(46.f, 46.f));
	sf::Texture s = *Resources::load<Texture>("PlayerSpritesheet.png");
	animation->setSpritesheet(s);
	animation->setFrameCount(15);
	animation->setFrameTime(0.06f);

	player->addComponent<PlayerPhysicsComponent>(Vector2f(22.f, 17.f));

	return player;
}

std::shared_ptr<Entity> AddEntity::makeFakePlayer1(Scene* scene, const Vector2f& pos, const sf::Vector2f& distance, float time) {
	auto fakePlayer1 = scene->makeEntity();
	fakePlayer1->setPosition(pos);
	fakePlayer1->addTag("fakePlayer1");

	auto physics = fakePlayer1->addComponent<PhysicsComponent>(true, sf::Vector2f(46.f, 46.f));
	physics->impulse(sf::Vector2f(-7.5f, 0));
	physics->setMass(25000.f);

	auto animation = fakePlayer1->addComponent<AnimationComponent>(Vector2f(46.f, 46.f));
	sf::Texture s = *Resources::load<Texture>("PlayerSpritesheet.png");
	animation->setSpritesheet(s);
	animation->setFrameCount(15);
	animation->setFrameTime(0.07f);

	return fakePlayer1;
}

std::shared_ptr<Entity> AddEntity::makeFakePlayer2(Scene* scene, const Vector2f& pos, const sf::Vector2f& distance, float time) {
	auto makeFakePlayer2 = scene->makeEntity();
	makeFakePlayer2->setPosition(pos);
	makeFakePlayer2->addTag("fakePlayer2");

	auto physics = makeFakePlayer2->addComponent<PhysicsComponent>(true, sf::Vector2f(46.f, 46.f));
	physics->impulse(sf::Vector2f(7.5f, 0));
	physics->setMass(25000.f);

	auto animation = makeFakePlayer2->addComponent<AnimationComponent>(Vector2f(46.f, 46.f));
	sf::Texture s = *Resources::load<Texture>("PlayerSpritesheet.png");
	animation->setSpritesheet(s);
	animation->setFrameCount(15);
	animation->setFrameTime(0.07f);

	return makeFakePlayer2;
}

std::shared_ptr<Entity> AddEntity::makeTutorialPlayer(Scene* scene, const Vector2f& pos) {
	auto player = scene->makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->addTag("player");

	auto animation = player->addComponent<AnimationComponent>(Vector2f(46.f, 46.f));
	sf::Texture s = *Resources::load<Texture>("PlayerSpritesheet.png");
	animation->setSpritesheet(s);
	animation->setFrameCount(15);
	animation->setFrameTime(0.06f);

	player->addComponent<PlayerPhysicsComponent>(Vector2f(22.f, 17.f));

	return player;
}

void AddEntity::makeWalls(Scene* scene) {
	auto walls = ls::findTiles(ls::WALL);
	for (auto w : walls) {
		auto pos = ls::getTilePosition(w);
		pos += Vector2f(10.f, 10.f);
		auto e = scene->makeEntity();
		e->setPosition(pos);
		e->addComponent<PhysicsComponent>(false, Vector2f(20.f, 20.f));
	}
}

std::shared_ptr<Entity> AddEntity::makeSentinel(Scene* scene, const Vector2f& pos) {

		auto makeSentinel = scene->makeEntity();
		makeSentinel->setPosition(pos);
		auto s = makeSentinel->addComponent<ShapeComponent>();
		s->setShape<CircleShape>(10.0f);
		s->getShape().setFillColor(Color::Blue);

		auto x = scene->ents.find("player")[0];
		auto sm = makeSentinel->addComponent<StateMachineComponent>();
		//sm->addState("stationary", make_shared<StationaryState>());
		sm->addState("seek", make_shared<SeekState>(makeSentinel, x));
		//sm->addState("flee", make_shared<FleeState>(makeSentinel, x));

		auto decision = make_shared<DistanceDecision>(
			x,
			50.0f,
			make_shared<FleeDecision>(),
			make_shared<DistanceDecision>(
				x,
				100.0f,
				make_shared<RandomDecision>(
					make_shared<SeekDecision>(),
					make_shared<StationaryDecision>()),
				make_shared<SeekDecision>()
				)
			);

		makeSentinel->addComponent<DecisionTreeComponent>(decision);
		//makeSentinel->addComponent<ActorMovementComponent>();

		return makeSentinel;
	}
