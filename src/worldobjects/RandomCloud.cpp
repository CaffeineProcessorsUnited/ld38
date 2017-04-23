#include <random>
using namespace std;

#include "RandomCloud.h"
#include "gameplay.h"
using namespace gameplay;

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
}

ObjectType RandomCloud::type() const {
    return ObjectType::CLOUD;
}