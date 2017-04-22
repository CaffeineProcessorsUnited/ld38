//
// Created by niels on 17.04.17.
//

#include "App.h"
using namespace CPU;

App::App():
        Game(),
        showFPS(false),
        fontFPS(NULL),
        manager(NULL)
{
}

ScreenManager* App::getScreenManager() {
    if(manager == nullptr){
        cerr << "Call to App::getScreenManager before manager is initialized. IF IT CRASHES IT IS YOUR FAULT!!!" << endl;
    }
    return manager;
}


void App::initialize() {
    Game::initialize();

    initialized = true;
    manager = new ScreenManager();
    fontFPS = Font::create("res/roboto.gpb");

    Game::setVsync(false);
}

void App::finalize() {
    Game::finalize();

    SAFE_RELEASE(fontFPS);
    SAFE_RELEASE(manager);
}

void App::update(float elapsedTime) {
    Game::update(elapsedTime);
    manager->update(elapsedTime);
}

void App::preRender() {
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);
}

void App::render(float elapsedTime) {
    Game::render(elapsedTime);

    preRender();
    manager->render();
    postRender();
}

void App::postRender() {
    drawFrameRate();
}

void App::keyEvent(Keyboard::KeyEvent evt, int key) {
    if(!isInitialized())
        return;
    Game::keyEvent(evt, key);
    manager->keyEvent(evt, key);
}

bool App::mouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta) {
    if(!isInitialized())
        return false;
    manager->mouseEvent(evt, x,y,wheelDelta);
    return Game::mouseEvent(evt, x, y, wheelDelta);
}

void App::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex) {
    if(evt == Touch::TouchEvent::TOUCH_PRESS) {
        manager->mouseEvent(Mouse::MouseEvent::MOUSE_PRESS_LEFT_BUTTON, x, y, 0);
    } else if(evt == Touch::TouchEvent::TOUCH_RELEASE) {
        manager->mouseEvent(Mouse::MouseEvent::MOUSE_RELEASE_LEFT_BUTTON, x, y, 0);
    } else {
        manager->mouseEvent(Mouse::MouseEvent::MOUSE_MOVE, x, y, 0);
    }
}

void App::drawFrameRate(){
    if(!showFPS)
        return;

    if(Game::getInstance() == nullptr){
        cerr << "Game::getInstance is NULL in App::drawFrameRate. THIS SHOULD NEVER HAPPEN!" << endl;
        return;
    }

    fontFPS->start();
    char text[1024];
    sprintf(text, "%d FPS", Game::getInstance()->getFrameRate());
    fontFPS->drawText(text, 20, 20, Vector4(1, 0, 0, 1), fontFPS->getSize());
    fontFPS->finish();
}

void App::setShowFPS(bool show) {
    showFPS = show;
}

bool App::isShowFPS() const {
    return showFPS;
}

void App::resizeEvent(unsigned int width, unsigned int height) {
    Game::resizeEvent(width, height);
    Game::getInstance()->setViewport(Rectangle(width, height));

    if(!initialized)
        return;
    manager->resize(width,height);
}

void App::postInitialize() {
    initialized = true;
}



