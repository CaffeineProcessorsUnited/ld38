#ifndef LD38_H_
#define LD38_H_

#include "Screens/TestScreen.h"
#include "CPU/CPU.h"

using namespace CPU;

/**
 * Main game class.
 */
class LD38: public App
{
public:
    LD38();
protected:
    virtual void resizeEvent(unsigned int width, unsigned int height) override;
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
