//
// Created by niels on 22.04.17.
//

#ifndef LD38_WORLDOBJECTSINGLE_H
#define LD38_WORLDOBJECTSINGLE_H

#include "src/fw_decl.h"
#include "src/gamelogic/WorldObject.h"
#include "CPU/SpriteBatch.h"

class WorldObjectSingle: public WorldObject {
protected:
    float speed;
    CPU::SpriteBatch* batch;
public:
    WorldObjectSingle(World *world);
    virtual ~WorldObjectSingle();
    virtual void update(float time_delta);
    virtual void draw();
    virtual void resize(unsigned int width, unsigned int height);
    virtual void setSpeed(float speed);

    bool intersect(int x, int y) const override;
};

#endif //LD38_WORLDOBJECTSINGLE_H
