//
// Created by niels on 17.04.17.
//

#ifndef LDTEST_APP_H
#define LDTEST_APP_H

#include "CPU.h"
using namespace CPU;

namespace CPU {
    class App: public Game {
        bool showFPS;
        Font *fontFPS;
        ScreenManager *manager;
    protected:
        ScreenManager* getScreenManager();

        //Override this to initialize GamePlay elements. DO NOT initialize those in the constructor
        virtual void initialize() override;

        //Override this to destroy GamePlay elements. DO NOT destroy those in the destructor
        virtual void finalize() override;

        //Override this to update your state between frames.
        virtual void update(float elapsedTime) override;

        //Override this to draw before the ScreenManager draws
        virtual void preRender();

        //Do not override. Overriding this causes you to draw before preRender of after postRender.
        virtual void render(float elapsedTime) override;

        //Override this to draw after the ScreenManager draws
        virtual void postRender();

        //Override this to customize the display of frame rate
        virtual void drawFrameRate();

        virtual void resizeEvent(unsigned int width, unsigned int height) override;
    public:
        App();

        void keyEvent(Keyboard::KeyEvent evt, int key) override;
        bool mouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta) override;
        void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex) override;
        void setShowFPS(bool show);
        bool isShowFPS() const;
    };
}

#endif //LDTEST_APP_H
