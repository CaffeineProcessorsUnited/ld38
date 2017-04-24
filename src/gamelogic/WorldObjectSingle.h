//
// Created by niels on 22.04.17.
//

#ifndef LD38_WORLDOBJECTSINGLE_H
#define LD38_WORLDOBJECTSINGLE_H

#include "CPU/Common.h"
using namespace CPU;

#include "src/fw_decl.h"
#include "CPU/SpriteBatch.h"
#include "WorldObject.h"

class WorldObjectSingle: public WorldObject {
protected:
    float speed;
    CPU::SpriteBatch* _batch;
    string overlayText;
    CPU::SpriteBatch* overlayBackground;
public:
    WorldObjectSingle(World *world);
    virtual ~WorldObjectSingle();
    virtual void update(float time_delta);
    virtual void draw();
    virtual void drawOverlay();
    virtual void resize(unsigned int width, unsigned int height);
    virtual void setSpeed(float speed);
    virtual ObjectType type() const = 0;

    bool intersect(int x, int y) const;
    bool near(const WorldPos& pos, float dist) const;

    float getSpeed();
};

#endif //LD38_WORLDOBJECTSINGLE_H
