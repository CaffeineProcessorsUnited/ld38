//
// Created by bene on 24.04.17.
//

#include "Sun.h"

#include "src/gamelogic/World.h"

Sun::Sun(World *world) : WorldObjectSingle(world) {
    _batch = new CPU::SpriteBatch("@sun");
    speed = 0;
}

ObjectType Sun::type() const {
    return ObjectType::SUN;
}

void Sun::update(float time_delta) {

}