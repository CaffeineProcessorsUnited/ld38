//
// Created by niels on 17.04.17.
//

#ifndef CPU_SCREENMANAGER_H
#define CPU_SCREENMANAGER_H

#include <vector>
#include "gameplay.h"

#ifndef CPU_SCENE_H
namespace CPU {
    class ScreenManager;
}
#include "Screen.h"
#endif
#include "Common.h"

using namespace CPU;

namespace CPU {
    using namespace std;
    using namespace gameplay;

    class ScreenManager: public Ref {
        vector<Screen*> screens;
    public:
        ScreenManager();
        ~ScreenManager();
        bool contains(const Screen * screen)const;
        void add(Screen* screen);
        void remove(Screen* screen);

        void keyPress(Keyboard::Key key);
        void keyRelease(Keyboard::Key key);
        void keyChar(Keyboard::Key key);

        void mousePress(MouseButton button, int x, int y);
        void mouseRelease(MouseButton button, int x, int y);
        void mouseMove(int x, int y);
        void mouseScrolled(int wheelData);

        void keyEvent(Keyboard::KeyEvent evt, int key);
        void mouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta);

        void update(float elapsedTime);
        void render();
        void resize(unsigned int width, unsigned int height);


        bool isMostFrontScreen(const Screen * screen) const;

        template<typename T>
        T* getByClass(){
            vector<Screen*>::const_iterator elem = screens.cbegin();
            vector<Screen*>::const_iterator it = screens.cbegin();
            for(;it != screens.cend(); ++it){
                T* t = const_cast<T>(*it);
                if(t != nullptr){
                    return t;
                }
            }
            return nullptr;
        };

        template <typename T>
        T* createScreen(ScreenLayer layer = BACK, bool visible=false){
            T* t = new T(this);
            t->initialize();
            t->setLayer(layer);
            t->setVisible(visible);
            return t;
        };
    };
}


#endif //CPU_SCREENMANAGER_H
