#ifndef UnicornAction_h_INCLUDED
#define UnicornAction_h_INCLUDED

#include "src/gamelogic/WorldObjectAction.h"
#include "src/gamelogic/ActionSelector.h"
#include "src/worldobjects/Unicorn.h"
#include <random>
#include <math.h>

class UnicornAction : public WorldObjectAction {
	protected:
		Unicorn* getUnicorn();
		random_device generator;
	public:
		UnicornAction(WorldObject* object);

		virtual void doAction() = 0;
		virtual float getPriority() = 0;
};

class UnicornActionWalk : public UnicornAction {
	private:
		int cnt;
		int cooldown;
		int walkcycle;
		bool wants_to_walk;
	public:
		UnicornActionWalk(WorldObject* object);
		void doAction();
		float getPriority();
};

class UnicornActionStop: public UnicornAction {
	public:
		UnicornActionStop(WorldObject* object);
		void doAction();
		float getPriority();
};

class UnicornActionDie: public UnicornAction {
	public:
		UnicornActionDie(WorldObject* object);
		void doAction();
		float getPriority();
};

class UnicornActionEat: public UnicornAction {
	private:
		constexpr static float maxprio = 10;
    		constexpr static int hungerstep = 10;
    		RainbowTree* food;
	public:
		UnicornActionEat(WorldObject* object);
		void doAction();
		float getPriority();
};
#endif // UnicornAction_h_INCLUDED

