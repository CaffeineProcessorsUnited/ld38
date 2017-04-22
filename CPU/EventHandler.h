//
// Created by nox on 4/22/17.
//

#ifndef LD38_EVENTHANDLER_H
#define LD38_EVENTHANDLER_H

#include "gameplay.h"

#include "Common.h"

namespace CPU {

    using namespace gameplay;

    class EventHandler {
    public:
        virtual void keyPress(Keyboard::Key key) {};
        virtual void keyRelease(Keyboard::Key key) {};
        virtual void keyChar(Keyboard::Key key) {};

        virtual void mousePress(MouseButton button, int x, int y) {};
        virtual void mouseRelease(MouseButton button, int x, int y) {};
        virtual void mouseMove(int x, int y) {};
        virtual void mouseScrolled(int wheelData) {};

        virtual void touchPress(int x, int y, unsigned int contactIndex) {};
        virtual void touchRelease(int x, int y, unsigned int contactIndex) {};
        virtual void touchMove(int x, int y, unsigned int contactIndex) {};
    };
}

#endif //LD38_EVENTHANDLER_H
