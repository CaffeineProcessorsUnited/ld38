//
// Created by niels on 22.04.17.
//

#ifndef LD38_BACKGROUND_H
#define LD38_BACKGROUND_H

#include "src/fw_decl.h"
#include "src/gamelogic/World.h"
#include "src/gamelogic/WorldObjectSingle.h"

class Background: public WorldObjectSingle {
protected:
    Vector4 *colors;
    int noColors, current, next;
    float lastColorChange, timePerColor;
public:
    Background(World *world);

    virtual void draw() override;
    virtual void update(float elapsedTime) override;
    virtual void resize(unsigned int width, unsigned int height) override;
};



#endif //LD38_BACKGROUND_H
