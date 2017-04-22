#include "World.h"

float World::RADIUS = 512;

World::World():
    resources(),
    objects()
{
    batch = new CPU::SpriteBatch("@world");
    batch->scale.set(2*RADIUS, 2*RADIUS);
    batch->rotationPoint.set(0.5, 0.5);

    batch2 = new CPU::SpriteBatch("@image");
    batch2->scale.set(4,4);

    batch3 = new CPU::SpriteBatch("@circle");

    background = new Background(this);

    size.set(Game::getInstance()->getWidth(), Game::getInstance()->getHeight());
    dragStart = Vector2::zero();
    rotateV = 0;
}

World::~World() {
    resources.clear();
    objects.clear();
}

vector<WorldResource *> & World::getResources() {
    return resources;
}
vector<WorldObject *> & World::getObjects() {
    return objects;
}

void World::update(float time_delta) {
    if (fabs(rotateV) > 0.000005) {
        cout << rotateV << endl;
        batch->rotationRad += rotateV * time_delta;
        rotateV *= 0.85;
    }
    background->update(time_delta);
    batch->pos.set(_offset.x, _offset.y, 1);
    batch2->pos.set(_offset.x, _offset.y, 1);
    batch3->pos.set(_offset.x, _offset.y, 1);
    for(WorldObject *obj: objects){
        obj->update(time_delta);
    }
}
void World::draw() {
    background->draw();
    batch->draw();
    batch2->draw();
    batch3->draw();
    for(WorldObject *obj: objects){
        obj->draw();
    }
}

void World::resize(unsigned int width, unsigned int height) {
    size.set(width, height);
    float w = max(size.x - 400,500.f);
    float h = max(size.x - 0.5f*sqrt(4*size.x*size.x - w*w),height/3.f);
    _offset.x = size.x/2.f;
    _offset.y = 1.5f*height-h;
    background->resize(size.x, size.y);
    for(WorldObject *obj: objects){
        obj->resize(size.x, size.y);
    }

    cout << w << " " << h << " " << width << " " << height << " " << _offset.y << endl;

    RADIUS = w/2.f;
    batch->recreate();
    batch->scale.set(w,w);
    batch->rotationPoint.set(0.5, 0.5);
}

void World::rotate(float rad) {
    batch->rotationRad += rad;
}

void World::touchPress(int x, int y, unsigned int contactIndex) {
    dragStart.set(x, y);
}

void World::touchRelease(int x, int y, unsigned int contactIndex) {
    cout << "release" << endl;
    //rotate(-rotateV);
}

void World::touchMove(int x, int y, unsigned int contactIndex) {
    a = Vector3(dragStart.x - _offset.x, dragStart.y - _offset.y, 0);
    b = Vector3((float) x - _offset.x, (float) y - _offset.y, 0);
    n = Vector3(a);
    n.cross(b);
    rotateV += n.z / 3600 * SPEED;
    cout << rotateV << endl;
    //rotate(rotateV);
    dragStart.set(x, y);
    /*
        cout << Vector2::angle(a, b) << Vector2::angle(a, b) * SPEED << endl;
        c = a.dot(b);
        cout << a.x << "," << a.y << " " << b.x << "," << b.y << " " << c << " " << acos(c) * SPEED << endl;
        rotate(Vector2::angle(a, b) * SPEED);
        dragStart.set(x, y);
    } else {
        dragStart.set(dragStart.x + dA, dragStart.y + dB);
    }*/
}

Vector2 World::offset() {
    return _offset;
}