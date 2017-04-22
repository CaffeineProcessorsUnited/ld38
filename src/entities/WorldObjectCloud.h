//
// Created by niels on 22.04.17.
//

#ifndef LD38_WORLDOBJECTCLOUD_H
#define LD38_WORLDOBJECTCLOUD_H

#include "src/gamelogic/WorldObject.h"

#include "CPU/SpriteBatch.h"

class WorldObjectCloud: public WorldObject {
protected:
    constexpr static float minSpeed = -0.5f;
    constexpr static float maxSpeed = 0.5f;
    float speed;
    CPU::SpriteBatch* batch;
public:
    WorldObjectCloud(World *world);
    virtual void update(float time_delta) override;
    virtual void draw() override;

};


#endif //LD38_WORLDOBJECTCLOUD_H
