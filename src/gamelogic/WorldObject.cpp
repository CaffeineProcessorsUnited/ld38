#include "src/gamelogic/WorldObject.h"
#include "src/gamelogic/World.h"

WorldObject::WorldObject(World *world):
    world(world),
    pos(0,0,0)
{
}