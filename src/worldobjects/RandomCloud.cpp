#include <random>
using namespace std;

#include "gameplay.h"
using namespace gameplay;

#include "src/worldobjects/RandomCloud.h"
#include "src/gamelogic/WorldObject.h"
#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/World.h"
#include "src/worldobjects/Rain.h"

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
    _batch = new CPU::SpriteBatch(RandomCloud::cloudSprites[spriteIndex]);
    _batch->scale.set(100, 50);

    rainAmount = 20;
    isRaining = false;
    rainTime = 0;
    myRain = NULL;
    mustDie = false;
}

void RandomCloud::update(float delta_time) {
    WorldObjectSingle::update(delta_time);

    overlayText = "water: "+to_string(rainAmount);


    if (isRaining) {
        if (myRain != nullptr){
            if (pos.height - myRain->pos.height > 100){
                spawnRaindrop();
            }
        }
        else {
            spawnRaindrop();
        }

        if(rainTime < rainDuration) {
            rainTime += delta_time;
        } else {
            isRaining = false;
        }
    } else {
        myRain = nullptr;
    }

    if(!isRaining && rainAmount <= 0) {
        cout << "DIEDIEDIE" << endl;
        world->destroy(this);
    }

    forceRainOnGrouping();
}

void RandomCloud::forceRainOnGrouping() const {
    vector<WorldObject*>& objects = world->getObjects();
    return;

    int count = 0;
    for(WorldObject* object: objects){
        RandomCloud* cloud = dynamic_cast<RandomCloud*>(object);
        if(cloud != nullptr){
            if(abs(cloud->pos.rad - pos.rad) < 0.1){
                count++;
            }
        }
    }
    if(count > 1) {
        for(WorldObject* object: objects){
            RandomCloud* cloud = dynamic_cast<RandomCloud*>(object);
            if(cloud != nullptr){
                if(abs(cloud->pos.rad - pos.rad) < 0.1){
                    cloud->doRain(10);
                }
            }
        }
    }
}

void RandomCloud::draw() {
    WorldObjectSingle::draw();
}

void RandomCloud::spawnRaindrop() {
    myRain = world->spawn<Rain>();
    myRain->pos = pos;
    //myRain->setSpeed(speed);
    myRain->pos.height = pos.height - 50;
}

ObjectType RandomCloud::type() const {
    return ObjectType::CLOUD;
}

bool RandomCloud::canRain() {
    return canRain(1);
}

bool RandomCloud::canRain(int amount) {
    return (rainAmount - amount >= 0);
}

bool RandomCloud::doRain() {
    return doRain(1);
}

bool RandomCloud::doRain(int amount) {
    if (!canRain(amount)) {
        return false;
    }
    rainAmount -= amount;
    rainTime = 0;
    isRaining = true;
    return true;
}