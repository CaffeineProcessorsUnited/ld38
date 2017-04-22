//
// Created by niels on 16.04.17.
//

#ifndef CPU_SPRITEBATCH_H
#define CPU_SPRITEBATCH_H

#include "gameplay.h"

namespace CPU {
    using namespace gameplay;
    class SpriteBatch {
        gameplay::SpriteBatch *batch;
    protected:
        gameplay::SpriteBatch *getBatch() const;
        Rectangle src;
        std::string path;

    public:
        SpriteBatch() {};
        SpriteBatch(std::string path);
        ~SpriteBatch();
        void recreate();

        Rectangle pos;

        void draw();
        void draw(const Rectangle &pos);
    };
}

#endif //CPU_SPRITEBATCH_H
