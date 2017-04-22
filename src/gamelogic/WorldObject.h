#ifndef WorldObject_h_INCLUDED
#define WorldObject_h_INCLUDED

#ifndef World_h_INCLUDED
class WorldObject;
#include "World.h"
#endif


struct WorldPos {
    float rad;
    unsigned int layer;
};

class WorldObject {
protected:
    WorldObject(World *world);

    World *world;
public:
    WorldPos pos;
    virtual void update(float time_delta) = 0;
    virtual void draw() = 0;

};

#endif // WorldObject_h_INCLUDED

