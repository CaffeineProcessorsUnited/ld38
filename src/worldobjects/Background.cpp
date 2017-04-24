#include <random>
using namespace std;

#include "Background.h"
using namespace gameplay;

Background::Background(World *world):
    WorldObjectSingle(world)
{
    /*colors = vector<Vector4>{
                                    Vector4(0, 0, 0, 1), // 0
                                    Vector4(0.2, 0.2, 0.2, 1),
                                    Vector4(0.7, 0.2, 0.1, 1),
                                    Vector4(0.7, 0.7, 0, 1),
                                    Vector4(0.2, 0.2, 0.8, 1),
                                    Vector4(0.2, 0.2, 0.2, 1),
                                    Vector4(0.5, 0.5, 0.5, 1)
    };*/
    colors = vector<Vector4>{
            Vector4(0, 0, 0, 0), // 0-1
            Vector4(0, 0, 0, 0), // 2-3
            Vector4(0.7, 0.2, 0.1, 1), // 4-5
            Vector4(0.7, 0.5, 0, 1), // 6-7
            Vector4(0.6, 0.4, 0, 1), // 8-9
            Vector4(0.5, 0.3, 0.5, 1), // 10-11
            Vector4(0.5, 0.3, 0.7, 1), // 12-13
            Vector4(0.5, 0.4, 0.7, 1), // 14-15
            Vector4(0.4, 0.4, 0.7, 1), // 16-17
            Vector4(0.6, 0.4, 0.4, 1), // 18-19
            Vector4(0.3, 0.3, 0.3, 1), // 20-21
            Vector4(0.1, 0.1, 0.1, 0.5) // 22-23 -> start again
    };
    
    _batch = new CPU::SpriteBatch("@white");
    _batch->scale.set(world->size.x, world->size.y);
    current = 0;
    next = 0;
    if (colors.size() > 1) {
        next = 1;
    }
    timePerColor = World::DAYTIME / colors.size();
    lastColorChange = 0;
}

void Background::draw() {
    if (_batch != nullptr) {
        _batch->draw();
    }
}

void Background::update(float elapsedTime) {
    if (current != next && _batch != nullptr) {
        lastColorChange += elapsedTime;
        if (lastColorChange > timePerColor) {
            lastColorChange -= timePerColor;
            current = next;
            next = (next + 1) % (int) colors.size();
        }
        float colorPercentage = lastColorChange / timePerColor;

        _batch->color.x = colorPercentage * colors[next].x + (1 - colorPercentage) * colors[current].x;
        _batch->color.y = colorPercentage * colors[next].y + (1 - colorPercentage) * colors[current].y;
        _batch->color.z = colorPercentage * colors[next].z + (1 - colorPercentage) * colors[current].z;
        _batch->color.w = colorPercentage * colors[next].w + (1 - colorPercentage) * colors[current].w;
    }
}

Background::~Background() {

}

void Background::resize(unsigned int width, unsigned int height) {
    if (_batch != nullptr) {
        _batch->recreate();
        _batch->scale.set(world->size.x, world->size.y);
        _batch->pos.set(world->size.x / 2, world->size.y / 2, 1);
    }
}

float Background::getHourOfDay() {
    float percentageOfDay = 24 / colors.size();
    float percentOfPart = lastColorChange / timePerColor;
    return current * percentageOfDay + percentOfPart;
}

void Background::setHourOfDay(float hour) {
    while (hour < 0) {
        hour += 24;
    }
    while (hour >= 24) {
        hour -= 24;
    }
    float percentageOfDay = 24 / colors.size();
    current = (int) (hour / percentageOfDay);
    next = (current + 1) % colors.size();
    cout << current << endl;
    lastColorChange = timePerColor * fmod(hour, percentageOfDay);
}

ObjectType Background::type() const {
    return ObjectType::BACKGROUND;
}