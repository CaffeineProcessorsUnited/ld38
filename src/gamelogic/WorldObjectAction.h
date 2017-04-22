#ifndef WorldObjectAction_h_INCLUDED
#define WorldObjectAction_h_INCLUDED

#include "src/gamelogic/WorldObject.h"
#include <random>

class WorldObjectAction {
	protected:
		WorldObject* object;
    	public:
        	const float indiffernece_offset = 0.05f;

        	WorldObjectAction(WorldObject* object);
        	virtual void doAction() = 0;
        	virtual float getPriority() = 0;
};

#endif // WorldObjectAction_h_INCLUDED

