//
// Created by bene on 23.04.17.
//

#include <random>
#include "src/worldobjects/Rain.h"

const vector<string> Rain::sprites = {"@rain1", "@rain2"};

Rain::Rain(World *world): WorldObjectSingle(world) {
    std::random_device generator;
    std::uniform_int_distribution<int> distributionIntSprite(0, Rain::sprites.size() - 1);

    spriteIndex = distributionIntSprite(generator);

    batch = new CPU::SpriteBatch(Rain::sprites[spriteIndex]);
    batch->scale.set(100, 50);


}

ObjectType Rain::type() {
    return ObjectType::RAIN;
}