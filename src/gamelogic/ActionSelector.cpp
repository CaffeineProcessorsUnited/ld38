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
	int cnt = 0;
	for(WorldObjectAction* ac: *actions) {
    		float prio = ac->getPriority();
		if (maxprio > prio) {
			continue;
		} else if(maxprio < prio) {
    			eqActions->clear();
			maxprio = prio;
			eqActions->push_back(ac);
			cnt = 1;
		} else {
			eqActions->push_back(ac);
			cnt++;
    		}
	}
	if (eqActions->size() == 1) {
		eqActions->at(0)->doAction();
	} else {
		uniform_int_distribution<int> selac(0,cnt);
		eqActions->at(selac(generator))->doAction();
	}
}
