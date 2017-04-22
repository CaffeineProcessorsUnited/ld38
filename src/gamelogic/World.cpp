#include "World.h"

World::World():
    resources(),
    objects()
{
}

const float World::WORLD_RADIUS = 42;

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
