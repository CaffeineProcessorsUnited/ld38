//
// Created by niels on 17.04.17.
//

#ifndef LDTEST_TESTSCREEN_H
#define LDTEST_TESTSCREEN_H

#include "CPU/CPU.h"
using namespace CPU;

class TestScreen: public ScreenForm {
    CPU::SpriteBatch *_batch;
public:
    TestScreen(ScreenManager *parent);

    void initialize() override;
    void finalize() override;
    void update(float elapsedTime) override;
    void render() override;
    void keyRelease(Keyboard::Key key) override;
    void mouseMove(int x, int y) override;

    void mouseScrolled(int wheelData) override;
};


#endif //LDTEST_TESTSCREEN_H
