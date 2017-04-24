#ifndef Granny_h_INCLUDED
#define Granny_h_INCLUDED

#include "CPU/Common.h"
using namespace CPU;

#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/WorldObjectAction.h"

class Granny : public WorldObjectSingle {
	private:
	public:
		Granny(World* world);
		~Granny();
		virtual ObjectType type() const override;
		void update(float delta_time);
		void draw();
};

#endif // Granny_h_INCLUDED

