//
// Created by niels on 22.04.17.
//

#ifndef LD38_RAINBOWTREE_H
#define LD38_RAINBOWTREE_H

#include "CPU/Common.h"
using namespace CPU;

#include "src/fw_decl.h"
#include "src/gamelogic/WorldObjectSingle.h"

class RainbowTree: public WorldObjectSingle {
    void upgradeBatch();
    int growthState;
    float water;
    constexpr static float DEHYDRATE = 0.01f;
public:
    RainbowTree(World* world);
    virtual void update(float delta);
    virtual void grow();
    virtual void consume();
    virtual ObjectType type() const;
    bool isGrown() const;
    bool canGrow() const;
    bool canDie() const;
    void die();
    void tryGrow();
    void tryDie();
    void receiveRain(float numWater);
};


#endif //LD38_RAINBOWTREE_H
