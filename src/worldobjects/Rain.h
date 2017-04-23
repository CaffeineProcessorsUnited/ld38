//
// Created by bene on 23.04.17.
//

#ifndef LD38_RAIN_H
#define LD38_RAIN_H

#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/World.h"
#include <vector>

class Rain: public WorldObjectSingle {
protected:
    int spriteIndex;
    const static vector<string> sprites;
    constexpr static float fallSpeed = 3;

public:
    Rain(World *world);
    virtual ObjectType type() const;
    virtual void update(float delta_time);
};

#endif //LD38_RAIN_H
