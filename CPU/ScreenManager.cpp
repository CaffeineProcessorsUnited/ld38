//
// Created by niels on 17.04.17.
//

#include "ScreenManager.h"

using namespace CPU;

ScreenManager::ScreenManager():
        screens()
{
    screens.clear();
}

ScreenManager::~ScreenManager() {
    for(Screen* screen: screens)
        screen->finalize();
}

bool ScreenManager::contains(const Screen * screen)const {
    vector<Screen*>::const_iterator it = find(screens.cbegin(), screens.cend(), screen);
    return it != screens.cend();
}

void ScreenManager::add(Screen *screen) {
    if(!contains(screen)){
        screens.push_back(screen);
    }
}

void ScreenManager::remove(Screen *screen) {
    vector<Screen*>::iterator it = find(screens.begin(), screens.end(), screen);
    if(it != screens.end()){
        screens.erase(it);
    }
}

void ScreenManager::keyPress(Keyboard::Key key) {
    for(auto& elem: screens){elem->keyPress(key);}
}

void ScreenManager::keyRelease(Keyboard::Key key) {
    for(auto& elem: screens){elem->keyRelease(key);}
}

void ScreenManager::keyChar(Keyboard::Key key) {
    for(auto& elem: screens){elem->keyChar(key);}
}

void ScreenManager::mousePress(MouseButton button, int x, int y) {
    for(auto& elem: screens){elem->mousePress(button, x, y);}
}

void ScreenManager::mouseRelease(MouseButton button, int x, int y) {
    for(auto& elem: screens){elem->mousePress(button, x, y);}
}

void ScreenManager::mouseMove(int x, int y) {
    for(auto& elem: screens){elem->mouseMove(x, y);}
}

void ScreenManager::mouseScrolled(int wheelData) {
    for(auto& elem: screens){elem->mouseScrolled(wheelData);}
}

void ScreenManager::keyEvent(Keyboard::KeyEvent evt, int key) {
    switch(evt){
        case Keyboard::KEY_PRESS:
            keyPress((Keyboard::Key)key);
            break;
        case Keyboard::KEY_RELEASE:
            keyRelease((Keyboard::Key)key);
            break;
        case Keyboard::KEY_CHAR:
            keyChar((Keyboard::Key)key);
            break;
    }
}

void ScreenManager::mouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta) {
    switch(evt){
        case Mouse::MOUSE_PRESS_LEFT_BUTTON:
            mousePress(LEFT, x, y);
            break;
        case Mouse::MOUSE_RELEASE_LEFT_BUTTON:
            mouseRelease(LEFT, x, y);
            break;
        case Mouse::MOUSE_PRESS_MIDDLE_BUTTON:
            mousePress(MIDDLE, x, y);
            break;
        case Mouse::MOUSE_RELEASE_MIDDLE_BUTTON:
            mouseRelease(MIDDLE, x, y);
            break;
        case Mouse::MOUSE_PRESS_RIGHT_BUTTON:
            mousePress(RIGHT, x, y);
            break;
        case Mouse::MOUSE_RELEASE_RIGHT_BUTTON:
            mouseRelease(RIGHT, x, y);
            break;
        case Mouse::MOUSE_MOVE:
            mouseMove(x,y);
            break;
        case Mouse::MOUSE_WHEEL:
            mouseScrolled(wheelDelta);
            break;
    }
}

void ScreenManager::update(float elapsedTime) {
    for(auto& elem: screens){elem->update(elapsedTime);}
}

void ScreenManager::render() {
    for(auto& elem: screens){elem->render();}
}

void ScreenManager::resize(unsigned int width, unsigned int height) {
    for(auto& elem: screens){elem->resize(width, height);}
}


bool ScreenManager::isMostFrontScreen(const Screen *screen) const {
    if(!contains(screen))
        return false;
    ScreenLayer layer = BACK;
    vector<Screen*>::const_iterator elem = screens.cbegin();
    vector<Screen*>::const_iterator it = screens.cbegin();
    for(;it != screens.cend(); ++it){
        if((*it)->getLayer() > layer){
            layer = (*it)->getLayer();
            elem = it;
        }
    }
    return *elem == screen;
}

