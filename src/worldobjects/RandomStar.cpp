#include <random>
using namespace std;

#include "RandomStar.h"
#include "gameplay.h"
using namespace gameplay;

const vector<string> RandomStar::sprites = {"@star1", "@star2"};

RandomStar::RandomStar(World *world):
    WorldObjectSingle(world)
{
    std::random_device generator;
    std::uniform_real_distribution<float> distribution(minSpeed, maxSpeed);
    std::uniform_int_distribution<int> distributionIntSprite(0, RandomStar::sprites.size() - 1);
    std::uniform_int_distribution<int> distributionIntHeight(minHeight, maxHeight);
    std::uniform_real_distribution<float> distributionRad(0, 2*M_PI);
    speed = distribution(generator);
    spriteIndex = distributionIntSprite(generator);
    pos.height = distributionIntHeight(generator);
    pos.rad = distributionRad(generator);

    batch = new CPU::SpriteBatch(RandomStar::sprites[spriteIndex]);
    batch->scale.set(5, 5);
}