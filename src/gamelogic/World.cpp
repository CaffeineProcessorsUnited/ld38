#include "World.h"

World::World():
    resources(),
    objects()
{
    batch = new CPU::SpriteBatch("@world");
    batch->scale.scale(0.4);
    batch->rotationPoint.set(0.5, 0.5);

    batch2 = new CPU::SpriteBatch("@image");
    batch2->scale.set(4,4);
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
    batch->rotationRad += SPEED * time_delta;
    for(WorldObject *obj: objects){
        obj->update(time_delta);
    }
}
void World::draw() {
    //batch->draw();
    batch2->draw();
    for(WorldObject *obj: objects){
        obj->draw();
    }
}

void World::resize(int width, int height) {
    _offset.x = width/2;
    _offset.y = height/2;
}

Vector2 World::offset() {
    return _offset;
}
