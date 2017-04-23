//
// Created by niels on 22.04.17.
//

#ifndef LD38_RAINBOWTREE_H
#define LD38_RAINBOWTREE_H

class World;

#include "CPU/Common.h"
using namespace CPU;

#include "src/gamelogic/WorldObjectSingle.h"

class RainbowTree: public WorldObjectSingle {
    void upgradeBatch();
    int growthState;
public:
    RainbowTree(World* world);
    virtual void grow();
    virtual void consume();
    virtual ObjectType type();
};


#endif //LD38_RAINBOWTREE_H
