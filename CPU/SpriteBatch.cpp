//
// Created by niels on 16.04.17.
//

#include "SpriteBatch.h"

CPU::SpriteBatch::SpriteBatch(std::string path) {
    gameplay::Texture* texture = gameplay::Texture::create(path.c_str());
    src = gameplay::Rectangle(0,0,texture->getWidth(), texture->getHeight());
    batch = gameplay::SpriteBatch::create(texture, NULL, 0u);
    SAFE_RELEASE(texture);
}

CPU::SpriteBatch::~SpriteBatch() {
    if(batch != nullptr){
        SAFE_DELETE(batch);
    }
}

void CPU::SpriteBatch::draw() {
    getBatch()->start();
    getBatch()->draw(pos, src, gameplay::Vector4::one());
    getBatch()->finish();
}

void CPU::SpriteBatch::draw(const gameplay::Rectangle &pos) {
    getBatch()->start();
    getBatch()->draw(pos, src, gameplay::Vector4::zero());
    getBatch()->finish();
}

gameplay::SpriteBatch *CPU::SpriteBatch::getBatch() const {
    return batch;
}




