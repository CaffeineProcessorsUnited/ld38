#ifndef World_h_INCLUDED
#define World_h_INCLUDED

#include <vector>
#include <CPU/EventHandler.h>

using namespace std;

#include "gameplay.h"
using namespace gameplay;

#include "src/fw_decl.h"
#include "CPU/SpriteBatch.h"
#include "CPU/EventHandler.h"

#include "WorldObject.h"
#include "WorldObjectSingle.h"
#include "src/worldobjects/RandomCloud.h"
#include "src/worldobjects/RandomStar.h"
#include "src/worldobjects/Unicorn.h"
#include "src/worldobjects/RainbowTree.h"
#include "src/worldobjects/Background.h"
#include "src/worldobjects/Granny.h"
#include "src/worldobjects/Rain.h"

class World: public CPU::EventHandler {
private:
    vector<WorldResource *> resources;
    vector<WorldObject *> objects;
    vector<WorldObject *> toSpawn;
    vector<WorldObject *> toDestroy;
    Vector2 _offset;
    CPU::SpriteBatch *batch;
    Font* font;
    Background *background;
    Granny *granny;
    int seeds;
    string seedText;

    bool drag;
    Vector2 mousePos;
    Vector2 dragStart;
    Vector3 a, b, n;
    float rotateV;
public:
    World();
    ~World();

    constexpr static unsigned int MAX_LAYERS = 10;
    constexpr static float MAX_HEIGHT= 4200;
    constexpr static float MINDRAGDISTANCE = 1000;
    static float RADIUS;
    constexpr static float SPEED = 3.337;
    constexpr static float DAYTIME = 60;
    constexpr static float GROUND = -40;
    constexpr static float AIR = 80;
    constexpr static float SKY = 430;
    constexpr static float RAIN_DIST = 64;
    constexpr static float RAIN_HYDR = 10.f;
    vector<WorldResource *> &getResources();
    vector<WorldObject *> &getObjects();

    virtual void update(float time_delta);
    virtual void draw();

    void resize(unsigned int width, unsigned int height);
    void rotate(float rad);

    virtual void mouseScrolled(int wheelData) override;

    void mouseMove(int x, int y) override;

    virtual void touchPress(int x, int y, unsigned int contactIndex) override;
    virtual void touchMove(int x, int y, unsigned int contactIndex) override;
    virtual void touchRelease(int x, int y, unsigned int contactIndex) override;

    Vector2 offset() const;
    Vector2 size;

    float getHourOfDay();
    float getHourOfDay(float deg);
    void setHourOfDay(float hour);
    vector<WorldObject*> objectsAtPos(int x, int y) const;
    bool isGround(int x, int y) const;
    bool isAir(int x, int y) const;
    bool isSky(int x, int y) const;
    bool isVisible(float deg) const;

    void unicornClicked(WorldObject *unicorn);
    void treeClicked(WorldObject *plant);
    void cloudClicked(WorldObject* cloud);
    void receiveSeeds(int n);
    void receiveRain(const WorldPos& pos);

    template<typename T>
    T* spawn() {
        T* t = new T(this);
        toSpawn.push_back(t);
        return t;
    }
    template<typename T>
    void destroy(T* t) {
        vector<WorldObject*>::iterator it = find(toDestroy.begin(), toDestroy.end(), t);
        //Kill only once :(
        if(it == toDestroy.end()) {
            toDestroy.push_back(t);
        }
    }

    void plantSapling(int x, int y);
    float points2angle(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3);
    float pos2angle(int x, int y);
    Vector2 angle2pos(float rad) const;
    Vector3 pos2vec(const WorldPos& pos) const;
    Font* activeFont();
};

#endif // World_h_INCLUDED

