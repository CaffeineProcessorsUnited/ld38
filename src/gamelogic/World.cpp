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
    background->update(time_delta);
    batch->pos.set(_offset.x, _offset.y, 1);
    batch2->pos.set(_offset.x, _offset.y, 1);
    batch3->pos.set(_offset.x, _offset.y, 1);
    batch->rotationRad += SPEED * time_delta;
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

Vector2 World::offset() {
    return _offset;
}