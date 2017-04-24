#include "Unicorn.h"
#include "src/gamelogic/World.h"

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
	action_sel->doAction();
    cout << "I'm " << (world->isVisible(pos.rad) ? "" : "not ") << "visible" << endl;
}

void Unicorn::draw() {
    if (speed != 0) {
        batch->scale.set(sgn(speed) * abs(batch->scale.x), batch->scale.y);
    }
	WorldObjectSingle::draw();
}
