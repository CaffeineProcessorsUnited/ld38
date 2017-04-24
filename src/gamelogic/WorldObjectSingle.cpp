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
    overlayBackground = NULL;
    _batch = NULL;
}

WorldObjectSingle::~WorldObjectSingle(){
    if(_batch != nullptr){
        SAFE_DELETE(_batch);
    }
}

void WorldObjectSingle::update(float time_delta){
    if(_batch == nullptr)
        return;

    pos.rad += (speed*time_delta);
    if(pos.rad > 2*M_PI){
        pos.rad -= 2*M_PI;
    } else if(pos.rad < -2*M_PI){
        pos.rad += 2*M_PI;
    }

    _batch->pos = world->pos2vec(pos);
    _batch->rotationRad = - pos.rad;
}

void WorldObjectSingle::draw() {
    if(_batch != nullptr)
        _batch->draw();
}


void WorldObjectSingle::resize(unsigned int width, unsigned int height) {
    if(_batch != nullptr)
        _batch->recreate();
    if(overlayBackground != nullptr)
        overlayBackground->recreate();
}

void WorldObjectSingle::setSpeed(float speed) {
    this->speed = speed;
}

bool WorldObjectSingle::intersect(int x, int y) const {
    //Important: Assume rotation point is the center

    const float w = _batch->scale.x;
    const float h = _batch->scale.y;
    const float cX = _batch->pos.x + w/2.f;
    const float cY = _batch->pos.y + h/2.f;
    const float angle = _batch->rotationRad;

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

bool WorldObjectSingle::near(const WorldPos &pos, float dist) const {
    Vector3 r = world->pos2vec(pos);
    Vector3 r2 = world->pos2vec(this->pos);
    return r.distance(r2) < dist;
}

float WorldObjectSingle::getSpeed() {
	return this->speed;
}

void WorldObjectSingle::drawOverlay() {
    if(overlayBackground == nullptr){
        overlayBackground = new CPU::SpriteBatch("@white");
    }
    Font* font = world->activeFont();
    unsigned int w, h;
    font->measureText(overlayText.c_str(),font->getSize(), &w, &h);
    Vector3 vec = world->pos2vec(pos);

    int x = vec.x+max(20.f,batch->scale.x/2.f);
    int y = vec.y-max(20.f,batch->scale.y/2.f);

    overlayBackground->pos.set(x+w/2.f,y+h/2.f,1);
    overlayBackground->scale.set(w+10,h+10);
    overlayBackground->draw();

    font->drawText(overlayText.c_str(), x, y, Vector4(0, 0, 1, 1), font->getSize());
}
