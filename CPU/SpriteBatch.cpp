//
// Created by niels on 16.04.17.
//

#include "SpriteBatch.h"

CPU::SpriteBatch::SpriteBatch(std::string path) {
    this->path = path;
    batch = NULL;

    pos = Vector3::zero();
    scale = Vector2::one();
    rotationPoint = Vector2(2.5, 1.5);
    rotationRad = 0;

    recreate();
}

CPU::SpriteBatch::~SpriteBatch() {
    if(batch != nullptr){
        SAFE_DELETE(batch);
    }
}

void CPU::SpriteBatch::draw() {
    getBatch()->start();
    getBatch()->draw(pos, src, scale, gameplay::Vector4::one(), rotationPoint, rotationRad);
    getBatch()->finish();
}

gameplay::SpriteBatch *CPU::SpriteBatch::getBatch() const {
    return batch;
}

void CPU::SpriteBatch::recreate() {
    if(batch != nullptr) {
        SAFE_DELETE(batch);
    }

    gameplay::Texture* texture = gameplay::Texture::create(path.c_str());
    src = gameplay::Rectangle(0,0,texture->getWidth(), texture->getHeight());
    scale.x = texture->getWidth();
    scale.y = texture->getHeight();
    batch = gameplay::SpriteBatch::create(texture, NULL, 0u);
    SAFE_RELEASE(texture);
}






