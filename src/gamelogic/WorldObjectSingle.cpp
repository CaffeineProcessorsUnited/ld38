#include <random>
using namespace std;


#include "WorldObjectSingle.h"
#include "src/gamelogic/WorldObject.h"
#include "src/gamelogic/World.h"
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

bool WorldObjectSingle::intersect(int x, int y) const {
    //Important: Assume rotation point is the center

    const float w = batch->scale.x;
    const float h = batch->scale.y;
    const float cX = batch->pos.x + w/2.f;
    const float cY = batch->pos.y + h/2.f;
    const float angle = batch->rotationRad;

    const Vector2 center(cX, cY);

    Vector2 posA(cX-w, cY-h);
    Vector2 posB(cX+w, cY-h);
    Vector2 posC(cX-w, cY+h);
    posA.rotate(center,angle);
    posB.rotate(center,angle);
    posC.rotate(center,angle);

    Vector2 AB(posB.x-posA.x, posB.y-posA.y);
    Vector2 AC(posC.x-posA.x, posC.y-posA.y);
    Vector2 AM(x-posA.x, y-posA.y);
    float ABAM = Vector2::dot(AB, AM);
    float ABAB = Vector2::dot(AB, AB);
    float ACAM = Vector2::dot(AC, AM);
    float ACAC = Vector2::dot(AC, AC);

    return 0 <= ABAM &&
            ABAM <= ABAB &&
            0 <= ACAM &&
            ACAM <= ACAC;
}

