//
// Created by niels on 17.04.17.
//

#ifndef CPU_SCREENFORM_H
#define CPU_SCREENFORM_H

#include "gameplay.h"
#include "Screen.h"

namespace CPU {
    using namespace CPU;
    class ScreenForm : public Screen, public Control::Listener {
        Form *form;

    public:
        ScreenForm(ScreenManager *parent = NULL);
        ~ScreenForm();

        void update(float elapsedTime) override ;
        void render() override;


        void loadForm(const string& filename);
        void registerFormControl(const string& element);

        virtual void controlEvent(Control* control, Control::Listener::EventType evt);
        virtual void controlPress(Control* control);
        virtual void controlRelease(Control* control);
        virtual void controlClick(Control* control);
        virtual void controlChanged(Control* control);
        virtual void controlActivated(Control* control);
        virtual void controlFocusGained(Control* control);
        virtual void controlFocusLost(Control* control);
    };
}

#endif //CPU_SCREENFORM_H
