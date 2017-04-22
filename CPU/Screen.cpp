//
// Created by niels on 17.04.17.
//

#include "Screen.h"
using namespace CPU;

Screen::Screen(CPU::ScreenManager *parent):
        parent(NULL),
        visible(false),
        layer(BACK),
        initialized(false)
{
    setParent(parent);
}

void Screen::setParent(CPU::ScreenManager *parent) {
    if(this->parent != nullptr){
        this->parent->remove(this);
    }
    this->parent = parent;
    parent->add(this);
}

Screen::~Screen() {
    if(this->parent != nullptr){
        this->parent->remove(this);
    }
}

ScreenManager *CPU::Screen::getParent() const {
    return parent;
}

bool Screen::isInitialized() const {
    return initialized;
}

void Screen::show() {
    setVisible(true);
}

void Screen::hide() {
    setVisible(false);
}

void Screen::setVisible(bool visible) {
    this->visible = visible;
}

void Screen::resize(int width, int height) {
}

bool Screen::isVisible() const {
    return visible;
}

void Screen::raise() {
    if(getLayer() != FRONT){
        setLayer(static_cast<ScreenLayer>(getLayer()+1));
    }
}

void Screen::lower() {
    if(getLayer() != BACK){
        setLayer(static_cast<ScreenLayer>(getLayer()-1));
    }
}

void Screen::moveToBack() {
    setLayer(BACK);
}

void Screen::moveToFront() {
    setLayer(FRONT);
}

ScreenLayer Screen::getLayer() const {
    return layer;
}

void Screen::setLayer(ScreenLayer layer) {
    this->layer = layer;
}

bool Screen::isMostFrontScreen() const {
    if(this->parent != nullptr){
        return this->parent->isMostFrontScreen(this);
    }
    return false;
}

void Screen::initialize() {
    initialized = true;
}

void Screen::finalize() {

}

void Screen::update(float elapsedTime) {
    if(!initialized){
        cerr << "Call to Screen::update before screen is initialized. IF IT CRASHES IT IS YOUR FAULT!!!" << endl;
    }
}

void Screen::render() {
    if(!initialized){
        cerr << "Call to Screen::render before screen is initialized. IF IT CRASHES IT IS YOUR FAULT!!!" << endl;
    }
}

