#include "src/gamelogic/UnicornAction.h"

UnicornAction::UnicornAction(WorldObject* object):WorldObjectAction(object){};

Unicorn* UnicornAction::getUnicorn() {
	return (Unicorn*) this->object;
}

UnicornActionWalk::UnicornActionWalk(WorldObject* object):UnicornAction(object) {
	cnt = 0;
	cooldown = 150;
	walkcycle = 100;
	wants_to_walk = true;
};

void UnicornActionWalk::doAction() {
	Unicorn* uni = this->getUnicorn();
	if(uni->getSpeed() == 0) {
		uniform_int_distribution<int> dist(70, 500);
		this->walkcycle = dist(this->generator);
		if(this->walkcycle%2) {
			uni->setSpeed(-0.1);
		} else {
			uni->setSpeed(0.1);
		}
	}
	cnt++;
}

float UnicornActionWalk::getPriority() {
	if(cnt>=this->walkcycle) {
    		cnt = this->cooldown;
		wants_to_walk = false;
	} else if (cnt <= 0) {
    		cnt = 0;
		wants_to_walk = true;
	}
	if(wants_to_walk) {
		return 1;
	}
	cnt--;
	return 0;
}

UnicornActionStop::UnicornActionStop(WorldObject* object):UnicornAction(object) {

}

void UnicornActionStop::doAction() {
	Unicorn* uni = this->getUnicorn();
	uni->setSpeed(0);
}

float UnicornActionStop::getPriority() {
	return 0.1;
}
