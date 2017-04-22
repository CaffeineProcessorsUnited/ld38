//
// Created by niels on 22.04.17.
//

#ifndef LD38_RANDOMSTAR_H
#define LD38_RANDOMSTAR_H

#include "src/fw_decl.h"
#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/World.h"
#include <vector>

class RandomStar: public WorldObjectSingle {
protected:
    constexpr static float minSpeed = -0.0002f;
    constexpr static float maxSpeed = 0.0002f;

    constexpr static float midAppearTod = 19;
    constexpr static float deviateAppear = 1.5;

    constexpr static float midDisappearTod = 3.6;
    constexpr static float deviateDisappear = 0.8;

    const static int minHeight = 128;
    const static int maxHeight = 600;
    const static vector<string> sprites;
    int spriteIndex;
    bool isVisible;
    float appearTod;
    float disappearTod;
public:
    RandomStar(World *world);
    void update(float delta_time);
    void draw();
};


#endif //LD38_CLOUD_H
