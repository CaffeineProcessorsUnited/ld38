//
// Created by niels on 17.04.17.
//

#include "TestScreen.h"

TestScreen::TestScreen(ScreenManager *parent) :
        ScreenForm(parent),
        _batch(NULL)
{
}

void TestScreen::initialize() {
    ScreenForm::initialize();
    _batch = new CPU::SpriteBatch("res/png/image.png");
    _batch->pos = Rectangle(Game::getInstance()->getWidth()/2, Game::getInstance()->getHeight()/2, 16, 16);

    loadForm("res/demo.form");
    registerFormControl("mainLabel");
}

void TestScreen::finalize() {
    ScreenForm::finalize();
}

void TestScreen::update(float elapsedTime) {
    if(!isInitialized() )
        return;
    ScreenForm::update(elapsedTime);
}

void TestScreen::render() {
    if(!isVisible() || !isInitialized() )
        return;
    _batch->draw();
    ScreenForm::render();
}

void TestScreen::keyRelease(Keyboard::Key key) {
    ScreenForm::keyRelease(key);
    if(key == Keyboard::KEY_SPACE) {
        _batch->pos.height += 4;
        _batch->pos.width += 4;
    } else if(key == Keyboard::KEY_TAB) {
        _batch->pos.height -= 4;
        _batch->pos.width -= 4;
    }
}

void TestScreen::mouseMove(int x, int y) {
    ScreenForm::mouseMove(x, y);
    _batch->pos.setPosition(x,y);
}

void TestScreen::mouseScrolled(int wheelData) {
    ScreenForm::mouseScrolled(wheelData);
    if(wheelData != 0){
        _batch->pos.height += wheelData;
        _batch->pos.width += wheelData;
    }
}