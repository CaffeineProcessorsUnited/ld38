#ifndef World_h_INCLUDED
#define World_h_INCLUDED

#include <vector>
using namespace std;

#ifndef WorldObject_h_INCLUDED
class World;
#include "WorldObject.h"
#endif

#include "WorldResource.h"

class World {
private:
    vector<WorldResource *> resources;
    vector<WorldObject *> objects;
public:
    World();

    const static unsigned int MAX_LAYERS;
    vector<WorldResource *> &getResources();
    vector<WorldObject *> &getObjects();

    virtual void update(float time_delta);
    virtual void draw();
};

#endif // World_h_INCLUDED

