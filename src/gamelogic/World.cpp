#include "World.h"

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
    batch->pos.set(_offset.x, _offset.y, 1);
    batch2->pos.set(_offset.x, _offset.y, 1);
    batch3->pos.set(_offset.x, _offset.y, 1);
    batch->rotationRad += SPEED * time_delta;
    background->update(time_delta);
    for(WorldObject *obj: objects){
        obj->update(time_delta);
    }
}
void World::draw() {
    batch->draw();
    batch2->draw();
    batch3->draw();
    background->draw();
    for(WorldObject *obj: objects){
        obj->draw();
    }
}

void World::resize(unsigned int width, unsigned int height) {
    size.set(width, height);
    _offset.x = size.x/2.f;
    _offset.y = size.y*1.25f;
    background->resize(size.x, size.y);
    for(WorldObject *obj: objects){
        obj->resize(size.x, size.y);
    }
}

Vector2 World::offset() {
    return _offset;
}