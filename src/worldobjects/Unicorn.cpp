#include "Unicorn.h"
#include "gameplay.h"
#include <math.h>

using namespace gameplay;

Unicorn::Unicorn(World* world):
WorldObjectSingle(world) {
	action_sel = new ActionSelector();
	speed = 0;

	action_sel->addAction(new UnicornActionWalk(this));
	action_sel->addAction(new UnicornActionStop(this));

	batch = new CPU::SpriteBatch("@unicorn");
	batch->scale.set(100,100);
}

Unicorn::~Unicorn() {
	delete action_sel;
}

ObjectType Unicorn::type() const {
	return ObjectType::UNICORN;
}

void Unicorn::update(float delta_time) {
	WorldObjectSingle::update(delta_time);
	if(this->speed < 0) {
		batch->scale.set(std::fabs(batch->scale.x)*-1,batch->scale.y);
	} else if(this->speed == 0) {
		batch->scale.set(batch->scale.x,batch->scale.y);
	} else {
		batch->scale.set(std::fabs(batch->scale.x),batch->scale.y);
	}
	action_sel->doAction();
}
