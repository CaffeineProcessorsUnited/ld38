//
// Created by niels on 17.04.17.
//

#include "TestScreen.h"

TestScreen::TestScreen(ScreenManager *parent) :
        ScreenForm(parent),
        _batch(NULL),
        world(NULL),
        cloud(NULL)
{
}

void TestScreen::initialize() {
    ScreenForm::initialize();
    _batch = new CPU::SpriteBatch("res/png/image.png");
    _batch->pos = Vector3(Game::getInstance()->getWidth()/2, Game::getInstance()->getHeight()/2,1);

    loadForm("res/demo.form");
    registerFormControl("mainLabel");

    world = new World();
    cloud = world->spawn<Cloud>();
    cloud->pos.height = 128;
}

void TestScreen::finalize() {
    ScreenForm::finalize();
}

void TestScreen::update(float elapsedTime) {
    if(!isInitialized() )
        return;
    ScreenForm::update(elapsedTime);
    _batch->rotationRad += 0.1;

    world->update(elapsedTime);
}

void TestScreen::render() {
    if(!isVisible() || !isInitialized() )
        return;
    _batch->draw();
    ScreenForm::render();
    world->draw();
}

void TestScreen::keyRelease(Keyboard::Key key) {
    ScreenForm::keyRelease(key);
    if(key == Keyboard::KEY_SPACE) {
        _batch->scale.x += 4;
        _batch->scale.y += 4;
    } else if(key == Keyboard::KEY_TAB) {
        _batch->scale.x -= 4;
        _batch->scale.y -= 4;
    }
}

void TestScreen::mouseMove(int x, int y) {
    ScreenForm::mouseMove(x, y);
    _batch->pos.set(x,y,1);
}

void TestScreen::mouseScrolled(int wheelData) {
    ScreenForm::mouseScrolled(wheelData);
    if(wheelData != 0){
        _batch->scale.x += wheelData;
        _batch->scale.y += wheelData;
    }
}

void TestScreen::touchPress(int x, int y, unsigned int contactIndex) {
    world->touchPress(x, y, contactIndex);
}

void TestScreen::touchRelease(int x, int y, unsigned int contactIndex) {
    world->touchRelease(x, y, contactIndex);
}

void TestScreen::touchMove(int x, int y, unsigned int contactIndex) {
    world->touchMove(x, y, contactIndex);
}

void TestScreen::resize(int width, int height) {
    ScreenForm::resize(width, height);
    _batch->recreate();
    world->resize(width, height);
}

