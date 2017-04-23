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
    std::normal_distribution<float> distributionScale(4, 1.5);
    std::uniform_int_distribution<int> flickerFactor(0, 100);

    if(flickerFactor(generator) < 6){
        isFlickering = true;
    } else{
        isFlickering = false;
    }

    isVisible = true;
    flickerCounter = 0;
    speed = distribution(generator);
    spriteIndex = distributionIntSprite(generator);
    pos.height = distributionIntHeight(generator);
    pos.rad = distributionRad(generator);

    batch = new CPU::SpriteBatch(RandomStar::sprites[spriteIndex]);
    float scale = distributionScale(generator);
    batch->scale.set(scale, scale);
}

void RandomStar::update(float delta_time)
{
    WorldObjectSingle::update(delta_time);
    flickerCounter++;
    if (isFlickering && flickerCounter > 5){
        isVisible = !isVisible;
        flickerCounter = 0;
    } else{
        isVisible = true;
    }
}

ObjectType RandomStar::type() const {
    return ObjectType::STAR;
}