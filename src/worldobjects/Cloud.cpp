#include <random>
using namespace std;

#include "Cloud.h"
#include "gameplay.h"
using namespace gameplay;

Cloud::Cloud(World *world):
    WorldObjectSingle(world)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(minSpeed, maxSpeed);
    speed = distribution(generator);

    batch = new CPU::SpriteBatch("@cloud");
    batch->scale.set(16, 16);
}

ObjectType Cloud::type() {
    return ObjectType::CLOUD;
}