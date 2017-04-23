#ifndef World_h_INCLUDED
#define World_h_INCLUDED

#include <vector>
using namespace std;

#include "gameplay.h"
using namespace gameplay;

#include "src/fw_decl.h"
#include "src/worldobjects/Background.h"
#include "src/gamelogic/WorldObject.h"
#include "src/gamelogic/WorldResource.h"
#include "CPU/SpriteBatch.h"
#include "CPU/EventHandler.h"

class World: public CPU::EventHandler {
private:
    vector<WorldResource *> resources;
    vector<WorldObject *> objects;
    Vector2 _offset;
    CPU::SpriteBatch *batch;
    Background *background;

    bool drag;
    Vector2 dragStart;
    Vector3 a, b, n;
    float rotateV;
public:
    World();
    ~World();

    constexpr static unsigned int MAX_LAYERS = 10;
    constexpr static float MAX_HEIGHT= 4200;
    static float RADIUS;
    constexpr static float SPEED = 3.337;
    constexpr static float DAYTIME = 60;
    constexpr static float GROUND = -40;
    constexpr static float AIR = 80;
    constexpr static float SKY = 430;
    vector<WorldResource *> &getResources();
    vector<WorldObject *> &getObjects();

    virtual void update(float time_delta);
    virtual void draw();

    void resize(unsigned int width, unsigned int height);
    void rotate(float rad);

    virtual void mouseScrolled(int wheelData) override;

    virtual void touchPress(int x, int y, unsigned int contactIndex) override;
    virtual void touchMove(int x, int y, unsigned int contactIndex) override;
    virtual void touchRelease(int x, int y, unsigned int contactIndex) override;

    Vector2 offset();
    Vector2 size;

    float getHourOfDay();
    vector<WorldObject*> objectsAtPos(int x, int y) const;
    bool isGround(int x, int y) const;
    bool isAir(int x, int y) const;
    bool isSky(int x, int y) const;

    void unicornCicked(WorldObject* unicorn);
    void plantClicked(WorldObject* plant);
    void cloudClicked(WorldObject* cloud);



    template<typename T>
    T* spawn() {
        T* t = new T(this);
        objects.push_back(t);
        return t;
    }
};

#endif // World_h_INCLUDED

