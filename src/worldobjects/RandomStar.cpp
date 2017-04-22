#include <random>
#include <math.h>

using namespace std;

#include "RandomStar.h"
#include "gameplay.h"
using namespace gameplay;

const vector<string> RandomStar::sprites = {"@star1"};

RandomStar::RandomStar(World *world):
    WorldObjectSingle(world)
{
    std::random_device generator;
    std::uniform_real_distribution<float> distribution(minSpeed, maxSpeed);
    std::uniform_int_distribution<int> distributionIntSprite(0, RandomStar::sprites.size() - 1);
    std::uniform_int_distribution<int> distributionIntHeight(minHeight, maxHeight);
    std::uniform_real_distribution<float> distributionRad(0, 2*M_PI);
    std::normal_distribution<float> distributionAppear(midAppearTod, deviateAppear);
    std::normal_distribution<float> distributionDisappear(midDisappearTod, deviateDisappear);

    isVisible = true;

    speed = distribution(generator);
    spriteIndex = distributionIntSprite(generator);
    pos.height = distributionIntHeight(generator);
    pos.rad = distributionRad(generator);

    appearTod = distributionAppear(generator);
    disappearTod = distributionDisappear(generator);

    batch = new CPU::SpriteBatch(RandomStar::sprites[spriteIndex]);
    batch->scale.set(4, 4);
}

void RandomStar::update(float delta_time)
{
    WorldObjectSingle::update(delta_time);
    if (world->getHourOfDay() >= disappearTod && world->getHourOfDay() < appearTod)
    {
        isVisible = false;
    }
    else
    {
        isVisible = true;
    }
}

void RandomStar::draw()
{
    if (isVisible)
    {
        WorldObjectSingle::draw();
    }
}