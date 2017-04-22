#include <random>
using namespace std;


#include "WorldObjectSingle.h"
#include "World.h"
#include "gameplay.h"
using namespace gameplay;

WorldObjectSingle::WorldObjectSingle(World *world):
        WorldObject(world)
{
    speed = 0;
    batch = NULL;
}

WorldObjectSingle::~WorldObjectSingle(){
    if(batch != nullptr){
        SAFE_DELETE(batch);
    }
}

void WorldObjectSingle::update(float time_delta){
    if(batch == nullptr)
        return;

    pos.rad += (speed*time_delta);
    if(pos.rad > 2*M_PI){
        pos.rad -= 2*M_PI;
    } else if(pos.rad < -2*M_PI){
        pos.rad += 2*M_PI;
    }

    batch->pos = Vector3(world->offset().x + sin(pos.rad)*(World::RADIUS+pos.height),
                         world->offset().y + cos(pos.rad)*(World::RADIUS+pos.height),
                         pos.zindex);
    batch->rotationRad = - pos.rad;
}

void WorldObjectSingle::draw() {
    if(batch != nullptr)
        batch->draw();
}


void WorldObjectSingle::resize(unsigned int width, unsigned int height) {
    if(batch != nullptr)
        batch->recreate();
}

void WorldObjectSingle::setSpeed(float speed) {
    this->speed = speed;
}
