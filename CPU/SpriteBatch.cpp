//
// Created by niels on 16.04.17.
//

#include "SpriteBatch.h"

CPU::SpriteBatch::SpriteBatch(std::string path) {
    this->path = path;
    batch = NULL;

    pos = Vector3::zero();
    scale = Vector2::zero();
    rotationPoint = Vector2(0.5, 0.5);
    rotationRad = 0;
    color = Vector4::one();

    recreate();
}

CPU::SpriteBatch::~SpriteBatch() {
    if(batch != nullptr){
        SAFE_DELETE(batch);
    }
}

void CPU::SpriteBatch::draw() {
    getBatch()->start();
    getBatch()->draw(Vector3(pos.x - scale.x / 2.f, pos.y - scale.y / 2.f, pos.z), src, scale, color, rotationPoint, rotationRad);
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






