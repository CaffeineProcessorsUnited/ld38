#include <random>
#include <math.h>
using namespace std;

#include "gameplay.h"
using namespace gameplay;

#include "src/worldobjects/RandomStar.h"
#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/WorldObject.h"
#include "src/gamelogic/World.h"
#include "src/worldobjects/Unicorn.h"

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

    appearTod = distributionAppear(generator);
    disappearTod = distributionDisappear(generator);

    batch = new CPU::SpriteBatch(RandomStar::sprites[spriteIndex]);
    float scale = distributionScale(generator);
    batch->scale.set(scale, scale);
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
        flickerCounter++;
        if (isFlickering && flickerCounter > 5){
            isVisible = !isVisible;
            flickerCounter = 0;
        }
        else{
            isVisible = true;
        }

    }
}

void RandomStar::draw()
{
    if (isVisible)
    {
        WorldObjectSingle::draw();
    }
}
ObjectType RandomStar::type() const {
    return ObjectType::STAR;
}