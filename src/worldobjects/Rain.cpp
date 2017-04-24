//
// Created by bene on 23.04.17.
//

#include <random>
#include "src/worldobjects/Rain.h"

const vector<string> Rain::sprites = {"@rain1"};

Rain::Rain(World *world) : WorldObjectSingle(world) {
    std::random_device generator;
    std::uniform_int_distribution<int> distributionIntSprite(0, Rain::sprites.size() - 1);

    spriteIndex = distributionIntSprite(generator);

    batch = new CPU::SpriteBatch(Rain::sprites[spriteIndex]);
    batch->scale.set(100, 50);
}

void Rain::update(float delta_time) {
    WorldObjectSingle::update(delta_time);
    pos.height -= delta_time * fallSpeed;
    if (pos.height <= 0) {
        world->receiveRain(pos);
        world->destroy(this);
    }
}

ObjectType Rain::type() const {
    return ObjectType::RAIN;
}