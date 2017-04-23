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

bool WorldObjectSingle::intersect(int x, int y) const {
    //Important: Assume rotation point is the center

    const float w = batch->scale.x;
    const float h = batch->scale.y;
    const float cX = batch->pos.x + w/2.f;
    const float cY = batch->pos.y + h/2.f;
    const float angle = batch->rotationRad;

    const Vector2 center(cX, cY);

    Vector2 posA(batch->pos.x+0, batch->pos.y+0);
    Vector2 posB(batch->pos.x+0, batch->pos.y+h);
    Vector2 posC(batch->pos.x+w, batch->pos.y+h);
    posA.rotate(center,angle);
    posB.rotate(center,angle);
    posC.rotate(center,angle);

    Vector2 mouse(x,y);

    Vector2 BA(posA.x-posB.x, posA.y-posB.y);
    Vector2 CA(posA.x-posC.x, posA.y-posC.y);
    Vector2 BM(x-posB.x, y-posB.y);
    Vector2 CM(x-posB.x, y-posB.y);
    float BABM = Vector2::dot(BA, BM);
    float BABA = Vector2::dot(BA, BA);
    float CACM = Vector2::dot(CA,CM);
    float CACA = Vector2::dot(CA,CA);

    return 0 <= BABM &&
            BABM <= BABA &&
            0 <= CACM &&
            CACM <= CACA;
}
