#include "World.h"

World::World():
    resources(),
    objects()
{
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
    for(WorldObject *obj: objects){
        obj->update(time_delta);
    }
}
void World::draw() {
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
