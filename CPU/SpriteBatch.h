//
// Created by niels on 16.04.17.
//

#ifndef CPU_SPRITEBATCH_H
#define CPU_SPRITEBATCH_H

#include "gameplay.h"

namespace CPU {
    using namespace std;
    using namespace gameplay;
    class SpriteBatch {
        gameplay::SpriteBatch *batch;
    protected:
        gameplay::SpriteBatch *getBatch() const;
        std::string path;

    public:
        SpriteBatch() {};
        SpriteBatch(std::string path);
        ~SpriteBatch();
        void recreate();

        Vector3 pos;
        Rectangle src;
        Vector2 scale;
        Vector2 rotationPoint;
        float rotationRad;

        void draw();
    };
}

#endif //CPU_SPRITEBATCH_H
