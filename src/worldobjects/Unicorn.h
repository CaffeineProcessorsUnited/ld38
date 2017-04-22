#ifndef Unicorn_h_INCLUDED
#define Unicorn_h_INCLUDED

#include "src/gamelogic/WorldObjectSingle.h"

class Unicorn : public WorldObjectSingle {
	private:
		constexpr static float maxSpeed = 0.1f;
    	public:
		Unicorn(World* world);
		Unicorn(World* world, float rad, unsigned int zindex, float height);
};

#endif // Unicorn_h_INCLUDED

