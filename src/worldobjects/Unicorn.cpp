#include "Unicorn.h"
#include "gameplay.h"

using namespace gameplay;

Unicorn::Unicorn(World* world):
WorldObjectSingle(world) {
	speed = 0;

	batch = new CPU::SpriteBatch("@unicorn");
	batch->scale.set(100,100);
}

Unicorn::Unicorn(World* world, float rad, unsigned int zindex, float height)
:Unicorn(world) 
{
	pos = WorldPos(rad, zindex, height);
}


ObjectType Unicorn::type() {
    return ObjectType::UNICORN;
}