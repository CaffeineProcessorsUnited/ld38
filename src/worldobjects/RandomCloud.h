//
// Created by niels on 22.04.17.
//

#ifndef LD38_RANDOMCLOUD_H
#define LD38_RANDOMCLOUD_H

#include "src/fw_decl.h"
#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/World.h"
#include <vector>

class RandomCloud: public WorldObjectSingle {
protected:
    constexpr static float minSpeed = -0.5f;
    constexpr static float maxSpeed = 0.5f;
    const static int minHeight = 80;
    const static int maxHeight = 200;
    const static vector<string> cloudSprites;
    int spriteIndex;
public:
    RandomCloud(World *world);
};


#endif //LD38_CLOUD_H
