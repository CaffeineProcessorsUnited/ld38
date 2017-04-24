//
// Created by bene on 24.04.17.
//

#ifndef LD38_MAINMENU_H
#define LD38_MAINMENU_H
#include "CPU/CPU.h"
#include "TestScreen.h"

using namespace CPU;

class MainMenu: public ScreenForm {

public:
    MainMenu(ScreenManager *parent);
    TestScreen *testScreen;
    void initialize() override;
    void update(float delta_time) override;
    void render() override;
    virtual void controlClick(Control* control) override;


};

#endif //LD38_MAINMENU_H
