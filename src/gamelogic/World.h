#ifndef World_h_INCLUDED
#define World_h_INCLUDED

#include <vector>
using namespace std;

#include "gameplay.h"
using namespace gameplay;

#ifndef WorldObject_h_INCLUDED
class World;
#include "WorldObject.h"
#endif

#include "WorldResource.h"

class World {
private:
    vector<WorldResource *> resources;
    vector<WorldObject *> objects;
    Vector2 _offset;
public:
    World();

    constexpr static unsigned int MAX_LAYERS = 10;
    constexpr static float RADIUS = 42;
    vector<WorldResource *> &getResources();
    vector<WorldObject *> &getObjects();

    virtual void update(float time_delta);
    virtual void draw();

    void resize(int width, int height);
    Vector2 offset();

    template<typename T>
    T* spawn() {
        T* t = new T(this);
        objects.push_back(t);
        return t;
    }
};

#endif // World_h_INCLUDED

