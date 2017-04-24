#ifndef Unicorn_h_INCLUDED
#define Unicorn_h_INCLUDED

#include "CPU/Common.h"
using namespace CPU;

#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/WorldObjectAction.h"
#include "src/gamelogic/UnicornAction.h"

class Unicorn : public WorldObjectSingle {
	private:
		constexpr static float maxSpeed = 0.1f;
		ActionSelector* action_sel;
	public:
		Unicorn(World* world);
		~Unicorn();
		virtual ObjectType type() const override;
		void update(float delta_time);
		void draw();
};

#endif // Unicorn_h_INCLUDED

