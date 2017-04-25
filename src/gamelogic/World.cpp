#include "World.h"

#include <algorithm>

#include "src/gamelogic/WorldResource.h"
#include "src/gamelogic/WorldObject.h"
#include "src/worldobjects/Background.h"
#include "src/worldobjects/Unicorn.h"
#include "src/worldobjects/RainbowTree.h"
#include "src/worldobjects/RandomCloud.h"
#include "src/worldobjects/Granny.h"

float World::RADIUS = 512;

World::World():
    resources(),
    objects()
{
    batch = new CPU::SpriteBatch("@world");
    batch->scale.set(-2*RADIUS, 2*RADIUS);
    batch->rotationPoint.set(0.5, 0.5);
    granny = new CPU::SpriteBatch("@granny");
    granny->scale.set(-2*RADIUS, 2*RADIUS);
    granny->rotationPoint.set(0.5, 0.5);
    granny->rotationRad = M_PI;

    background = new Background(this);
    setHourOfDay(12);

    size.set(Game::getInstance()->getWidth(), Game::getInstance()->getHeight());
    dragStart = Vector2::zero();
    rotateV = 0;
    drag = false;

    font = Font::create("res/roboto.gpb");
    seeds = 10;
    seedText = "Got "+to_string(seeds)+" seeds";

    timeToCloudSpawn = CLOUD_DELAY;

    for(int i = 0; i < 30; i++){
        spawn<RandomCloud>();
    }
    for(int i = 0; i < 4; i++){
        spawn<Unicorn>();
    }

    //Spawn Random Stars.
    for(int i = 0; i < 200; i++){
        spawn<RandomStar>();
    }
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
    vector<WorldObject*>::iterator it;
    for(it=toSpawn.begin();it!=toSpawn.end();++it){
        if((*it) != nullptr){
            objects.push_back(*it);
        }
    }
    toSpawn.clear();

    int i = 0;
    while(i < toDestroy.size()) {
        WorldObject* tod = nullptr;
        it = toDestroy.begin();
        tod = *(it+i);
        if (tod != nullptr) {
            vector<WorldObject *>::iterator itt = find(objects.begin(), objects.end(), tod);
            if (itt != objects.end()) {
                objects.erase(itt);
            }
        }
        delete tod;
        tod = nullptr;
        ++i;
    }
    toDestroy.clear();

    timeToCloudSpawn -= time_delta;
    if(timeToCloudSpawn <= 0) {
        timeToCloudSpawn = CLOUD_DELAY;

        RandomCloud* cloud = spawn<RandomCloud>();
        cloud->pos.rad = 0;
    }

    if (fabs(rotateV) > 0.000005) {
        rotate(rotateV * time_delta);
        rotateV *= 0.85;
    }
    background->update(time_delta);
    batch->pos.set(_offset.x, _offset.y, 1);
    granny->pos.set(_offset.x, _offset.y, 1);
    for(WorldObject *obj: objects){
        if(obj == nullptr){
            continue;
        }
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
    granny->draw();
    for(WorldObject *obj: objects){
        if (obj->type() != ObjectType::STAR) {
            obj->draw();
        }
    }

    font->start();
    font->drawText(seedText.c_str(), 20, 50, Vector4(1, 0, 0, 1), font->getSize());
    for(WorldObject *obj: objects){
        if(obj->intersect(mousePos.x, mousePos.y)) {
            obj->drawOverlay();
        }
    }
    font->finish();
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
    batch->scale.set(-w,w);
    batch->rotationPoint.set(0.5, 0.5);
    granny->recreate();
    granny->scale.set(-w,w);
    granny->rotationPoint.set(0.5, 0.5);
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

void World::mouseMove(int x, int y) {
    mousePos.set(x,y);
}

void World::touchPress(int x, int y, unsigned int contactIndex) {
    mousePos.set(x,y);
    dragStart.set(x, y);
}

void World::touchRelease(int x, int y, unsigned int contactIndex) {
    mousePos.set(x,y);
    cout << "DRAG " << drag << endl;
    if(!drag){
        cout << Vector2(_offset.x-x, _offset.y-y).length()-RADIUS << endl;
        vector<WorldObject *> objs = objectsAtPos(x,y);
        cout << "got " << objs.size() << "objs" << endl;

        int countRain = 0;

        for(WorldObject* obj: objs){
            ObjectType type = obj->type();
            switch(type){
                case TREE:
                    treeClicked(obj);
                    break;
                case UNICORN:
                    unicornClicked(obj);
                    break;
                case CLOUD:
                    cloudClicked(obj);
                    break;
                case RAIN:
                    countRain += 1;
                    break;
            }
        }
        if(isGround(x,y)){
            cout << "GROUND " << x << " " << y << endl;
            if(objs.size() == countRain) {
                plantSapling(x, y);
            }
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
    mousePos.set(x,y);
    a = Vector3(dragStart.x - _offset.x, dragStart.y - _offset.y, 0);
    b = Vector3((float) x - _offset.x, (float) y - _offset.y, 0);
    n = Vector3(a);
    n.cross(b);
    if (abs(n.z) > MINDRAGDISTANCE) {
        rotateV += n.z / 36000 * SPEED;
        dragStart.set(x, y);
        drag = true;
    }
}

void World::mouseScrolled(int wheelData) {
    if(wheelData != 0){
        rotateV += wheelData * SPEED / 6;
    }
}

Vector2 World::offset() const {
    return _offset;
}

float World::getHourOfDay() {
    return background->getHourOfDay();
}

float World::getHourOfDay(float deg) {
    float degPercent = deg / (2 * M_PI);
    return background->getHourOfDay() + (degPercent * 24);
}

void World::setHourOfDay(float hour) {
    background->setHourOfDay(hour);
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

bool World::isVisible(float deg) const {
    Vector2 pos = angle2pos(deg);
    return pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y;
}

void World::treeClicked(WorldObject *plant) {
    RainbowTree *tree = dynamic_cast<RainbowTree*>(plant);
    if(tree != nullptr){
        tree->grow();
        destroy(tree);
    }
}

void World::cloudClicked(WorldObject *cloud) {
    RandomCloud *mycloud = dynamic_cast<RandomCloud*>(cloud);
    if (mycloud != NULL){
        mycloud->doRain(10);
    }

}

void World::unicornClicked(WorldObject *unicorn) {

}

void World::plantSapling(int x, int y) {
    if(seeds > 0) {
        float rotation = pos2angle(x, y);
        RainbowTree *tree = spawn<RainbowTree>();
        tree->pos.rad = rotation;
        seeds -= 1;
        seedText = "Got "+to_string(seeds)+" seeds";
    }
}

float World::points2angle(const Vector2& p1, const Vector2& p2, const Vector2& p3){
    Vector2 a(p2.x-p1.x,p2.y-p1.y);
    Vector2 b(p2.x-p3.x,p2.y-p3.y);

    float dot = (a.x*b.x+a.y*b.y);
    float cross = (a.x*b.y-a.y*b.x);
    float alpha = atan2(cross+MATH_FLOAT_SMALL,dot);
    return alpha;
}

float World::pos2angle(int x, int y){
    Vector2 top = offset();
    top.y = 9999;
    float angle = points2angle(Vector2(x, y), offset(), top);
    return (float) fmod(angle,4 * M_PI);
}

Vector2 World::angle2pos(float rad) const {
    Vector3 vec = pos2vec(WorldPos(rad,0,0));
    return Vector2(vec.x, vec.y);
}

void World::receiveSeeds(int n) {
    seeds += n;
    seedText = "Got "+to_string(seeds)+" seeds";
}

void World::receiveRain(const WorldPos& pos) {
    vector<WorldObject*> obj;

    for(WorldObject* object: objects){
        RainbowTree* tree = dynamic_cast<RainbowTree*>(object);
        if(tree != nullptr) {
            if (tree->near(pos, RAIN_DIST)) {
                tree->receiveRain(RAIN_HYDR);
            }
        }
    }
}

Vector3 World::pos2vec(const WorldPos& pos) const {
    return Vector3(offset().x + sin(pos.rad)*(World::RADIUS+pos.height),
            offset().y + cos(pos.rad)*(World::RADIUS+pos.height),
            pos.zindex);
}

Font *World::activeFont() {
    return font;
}
