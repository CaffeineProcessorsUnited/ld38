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
		int hunger_cnt;
		float lasttime; 
	public:
		constexpr static float maxSpeed = 0.1f;
		constexpr static int maxHunger = 100;
		constexpr static int hungerStep = 50;
		constexpr static int maxAge = 365;
		constexpr static float range = 0.5;

        float lastBreed;
		int hunger;
		int thirst;
		int age;
        bool canBreed;

		Unicorn(World* world);
		~Unicorn();
		void kill();
		virtual ObjectType type() const override;
		void update(float delta_time);
		void setOverlayText(string text);
		void draw();
		World* getWorld();
};

#endif // Unicorn_h_INCLUDED

