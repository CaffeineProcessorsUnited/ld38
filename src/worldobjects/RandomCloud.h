//
// Created by niels on 22.04.17.
//

#ifndef LD38_RANDOMCLOUD_H
#define LD38_RANDOMCLOUD_H

#include <vector>
#include <string>
using namespace std;

#include "CPU/Common.h"
using namespace CPU;

#include "src/fw_decl.h"
#include "src/gamelogic/WorldObjectSingle.h"

class RandomCloud: public WorldObjectSingle {
protected:
    constexpr static float minSpeed = -0.2f;
    constexpr static float maxSpeed = 0.2f;
    constexpr static int minHeight = 128;
    constexpr static int maxHeight = 333;
    constexpr static float rainDuration = 2;
    const static vector<string> cloudSprites;
    int spriteIndex;
    int rainAmount;
    bool isRaining;
    float rainTime;
public:
    RandomCloud(World *world);

    virtual void update(float delta_time);
    virtual void draw();

    bool canRain();
    bool canRain(int amount);
    bool doRain();
    bool doRain(int amount);
    virtual ObjectType type() const;
};


#endif //LD38_CLOUD_H
