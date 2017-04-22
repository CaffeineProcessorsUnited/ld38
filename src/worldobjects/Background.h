//
// Created by niels on 22.04.17.
//

#ifndef LD38_BACKGROUND_H
#define LD38_BACKGROUND_H

#ifndef LD38_WORLDOBJECTSINGLE_H
class Background;
#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/World.h"
#endif

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
