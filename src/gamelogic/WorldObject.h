#ifndef WorldObject_h_INCLUDED
#define WorldObject_h_INCLUDED

#include "CPU/Common.h"
using namespace CPU;


struct WorldPos {
    float rad;
    unsigned int zindex;
    float height;

    WorldPos(float rad, unsigned int zindex, float height) {
        this->rad = rad;
        this->zindex = zindex;
        this->height = height;
    }
};
class World;

#include "src/fw_decl.h"

class WorldObject {
protected:
    WorldObject(World *world);

    World *world;
public:
    virtual void resize(unsigned int width, unsigned int height) = 0;
    virtual void update(float time_delta) = 0;
    virtual void draw() = 0;
    virtual ObjectType type() const = 0;
    virtual bool intersect(int x, int y) const = 0;
    virtual bool near(const WorldPos& pos, float dist) const = 0;
    virtual void drawOverlay() = 0;

    WorldPos pos;
};

#endif // WorldObject_h_INCLUDED

