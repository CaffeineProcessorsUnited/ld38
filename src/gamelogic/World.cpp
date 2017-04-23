#include "World.h"

#include <src/worldobjects/Unicorn.h>
#include <src/worldobjects/RainbowTree.h>
#include <src/worldobjects/RandomCloud.h>

float World::RADIUS = 512;

World::World():
    resources(),
    objects()
{
    batch = new CPU::SpriteBatch("@world");
    batch->scale.set(2*RADIUS, 2*RADIUS);
    batch->rotationPoint.set(0.5, 0.5);

    background = new Background(this);

    size.set(Game::getInstance()->getWidth(), Game::getInstance()->getHeight());
    dragStart = Vector2::zero();
    rotateV = 0;
    drag = false;
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
        rotate(rotateV * time_delta);
        rotateV *= 0.85;
    }
    background->update(time_delta);
    batch->pos.set(_offset.x, _offset.y, 1);
    for(WorldObject *obj: objects){
        obj->update(time_delta);
    }

}
void World::draw() {
    for(WorldObject *obj: objects){
        if (obj->type() == ObjectType::STAR) {
            obj->draw();
        }
    }
    background->draw();
    batch->draw();
    for(WorldObject *obj: objects){
        if (obj->type() != ObjectType::STAR) {
            obj->draw();
        }
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

    RADIUS = w/2.f;
    batch->recreate();
    batch->scale.set(w,w);
    batch->rotationPoint.set(0.5, 0.5);
}

void World::rotate(float rad) {
    batch->rotationRad += rad;
    for(WorldObject* obj: objects){
        obj->pos.rad -= rad;
        if(obj->pos.rad > 2*M_PI){
            obj->pos.rad -= 2*M_PI;
        } else if(obj->pos.rad < -2*M_PI){
            obj->pos.rad += 2*M_PI;
        }
    }
}


void World::touchPress(int x, int y, unsigned int contactIndex) {
    dragStart.set(x, y);
}

void World::touchRelease(int x, int y, unsigned int contactIndex) {
    cout << "DRAG " << drag << endl;
    if(!drag){
        cout << Vector2(_offset.x-x, _offset.y-y).length()-RADIUS << endl;
        vector<WorldObject *> objs = objectsAtPos(x,y);

        for(WorldObject* obj: objs){
            Unicorn* unicorn = dynamic_cast<Unicorn*>(obj);
            if(unicorn != nullptr){
                unicornCicked(obj);
            }
            RainbowTree* tree = dynamic_cast<RainbowTree*>(obj);
            if(tree != nullptr){
                plantClicked(obj);
            }
            RandomCloud* rcloud = dynamic_cast<RandomCloud*>(obj);
            if(rcloud != nullptr){
                cloudClicked(obj);
            }
            /*
Sun* sun = dynamic_cast<Sun*>(obj);
if(sun != nullptr){
    //do stuff with sun
}
Moon* moon = dynamic_cast<Moon*>(obj);
if(moon != nullptr){
    //do stuff with moon
}*/
        }
        if(isGround(x,y)){
            cout << "GROUND " << x << " " << y << endl;
            //Do something with ground
        } else if(isAir(x,y)){
            cout << "AIR " << x << " " << y << endl;
            //Do something with air
        } else if(isSky(x,y)){
            cout << "SKY " << x << " " << y << endl;
            //Do something with sky
        }
    }
    drag = false;
}

void World::touchMove(int x, int y, unsigned int contactIndex) {
    a = Vector3(dragStart.x - _offset.x, dragStart.y - _offset.y, 0);
    b = Vector3((float) x - _offset.x, (float) y - _offset.y, 0);
    n = Vector3(a);
    n.cross(b);
    rotateV += n.z / 36000 * SPEED;
    dragStart.set(x, y);
    drag = true;
}

void World::mouseScrolled(int wheelData) {
    if(wheelData != 0){
        rotateV += wheelData * SPEED / 6;
    }
}

Vector2 World::offset() {
    return _offset;
}

float World::getHourOfDay() {
    return background->getHourOfDay();
}

vector<WorldObject *> World::objectsAtPos(int x, int y) const {
    vector<WorldObject*> obj;

    for(WorldObject* object: objects){
        if(object->intersect(x,y)){
            obj.push_back(object);
        }
    }
    return obj;
}

bool World::isGround(int x, int y) const {
    float dist = Vector2(_offset.x-x, _offset.y-y).length() - RADIUS;
    return GROUND <= dist && dist <= AIR;
}

bool World::isAir(int x, int y) const {
    float dist = Vector2(_offset.x-x, _offset.y-y).length() - RADIUS;
    return AIR <= dist && dist <= SKY;
}

bool World::isSky(int x, int y) const {
    float dist = Vector2(_offset.x-x, _offset.y-y).length() - RADIUS;
    return SKY <= dist;
}

void World::plantClicked(WorldObject *plant) {

}

void World::cloudClicked(WorldObject *cloud) {

}

void World::unicornCicked(WorldObject *unicorn) {

}
