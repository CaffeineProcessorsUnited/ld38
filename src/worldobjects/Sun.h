//
// Created by bene on 24.04.17.
//

#ifndef LD38_SUN_H
#define LD38_SUN_H

#include "src/gamelogic/WorldObjectSingle.h"

class Sun: public WorldObjectSingle {
public:
    Sun(World *world);
    virtual ObjectType type() const;
    virtual void update(float delta_time);
};

#endif //LD38_SUN_H
