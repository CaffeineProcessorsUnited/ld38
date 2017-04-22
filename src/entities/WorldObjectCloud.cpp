#include <random>
using namespace std;

#include "WorldObjectCloud.h"
#include "gameplay.h"
using namespace gameplay;

WorldObjectCloud::WorldObjectCloud(World *world):
    WorldObjectSingle(world)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(minSpeed, maxSpeed);
    speed = distribution(generator);

    batch = new CPU::SpriteBatch("@cloud");
    batch->scale.set(16, 16);
}