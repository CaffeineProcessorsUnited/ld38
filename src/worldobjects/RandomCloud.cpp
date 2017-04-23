#include <random>
using namespace std;

#include "gameplay.h"
using namespace gameplay;

#include "src/worldobjects/RandomCloud.h"
#include "src/gamelogic/WorldObject.h"
#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/World.h"

const vector<string> RandomCloud::cloudSprites = {"@cloud", "@cloud2"};

RandomCloud::RandomCloud(World *world):
    WorldObjectSingle(world)
{
    std::random_device generator;
    std::uniform_real_distribution<float> distribution(minSpeed, maxSpeed);
    std::uniform_int_distribution<int> distributionIntSprite(0, RandomCloud::cloudSprites.size() - 1);
    std::uniform_int_distribution<int> distributionIntHeight(minHeight, maxHeight);
    std::uniform_real_distribution<float> distributionRad(0, 2*M_PI);
    speed = distribution(generator);
    spriteIndex = distributionIntSprite(generator);
    pos.height = distributionIntHeight(generator);
    pos.rad = distributionRad(generator);

    cout << pos.height << " " << pos.rad << endl;
    batch = new CPU::SpriteBatch(RandomCloud::cloudSprites[spriteIndex]);
    batch->scale.set(100, 50);

    rainAmount = 1; // TODO: maybe randomize?
    isRaining = false;
    rainTime = 0;
}

void RandomCloud::update(float delta_time) {
    WorldObjectSingle::update(delta_time);
    if (isRaining) {
        if(rainTime < rainDuration) {
            rainTime += delta_time;
        } else {
            isRaining = false;
        }
    }
}

void RandomCloud::draw() {
    WorldObjectSingle::draw();
    if (isRaining) {
        // TODO: Draw rain
    }
}

ObjectType RandomCloud::type() const {
    return ObjectType::CLOUD;
}

bool RandomCloud::canRain() {
    return canRain(1);
}

bool RandomCloud::canRain(int amount) {
    if (rainAmount - amount >= 0) {
        rainAmount -= amount;
        return true;
    }
    return false;
}

bool RandomCloud::doRain() {
    return doRain(1);
}

bool RandomCloud::doRain(int amount) {
    if (!canRain(amount)) {
        return false;
    }
    rainTime = 0;
    isRaining = true;
    return true;
}