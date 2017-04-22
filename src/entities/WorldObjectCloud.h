//
// Created by niels on 22.04.17.
//

#ifndef LD38_WORLDOBJECTCLOUD_H
#define LD38_WORLDOBJECTCLOUD_H

#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/World.h"

class WorldObjectCloud: public WorldObjectSingle {
protected:
    constexpr static float minSpeed = -0.5f;
    constexpr static float maxSpeed = 0.5f;
public:
    WorldObjectCloud(World *world);
};


#endif //LD38_WORLDOBJECTCLOUD_H
