//
// Created by niels on 17.04.17.
//

#include "TestScreen.h"

TestScreen::TestScreen(ScreenManager *parent) :
        ScreenForm(parent),
        world(NULL)
{
}

void TestScreen::initialize() {
    ScreenForm::initialize();

    //loadForm("res/demo.form");
    //registerFormControl("mainLabel");

    world = new World();

    //Spawn Random Clouds.
    for(int i = 0; i < 10; i++){
        myCloud = world->spawn<RandomCloud>();
        clouds.push_back(myCloud);

    }

    //Spawn Random Stars.
    for(int i = 0; i < 200; i++){
        myStar = world->spawn<RandomStar>();
        stars.push_back(myStar);
    }
    uni = world->spawn<Unicorn>();

}

void TestScreen::finalize() {
    ScreenForm::finalize();
}

void TestScreen::update(float elapsedTime) {
    if(!isInitialized() )
        return;
    ScreenForm::update(elapsedTime);

    world->update(elapsedTime);
}

void TestScreen::render() {
    if(!isVisible() || !isInitialized() )
        return;
    ScreenForm::render();
    world->draw();
}

void TestScreen::keyRelease(Keyboard::Key key) {
    ScreenForm::keyRelease(key);
    if(key == Keyboard::KEY_SPACE) {
    } else if(key == Keyboard::KEY_TAB) {
    }
}

void TestScreen::mouseMove(int x, int y) {
    ScreenForm::mouseMove(x, y);
}

void TestScreen::mouseScrolled(int wheelData) {
    ScreenForm::mouseScrolled(wheelData);
    if(wheelData != 0){
        world->mouseScrolled(wheelData);
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
    world->resize(width, height);
}

