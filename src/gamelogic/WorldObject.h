#ifndef src/gamelogic/WorldObject_h_INCLUDED
#define src/gamelogic/WorldObject_h_INCLUDED

#include "gameplay.h"

class WorldObject{
	protected:
    		WorldObject(World* world);
    		World* world;
    		Vector2 rad_lay_pos;
	public:
    		void update(float time_delta);
};

#endif // src/gamelogic/WorldObject_h_INCLUDED

