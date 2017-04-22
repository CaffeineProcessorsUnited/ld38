#include <random>
using namespace std;

#include "WorldObjectCloud.h"
#include "gameplay.h"
using namespace gameplay;

WorldObjectCloud::WorldObjectCloud(World *world):
        WorldObject(world)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(minSpeed, maxSpeed);
    speed = distribution(generator);

    batch = new CPU::SpriteBatch("@cloud");
    batch->scale.set(16, 16);
}

void WorldObjectCloud::update(float time_delta){
    pos.rad += (speed*time_delta);
    batch->pos = Vector3(world->offset().x + sin(pos.rad)*(World::RADIUS+pos.height),
                         world->offset().y + cos(pos.rad)*(World::RADIUS+pos.height),
                         pos.zindex);
    batch->rotationPoint.x = 0.5;
    batch->rotationPoint.y = 0;
    batch->rotationRad = -pos.rad;
}

void WorldObjectCloud::draw() {
    batch->draw();
}


void WorldObjectCloud::resize(unsigned int width, unsigned int height) {
    batch->recreate();
}