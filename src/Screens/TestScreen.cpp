//
// Created by niels on 17.04.17.
//

#include "TestScreen.h"
#include "src/gamelogic/World.h"
#include "src/gamelogic/WorldObjectSingle.h"
#include "src/gamelogic/WorldObject.h"
#include "src/worldobjects/RandomCloud.h"
#include "src/worldobjects/RandomStar.h"

TestScreen::TestScreen(ScreenManager *parent) :
        ScreenForm(parent),
        world(NULL)
{
}

void TestScreen::initialize() {
    ScreenForm::initialize();

    world = new World();
}

void TestScreen::finalize() {
    ScreenForm::finalize();
}

void TestScreen::update(float elapsedTime) {
    if(isPaused() || !isInitialized() )
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
    world->mouseMove(x,y);
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

