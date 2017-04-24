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
    water = 50;
    upgradeBatch();
}

void RainbowTree::grow(){
    if(this->growthState <= 2) {
        this->growthState += 1;

        if(growthState == 3){
            std::random_device generator;
            std::uniform_int_distribution<int> seedDist(0,100);
            int numseeds = seedDist(generator);
            if(numseeds < 60) {
                world->receiveSeeds(1);
            } else if(numseeds < 90){
                world->receiveSeeds(2);
            } else {
                world->receiveSeeds(3);
            }
        }
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
    return !isGrown() && 8 <= hour && hour <= 18 && water > 10;
}

void RainbowTree::update(float delta) {
    WorldObjectSingle::update(delta);

    water -= DEHYDRATE;
    cout << "water " << water <<endl;

    tryGrow();
    tryDie();
}

void RainbowTree::receiveRain(float numWater) {
    water = min(water+numWater,99.f);
}

bool RainbowTree::canDie() const {
    return water < 10;
}

void RainbowTree::tryGrow() {
    if(canGrow()){
        std::random_device generator;
        std::uniform_real_distribution<float> grow_dist(0,1000.f/(10.f-water/10.f+MATH_FLOAT_SMALL));
        float num = grow_dist(generator);

        if(num < 1){
            grow();
        }
    }
}

void RainbowTree::tryDie() {
    if(canDie()){
        if(water < 0){
            die();
        }

        std::random_device generator;
        std::uniform_real_distribution<float> grow_dist(0,1000.f/(water/10.f+MATH_FLOAT_SMALL));
        float num = grow_dist(generator);

        if(num < 1){

            die();
        }
    }
}

void RainbowTree::die() {
    world->destroy(this);
}
