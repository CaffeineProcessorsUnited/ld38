//
// Created by niels on 17.04.17.
//

#ifndef CPU_SCENE_H
#define CPU_SCENE_H

#include "gameplay.h"


#ifndef CPU_SCREENMANAGER_H
namespace CPU {
    class Screen;
}
#include "ScreenManager.h"
#endif

#include "Common.h"
#include "CPU/EventHandler.h"

namespace CPU {
    using namespace gameplay;
    class Screen : public Ref, public EventHandler  {
        ScreenManager *parent;
        bool visible;
        ScreenLayer layer;
        bool initialized;

    public:
        Screen(ScreenManager *parent = NULL);
        virtual ~Screen();

        void setParent(ScreenManager *parent);
        ScreenManager * getParent() const;

        bool isInitialized() const;
        void show();
        void hide();
        void setVisible(bool visible);
        bool isVisible() const;

        virtual void resize(int width, int height);

        void raise();
        void lower();
        void moveToBack();
        void moveToFront();
        virtual void setLayer(ScreenLayer layer);
        virtual ScreenLayer getLayer() const;
        bool isMostFrontScreen() const;

        virtual void initialize();
        virtual void finalize();
        virtual void update(float elapsedTime);
        virtual void render();

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

#endif //CPU_SCENE_H
