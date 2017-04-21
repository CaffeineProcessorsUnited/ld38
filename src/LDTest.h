#ifndef LDTest_H_
#define LDTest_H_

#include "Screens/TestScreen.h"
#include "CPU/CPU.h"

using namespace CPU;

/**
 * Main game class.
 */
class LDTest: public App
{
public:
    LDTest();
    void keyEvent(Keyboard::KeyEvent evt, int key);
    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

protected:
    void initialize();
    void finalize();
    void update(float elapsedTime);

    void preRender() override;
    void render(float elapsedTime);

private:
    bool drawScene(Node* node);

    Scene* _scene;
    bool _wireframe;
    TestScreen *testScreen;
};

#endif
