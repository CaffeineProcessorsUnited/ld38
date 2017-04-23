//
// Created by niels on 22.04.17.
//

#ifndef LD38_RANDOMCLOUD_H
#define LD38_RANDOMCLOUD_H

#include "CPU/Common.h"
using namespace CPU;

#include "src/fw_decl.h"
#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/World.h"
#include <vector>

class RandomCloud: public WorldObjectSingle {
protected:
    constexpr static float minSpeed = -0.2f;
    constexpr static float maxSpeed = 0.2f;
    const static int minHeight = 128;
    const static int maxHeight = 333;
    const static vector<string> cloudSprites;
    int spriteIndex;
public:
    RandomCloud(World *world);
    virtual ObjectType type() const override;
};


#endif //LD38_CLOUD_H
