//
// Created by niels on 22.04.17.
//

#ifndef LD38_RANDOMSTAR_H
#define LD38_RANDOMSTAR_H

#include "CPU/Common.h"
using namespace CPU;

#include "src/fw_decl.h"
#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/World.h"
#include <vector>
#include <random>
#include "src/worldobjects/Unicorn.h"

class RandomStar: public WorldObjectSingle {
protected:
    constexpr static float minSpeed = -0.0002f;
    constexpr static float maxSpeed = 0.0002f;

    constexpr static float midAppearTod = 19;
    constexpr static float deviateAppear = 1.5;

    const static int minHeight = 50;
    const static int maxHeight = 800;
    const static vector<string> sprites;
    int spriteIndex;
    bool isVisible;
    bool isFlickering;
    int flickerCounter;
public:
    RandomStar(World *world);
    void update(float delta_time);
    virtual ObjectType type();
};


#endif //LD38_CLOUD_H
