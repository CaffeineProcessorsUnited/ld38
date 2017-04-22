//
// Created by niels on 17.04.17.
//

#ifndef LDTEST_TESTSCREEN_H
#define LDTEST_TESTSCREEN_H

#include "src/gamelogic/World.h"
#include "src/worldobjects/RandomCloud.h"
#include "src/worldobjects/Unicorn.h"

#include "CPU/CPU.h"
using namespace CPU;

class TestScreen: public ScreenForm {
    CPU::SpriteBatch *_batch;
    World *world;
    vector<RandomCloud*> clouds;
    RandomCloud *myCloud;
    Unicorn *unicorn;
public:
    virtual void resize(int width, int height) override;

    TestScreen(ScreenManager *parent);

    void initialize() override;
    void finalize() override;
    void update(float elapsedTime) override;
    void render() override;
    void keyRelease(Keyboard::Key key) override;
    void mouseMove(int x, int y) override;

    void mouseScrolled(int wheelData) override;

    virtual void touchPress(int x, int y, unsigned int contactIndex) override;
    virtual void touchRelease(int x, int y, unsigned int contactIndex) override;
    virtual void touchMove(int x, int y, unsigned int contactIndex) override;
};


#endif //LDTEST_TESTSCREEN_H
