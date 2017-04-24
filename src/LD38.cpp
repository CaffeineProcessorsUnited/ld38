#include "LD38.h"

// Declare our game instance
LD38 game;

LD38::LD38():
    App(),
    testScreen(NULL)
{
}

void LD38::initialize()
{
    App::initialize();
    testScreen = getScreenManager()->createScreen<TestScreen>(BACK, false);
    testScreen->show();

    setShowFPS(true);
    Game::setVsync(false);

    App::postInitialize();
    resizeEvent(game.getWidth(), game.getHeight());
}

void LD38::finalize()
{
    App::finalize();

    SAFE_RELEASE(testScreen);
}

void LD38::update(float elapsedTime)
{
    if(!isInitialized())
        return;
    App::update(elapsedTime / 1000.0f); // Turn into seconds
}

void LD38::preRender() {
    App::preRender();
}

void LD38::render(float elapsedTime)
{
    App::render(elapsedTime);
}

void LD38::keyEvent(Keyboard::KeyEvent evt, int key)
{
    App::keyEvent(evt,key);

    if (evt == Keyboard::KEY_PRESS)
    {
        switch (key)
        {
            case Keyboard::KEY_ESCAPE:
                exit();
                break;
        }
    }
}

void LD38::resizeEvent(unsigned int width, unsigned int height) {
    App::resizeEvent(width, height);
}

