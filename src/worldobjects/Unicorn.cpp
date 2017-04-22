#include "Unicorn.h"

Unicorn::Unicorn(World* world)
:WorldObjectSingle(world) {

}

Unicorn::Unicorn(World* world, float rad, unsigned int zindex, float height)
:Unicorn(world), pos(rad, zindex, height)
{
}
