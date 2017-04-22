#include <random>
using namespace std;

#include "Background.h"
#include "gameplay.h"
using namespace gameplay;

Background::Background(World *world):
    WorldObjectSingle(world)
{
    colors = new Vector4[2] { Vector4(0, 0, 0, 1), Vector4(1, 1, 1, 1) };
    
    batch = new CPU::SpriteBatch("@white");
    batch->scale.set(world.size.x, world.size.y);
    noColors = sizeof(colors) / sizeof(Vector4);
    current = 0;
    if (noColors > 1) {
        next = 1;
    }
    timePerColor = World::DAYTIME / noColors;
}

void Background::draw() {
    if (batch != nullptr) {
        batch->draw();
    }
}

void Background::update(float elapsedTime) {
    if (current != next) {
        lastColorChange += elapsedTime;
        if (lastColorChange > timePerColor) {
            lastColorChange -= timePerColor;
            current = next;
            next = (next + 1) % noColors;
            float colorPercentage = lastColorChange / timePerColor;
            batch->color.set(colorPercentage * colors[next].x, colorPercentage * colors[next].y, colorPercentage * colors[next].z, colorPercentage * colors[next].w);
        }
    }
}

void Background::resize(unsigned int width, unsigned int height) {
    if (batch != nullptr) {
        batch->recreate();
        batch->scale.set(world.size.x, world.size.y);
    }
}