#include "MainMenuState.h"

// Initializer functions
void MainMenuState::initVariables()
{
    /* Scale sizes */
    start_x *= scale_x;
    start_y *= scale_y;
    distance_x *= scale_x;
    distance_y *= scale_x;
    characterSize *= scale_x * scale_y;
}

void MainMenuState::initBackground()
{
    this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));

    if (!this->backgroundTexture.loadFromFile("Resources/Images/menu_background.png"))
    {
        throw "ERROR::MAIN MENU STATE::FAILED TO LOAD BACKGROUND TEXTURE";
    }
    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAIN MENU STATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("Config/mainMenuState_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void MainMenuState::initButtons()
{

    this->buttons["Hash Table"] = new Button(
        start_x + 0 * distance_x, start_y + 0 * distance_y, scale_x, scale_y,
        &this->font, "Hash Table", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        0
    ); 

    this->buttons["AVL Tree"] = new Button(
        start_x + 0 * distance_x, start_y + 1 * distance_y, scale_x, scale_y,
        &this->font, "AVL Tree", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        0
    );

    this->buttons["Heap Min"] = new Button(
        start_x + 0 * distance_x, start_y + 2 * distance_y, scale_x, scale_y,
        &this->font, "Min Heap", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        0
    );

    this->buttons["Heap Max"] = new Button(
        start_x + 0 * distance_x, start_y + 3 * distance_y, scale_x, scale_y,
        &this->font, "Max Heap", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        0
    );

    this->buttons["234 Tree"] = new Button(
        start_x + 1 * distance_x, start_y + 0 * distance_y, scale_x, scale_y,
        &this->font, "234 Tree", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        0
    );

    this->buttons["Trie"] = new Button(
        start_x + 1 * distance_x, start_y + 1 * distance_y, scale_x, scale_y,
        &this->font, "Trie", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        0
    );

    this->buttons["Graph"] = new Button(
        start_x + 1 * distance_x, start_y + 2 * distance_y, scale_x, scale_y,
        &this->font, "Graph", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), 
        0
    );

    this->buttons["Quit"] = new Button(
        start_x + 1 * distance_x, start_y + 3 * distance_y, scale_x, scale_y,
        &this->font, "Quit", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        0
    );
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void MainMenuState::updateInput(const float &dt)
{
}


void MainMenuState::updateCursor()
{   
    /* Update all the buttons */
    isHandCursor = false;
    for (auto &it : this->buttons)
    {
        it.second->update(isHandCursor);
    }

    /*  Show Mouse Cursor */
    if (isHandCursor)
    {
        this->window->setMouseCursor(handCursor);
    }
    else
    {
        this->window->setMouseCursor(arrowCursor);
    }
}

void MainMenuState::updateButtons()
{
    //AVL Tree
    if (this->buttons["AVL Tree"]->isPressed())
    {
        this->states->push(new AVL(this->window, this->supportedKeys, this->states));
    }

    // Heap
    if (this->buttons["Heap Min"]->isPressed())
    {
        this->states->push(new Heap(this->window, this->supportedKeys, this->states));
    }

    // Heap Max
    if (this->buttons["Heap Max"]->isPressed())
    {
        this->states->push(new HeapMax(this->window, this->supportedKeys, this->states));
    }

    // Hash
    if (this->buttons["Hash Table"]->isPressed())
    {
        this->states->push(new Hash(this->window, this->supportedKeys, this->states));
    }

    // Trie
    if (this->buttons["Trie"]->isPressed())
    {
        this->states->push(new Trie(this->window, this->supportedKeys, this->states));
    }

    //Graph
    if (this->buttons["Graph"]->isPressed())
    {
        this->states->push(new Graph(this->window, this->supportedKeys, this->states));
    }

    // 234 Tree
    if (this->buttons["234 Tree"]->isPressed())
    {
        this->states->push(new Tree234(this->window, this->supportedKeys, this->states));
    }

    // Quit the game
    if (this->buttons["Quit"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::updateSFMLEvents(const float &dt, sf::Event& event)
{
    for (auto &it : this->buttons)
    {
        it.second->updateSFMLEvents(dt, event, this->mousePosView);
    }
}

void MainMenuState::update(const float &dt)
{
    this->window->setTitle("Data Structure Visualization");
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateCursor();
    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget *target)
{
    /* Render all buttons */
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget *target)
{
    if (!target)
    {
        target = this->window;
    }
    target->draw(this->background);
    this->renderButtons(target);
}
