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
    constexpr static float minSpeed = -0.02f;
    constexpr static float maxSpeed = 0.02f;
    const static int minHeight = 128;
    const static int maxHeight = 333;
    const static vector<string> sprites;
    int spriteIndex;
public:
    RandomStar(World *world);
};


#endif //LD38_CLOUD_H
