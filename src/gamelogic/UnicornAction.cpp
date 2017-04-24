#include "src/gamelogic/UnicornAction.h"
#include "src/worldobjects/RainbowTree.h"
#include "src/gamelogic/World.h"

UnicornAction::UnicornAction(WorldObject* object):WorldObjectAction(object){}

Unicorn* UnicornAction::getUnicorn() {
	return (Unicorn*) this->object;
}

UnicornActionWalk::UnicornActionWalk(WorldObject* object):UnicornAction(object) {
	cnt = 0;
	cooldown = 150;
	walkcycle = 100;
	wants_to_walk = true;
}

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
	if(cnt>=this->walkcycle && wants_to_walk) {
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

UnicornActionStop::UnicornActionStop(WorldObject* object):UnicornAction(object) {}

void UnicornActionStop::doAction() {
	Unicorn* uni = this->getUnicorn();
	uni->setSpeed(0);
}

float UnicornActionStop::getPriority() {
	return 0.1;
}

UnicornActionDie::UnicornActionDie(WorldObject* object):UnicornAction(object) {
	hunger_cnt = 0;
}

void UnicornActionDie::doAction() {
	this->getUnicorn()->kill();
}

float UnicornActionDie::getPriority() {
	Unicorn* uni = this->getUnicorn();
	if (uni->hunger > uni->maxHunger) {
		hunger_cnt++;
	} else {
		hunger_cnt = 0;
	}
	if (uni->age > uni->maxAge || hunger_cnt == hungerDeathDelay) {
		return 100;
	}
	return 0;
}

UnicornActionEat::UnicornActionEat(WorldObject* object):UnicornAction(object) {
	food = nullptr;
}

void UnicornActionEat::doAction() {
	Unicorn* uni = this->getUnicorn();
	uni->setOverlayText("Going to eat something");
	if (abs(food->pos.rad - uni->pos.rad) > 0.1 ) {
		uni->setSpeed(sgn(food->pos.rad - uni->pos.rad) * uni->maxSpeed);
	} else if (food->isGrown()) {
		food->consume();
		uni->hunger -= this->hungerstep;
		this->food = nullptr;
	} else {
		this->food = nullptr;
	}
}

float UnicornActionEat::getPriority() {
	if (this->food != nullptr) {
		if (food->isGrown()) {
			return this->maxprio;
		} else {
			this->food = nullptr;
		}
	}
	Unicorn* uni = this->getUnicorn();
	if (uni->hunger >= hungerstep) {
		vector<WorldObject*>& objects = uni->getWorld()->getObjects();
		for(WorldObject* object: objects){
			RainbowTree* tree = dynamic_cast<RainbowTree*>(object);
			if (tree != nullptr) {
				if ( abs(tree->pos.rad - uni->pos.rad) < uni->range) {
    					if (tree->isGrown()) {
						this->food = tree;
						return this->maxprio;
    					}
				}
			}
		}

	}
	return 0;
}

UnicornActionReproduce::UnicornActionReproduce(WorldObject* object):UnicornAction(object) {
    partner = nullptr;
}

void UnicornActionReproduce::doAction() {
    Unicorn* uni = this->getUnicorn();
    if(partner != nullptr && uni->canBreed && partner->canBreed){
        std::uniform_int_distribution<int> breedChance(0,100);
        if (breedChance(generator) < 10){
            uni->setOverlayText("Where do small Unicorns come from?");
            uni->lastBreed = 0;
            partner->lastBreed = 0;
            uni->hunger += 20;
            partner->hunger += 20;
            uni->getWorld()->spawn<Unicorn>();
            cout << "new unicörn" << endl;
            partner->canBreed = false;
            partner = nullptr;
            uni->canBreed = false;

        }






    }

}

float UnicornActionReproduce::getPriority() {
    if (this->partner != nullptr) {

        return this->maxprio;
    }

    Unicorn* uni = this->getUnicorn();
    uni->canBreed = (uni->hunger <= maxHunger && uni->age >= minAge && uni->age <= maxAge && uni->lastBreed >= breedCooldown);
    if(uni->canBreed){
        vector<WorldObject*>& objects = uni->getWorld()->getObjects();
        for(WorldObject* object: objects){
            Unicorn* uni2 = dynamic_cast<Unicorn*>(object);
            if (uni2 != nullptr) {
                if ( abs(uni2->pos.rad - uni->pos.rad) < uni->range) {
                    if (uni2->canBreed) {
                        this->partner = uni2;
                        return this->maxprio;
                    }
                }
            }
        }

    }
    return 0;
}
