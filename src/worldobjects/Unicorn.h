#ifndef Unicorn_h_INCLUDED
#define Unicorn_h_INCLUDED

#include "CPU/Common.h"
using namespace CPU;

#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/WorldObjectAction.h"
#include "src/gamelogic/UnicornAction.h"

class Unicorn : public WorldObjectSingle {
	private:
		ActionSelector* action_sel;
	public:
		constexpr static float maxSpeed = 0.1f;
		constexpr static int maxHunger = 100;
		constexpr static int maxThirst = 100;
		constexpr static int maxAge = 100;
		constexpr static float range = 1;

		int hunger;
		int thirst;
		int age;

		Unicorn(World* world);
		~Unicorn();
		void kill();
		virtual ObjectType type() const override;
		void update(float delta_time);
		void setOverlayText(string text);
		void draw();
};

#endif // Unicorn_h_INCLUDED

