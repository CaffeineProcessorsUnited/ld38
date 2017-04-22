#include "src/gamelogic/ActionSelector.h"

ActionSelector::ActionSelector() {
	actions = new vector<WorldObjectAction*>();
	eqActions = new vector<WorldObjectAction*>();
}

ActionSelector::~ActionSelector() {
        for(WorldObjectAction* ac: *eqActions) {
		delete ac;
        }
        for(WorldObjectAction* ac: *actions) {
		delete ac;
        }
	delete actions;
	delete eqActions;
}

void ActionSelector::addAction(WorldObjectAction* action) {
	actions->push_back(action);
}

void ActionSelector::doAction() {
	float maxprio = 0;
	for(WorldObjectAction* ac: *actions) {
		float diff = maxprio - ac->getPriority();
		if (diff > indiffernece_offset) {
			continue;
		} else if (diff < (-1*indiffernece_offset)) {
    			eqActions->clear();
			maxprio += diff;
			eqActions->push_back(ac);
		} else {
			eqActions->push_back(ac);
    		}
	}
	if (eqActions->size() == 1) {
		eqActions->at(0)->doAction();
	} else {
		uniform_int_distribution<int> selac(0,eqActions->size());
		eqActions->at(selac(generator))->doAction();
	}
}
