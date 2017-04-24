#include "Unicorn.h"
#include "gameplay.h"
#include <math.h>
#include "src/gamelogic/World.h"

using namespace gameplay;

Unicorn::Unicorn(World* world):
WorldObjectSingle(world) {
	action_sel = new ActionSelector();
	speed = 0;
	hunger = 0;
	thirst = 0;
	age = 0;

	action_sel->addAction(new UnicornActionWalk(this));
	action_sel->addAction(new UnicornActionStop(this));
	action_sel->addAction(new UnicornActionDie(this));
	action_sel->addAction(new UnicornActionEat(this));

	_batch = new CPU::SpriteBatch("@unicorn");
	_batch->scale.set(90,90);
}

Unicorn::~Unicorn() {
	delete action_sel;
}

ObjectType Unicorn::type() const {
	return ObjectType::UNICORN;
}

void Unicorn::update(float delta_time) {
	overlayText = "thinking...";

	WorldObjectSingle::update(delta_time);
	action_sel->doAction();
	if (speed != 0) {
	    _batch->scale.set(sgn(speed) * abs(_batch->scale.x), _batch->scale.y);
	}
	cout << "I'm " << (world->isVisible(pos.rad) ? "" : "not ") << "visible" << endl;
	hunger++;
}

void Unicorn::draw() {
	WorldObjectSingle::draw();
}

void Unicorn::kill() {
	world->destroy(this);
}

void Unicorn::setOverlayText(string text) {
	this->overlayText = text;
}

World* Unicorn::getWorld() {
	return world;
}

