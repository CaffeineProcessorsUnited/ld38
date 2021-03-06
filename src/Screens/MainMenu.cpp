//
// Created by bene on 24.04.17.
//

#include "MainMenu.h"

MainMenu::MainMenu(ScreenManager *parent) :
    ScreenForm(parent)
{
}

void MainMenu::initialize() {
    ScreenForm::initialize();
    loadForm("res/mainmenu.form");
    registerFormControl("startButton");
}

void MainMenu::update(float elapsedTime) {
    if(!isInitialized() )
        return;
    ScreenForm::update(elapsedTime);
}

void MainMenu::render() {
    if(!isVisible() || !isInitialized() )
        return;
    ScreenForm::render();
}

void MainMenu::controlClick(Control* control){
    if(strcmp(control->getId(),"startButton") == 0){
        cout << "Start Button Pressed! Yay!" << endl;
        testScreen = getParent()->createScreen<TestScreen>(BACK, false);
        testScreen->initialize();
        testScreen->show();
        setVisible(false);
        testScreen->update(0);


    }
}

