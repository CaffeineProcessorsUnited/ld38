#include "Granny.h"
#include "src/gamelogic/World.h"

using namespace gameplay;

Granny::Granny(World* world):
WorldObjectSingle(world) {
	speed = 0;

	_batch = new CPU::SpriteBatch("@granny");
	_batch->scale.set(100,100);
}

Granny::~Granny() {
	delete action_sel;
}

ObjectType Granny::type() const {
    return ObjectType::GRANNY;
}

void Granny::update(float delta_time) {
	WorldObjectSingle::update(delta_time);
}

void Granny::draw() {
	WorldObjectSingle::draw();
}

CPU::SpriteBatch* Granny::batch() {
    return _batch;
}