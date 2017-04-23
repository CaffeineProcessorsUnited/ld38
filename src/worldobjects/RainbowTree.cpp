//
// Created by niels on 22.04.17.
//

#include "RainbowTree.h"

#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/WorldObject.h"
#include "src/gamelogic/World.h"

RainbowTree::RainbowTree(World* world):
        WorldObjectSingle(world)
{
    batch = new CPU::SpriteBatch("@plantseed");
    batch->scale.set(20,20);
    growthState = 0;
    //grow();
    //grow();
    //grow();
}

void RainbowTree::grow(){
    if(this->growthState <= 2) {
        this->growthState += 1;
    }
    upgradeBatch();
}

void RainbowTree::consume(){
    if(this->growthState >= 1) {
        this->growthState -= 1;
    }
    upgradeBatch();
}

void RainbowTree::upgradeBatch() {
    if (batch != nullptr) {
        SAFE_DELETE(batch);
    }
    switch (growthState) {
        case 0:
            batch = new CPU::SpriteBatch("@plantseed");
            batch->scale.set(20, 20);
            break;
        case 1:
            batch = new CPU::SpriteBatch("@plantsmall");
            batch->scale.set(30, 30);
            break;
        case 2:
            batch = new CPU::SpriteBatch("@plantmedium");
            batch->scale.set(50, 50);
            break;
        case 3:
            batch = new CPU::SpriteBatch("@planttree");
            batch->scale.set(100, 100);
            break;
        default:
            batch = NULL;
            break;
    }
    batch->recreate();
}

ObjectType RainbowTree::type() const {
    return ObjectType::TREE;
}

bool RainbowTree::isGrown() const {
    return growthState == 3;
}

bool RainbowTree::canGrow() const {
    int hour = world->getHourOfDay();
    return !isGrown() && 8 <= hour && hour <= 18;
}
