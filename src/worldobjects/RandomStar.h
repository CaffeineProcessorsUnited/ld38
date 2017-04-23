//
// Created by niels on 22.04.17.
//

#ifndef LD38_RANDOMSTAR_H
#define LD38_RANDOMSTAR_H

#include <vector>
#include <random>
using namespace std;

#include "CPU/Common.h"
using namespace CPU;

#include "src/fw_decl.h"
#include "src/gamelogic/WorldObjectSingle.h"

class RandomStar: public WorldObjectSingle {
protected:
    constexpr static float minSpeed = -0.0002f;
    constexpr static float maxSpeed = 0.0002f;

    constexpr static float midAppearTod = 19;
    constexpr static float deviateAppear = 1.5;

    constexpr static float midDisappearTod = 3.6;
    constexpr static float deviateDisappear = 0.8;

    const static int minHeight = 50;
    const static int maxHeight = 800;
    const static vector<string> sprites;
    int spriteIndex;
    bool isVisible;
    bool isFlickering;
    float appearTod;
    float disappearTod;
    int flickerCounter;
public:
    RandomStar(World *world);
    virtual void update(float delta_time) ;
    virtual void draw();
    virtual ObjectType type() const;
};



#endif //LD38_CLOUD_H
