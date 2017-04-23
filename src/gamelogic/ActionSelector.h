#ifndef ActionSelector_h_INCLUDED
#define ActionSelector_h_INCLUDED

#include <vector>
#include <random>
#include "src/gamelogic/WorldObjectAction.h"

using namespace std;

class ActionSelector{
	private:
		vector<WorldObjectAction*>* eqActions;
		vector<WorldObjectAction*>* actions;
		random_device generator;
    	public:
        	const float indiffernece_offset = 0.05f;

        	ActionSelector();
        	~ActionSelector();
        	void addAction(WorldObjectAction* action);
        	void doAction();
};

#endif // ActionSelector_h_INCLUDED

