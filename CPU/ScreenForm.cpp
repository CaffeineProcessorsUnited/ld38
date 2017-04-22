//
// Created by niels on 17.04.17.
//

#include "ScreenForm.h"

using namespace CPU;

template<typename T, typename U>
bool instanceOf(T* t){
    return nullptr != dynamic_cast<U*>(t);
};

ScreenForm::ScreenForm(CPU::ScreenManager *parent):
        Screen(parent),
        Control::Listener(),
        form(NULL)
{
}

ScreenForm::~ScreenForm() {
    if(form != nullptr){
        SAFE_RELEASE(form);
    }
}

void ScreenForm::update(float elapsedTime) {
    Screen::update(elapsedTime);
    if(form != nullptr){
        form->update(elapsedTime);
    }
}

void ScreenForm::render() {
    Screen::render();
    if(form != nullptr){
        form->draw();
    }
}

void ScreenForm::resize(int width, int height) {
    Screen::resize(width, height);
}


void ScreenForm::loadForm(const string &filename) {
    if(form != nullptr){
        SAFE_RELEASE(form);
    }
    form = Form::create(filename.c_str());
}

void ScreenForm::registerFormControl(const string& element) {
    Control* control = form->getControl(element.c_str());

    Control::Listener::EventType listener = static_cast<Control::Listener::EventType>(
            Control::Listener::PRESS |
            Control::Listener::RELEASE |
            Control::Listener::CLICK |
            Control::Listener::MIDDLE_CLICK |
            Control::Listener::RIGHT_CLICK |
            Control::Listener::ACTIVATED |
            Control::Listener::FOCUS_GAINED |
            Control::Listener::FOCUS_LOST
    );

    if(instanceOf<Control,Slider>(control) ||
            instanceOf<Control,CheckBox>(control) ||
            instanceOf<Control,RadioButton>(control))
    {
        listener = static_cast<Control::Listener::EventType>(listener | Control::Listener::VALUE_CHANGED);
    }
    if(instanceOf<Control,TextBox>(control)){
        listener = static_cast<Control::Listener::EventType>(listener | Control::Listener::TEXT_CHANGED);
    }

    control->addListener(this, listener);
}
void ScreenForm::controlEvent(Control* control, Control::Listener::EventType evt) {
    switch(evt){
        case Control::Listener::PRESS:
            controlPress(control);
            break;
        case Control::Listener::RELEASE:
            controlRelease(control);
            break;
        case Control::Listener::CLICK:
        case Control::Listener::MIDDLE_CLICK:
        case Control::Listener::RIGHT_CLICK:
            controlClick(control);
            break;
        case Control::Listener::VALUE_CHANGED:
        case Control::Listener::TEXT_CHANGED:
            controlChanged(control);
            break;
        case Control::Listener::ACTIVATED:
            controlActivated(control);
            break;
        case Control::Listener::FOCUS_GAINED:
            controlFocusGained(control);
            break;
        case Control::Listener::FOCUS_LOST:
            controlFocusLost(control);
            break;
    }
}
void ScreenForm::controlPress(Control* control) {

}
void ScreenForm::controlRelease(Control* control) {

}
void ScreenForm::controlClick(Control* control) {

}
void ScreenForm::controlChanged(Control* control) {

}
void ScreenForm::controlActivated(Control* control) {

}
void ScreenForm::controlFocusGained(Control* control) {

}
void ScreenForm::controlFocusLost(Control* control) {

}



