#include "LD38.h"

// Declare our game instance
LD38 game;

LD38::LD38():
    App(),
    _scene(NULL),
    _wireframe(false),
    testScreen(NULL)
{
}

void LD38::initialize()
{
    App::initialize();

    // Load game scene from file
    _scene = Scene::load("res/demo.scene");
    float aspect = game.getWidth() / game.getHeight();
    Camera* camera = Camera::createOrthographic(1920, 1080, aspect, 0.2, 100);
    _scene->setActiveCamera(camera);

    // Get the box model and initialize its material parameter values and bindings
    Node* boxNode = _scene->findNode("box");
    boxNode->scale(100);
    Model* boxModel = dynamic_cast<Model*>(boxNode->getDrawable());
    Material* boxMaterial = boxModel->getMaterial();

    testScreen = getScreenManager()->createScreen<TestScreen>(BACK, true);

    setShowFPS(true);
    Game::setVsync(false);

    App::postInitialize();
    resizeEvent(game.getWidth(), game.getHeight());
}

void LD38::finalize()
{
    App::finalize();

    SAFE_RELEASE(_scene);
    SAFE_RELEASE(testScreen);
}

void LD38::update(float elapsedTime)
{
    if(!isInitialized())
        return;
    App::update(elapsedTime / 1000.0f); // Turn into seconds

    _scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
}

void LD38::preRender() {
    App::preRender();

    _scene->visit(this, &LD38::drawScene);
}

void LD38::render(float elapsedTime)
{
    App::render(elapsedTime);
}

bool LD38::drawScene(Node* node)
{
    // If the node visited contains a drawable object, draw it
    Drawable* drawable = node->getDrawable();
    if (drawable)
        drawable->draw(_wireframe);

    return true;
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

void LD38::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    switch (evt)
    {
        case Touch::TOUCH_PRESS:
            _wireframe = !_wireframe;
            break;
    };
    App::touchEvent(evt, x, y, contactIndex);
}

void LD38::resizeEvent(unsigned int width, unsigned int height) {
    App::resizeEvent(width, height);
}

