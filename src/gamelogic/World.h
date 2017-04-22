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
    CPU::SpriteBatch *batch, *batch2, *batch3;
    Background *background;

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
    constexpr static float DAYTIME = 20;
    vector<WorldResource *> &getResources();
    vector<WorldObject *> &getObjects();

    virtual void update(float time_delta);
    virtual void draw();

    void resize(unsigned int width, unsigned int height);
    void rotate(float rad);

    virtual void touchPress(int x, int y, unsigned int contactIndex) override;
    virtual void touchMove(int x, int y, unsigned int contactIndex) override;

    Vector2 offset();
    Vector2 size;

    template<typename T>
    T* spawn() {
        T* t = new T(this);
        objects.push_back(t);
        return t;
    }
};

#endif // World_h_INCLUDED

