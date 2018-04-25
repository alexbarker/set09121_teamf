#include "add_entity.h"
#include "animation.h"
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
	//player->setPosition(pos);
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