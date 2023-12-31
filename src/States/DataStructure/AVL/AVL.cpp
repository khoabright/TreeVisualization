#include "AVL.h"

AVL::AVL(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : DataStructure(window, supportedKeys, states)
{
    auto AVLScale = [&]()
    {
        nodeDistanceX *= scale_x;
        nodeDistanceY *= scale_y;
    };

    auto childButtonScale = [&]()
    {
        childButtonOriginX *= scale_x;
        childButtonOriginY *= scale_y;
        childButtonWidth *= scale_x;
        childButtonHeight *= scale_y;
        childButtonCharacterSize *= scale_y;
        childButtonDistanceX *= scale_x;
    };

    auto inputFieldScale = [&]()
    {
        inputFieldOriginX *= scale_x;
        inputFieldOriginY *= scale_y;
        inputFieldWidth *= scale_x;
        inputFieldHeight *= scale_y;
        inputFieldCharacterSize *= scale_y;
        inputFieldDistanceX *= scale_x;
    };

    childButtonScale();
    inputFieldScale();
    AVLScale();

    this->initHighlightCode();
    this->initTriggerFunction();
    this->initChildButtons();
    this->initInputFields();
    this->initAnimation();

    reset();
}

AVL::~AVL()
{
    this->DeleteNodePointers();
    delete (this->animationAVL);
}

void AVL::DeleteNodePointers()
{
    for (auto &v : this->Nodes)
    {
        delete (v);
    }
    this->Nodes.clear();
}

/* Init */
void AVL::initTriggerFunction()
{
    auto InstructionButtons = [&]()
    {
        this->triggerFunction["Theme"] = std::bind(&AVL::button_theme, this);
        this->triggerFunction["Initialize"] = std::bind(&AVL::button_initialize, this);
        this->triggerFunction["Add"] = std::bind(&AVL::button_add, this);
        this->triggerFunction["Delete"] = std::bind(&AVL::button_delete, this);
        this->triggerFunction["Update"] = std::bind(&AVL::button_update, this);
        this->triggerFunction["Search"] = std::bind(&AVL::button_search, this);
        this->triggerFunction["Quit"] = std::bind(&AVL::button_quit, this);
        this->triggerFunction["SpeedMinus"] = std::bind(&AVL::button_SpeedMinus, this);
        this->triggerFunction["SpeedPlus"] = std::bind(&AVL::button_SpeedPlus, this);
        this->triggerFunction["CodeSwitch"] = std::bind(&AVL::button_CodeSwitch, this);
    };

    auto RunButtons = [&]()
    {
        this->triggerFunction["First"] = std::bind(&AVL::button_first, this);
        this->triggerFunction["Prev"] = std::bind(&AVL::button_prev, this);
        this->triggerFunction["Pause"] = std::bind(&AVL::button_pause, this);
        this->triggerFunction["Play"] = std::bind(&AVL::button_play, this);
        this->triggerFunction["Replay"] = std::bind(&AVL::button_replay, this);
        this->triggerFunction["Next"] = std::bind(&AVL::button_next, this);
        this->triggerFunction["Last"] = std::bind(&AVL::button_last, this);
    };

    InstructionButtons();
    RunButtons();
}

void AVL::initChildButtons()
{
    int idy = -1;

    auto init_theme = [&]()
    {
        ++idy;
        this->childButtons["Theme"].insert({"1Standard", nullptr});
        this->childButtons["Theme"].insert({"2Sky", nullptr});
        this->childButtons["Theme"].insert({"3Desert", nullptr});

        int idx = 0;
        for (auto &it : this->childButtons["Theme"])
        {
            it.second = new Button(
                this->childButtonOriginX + (idx++) * (this->childButtonDistanceX + this->childButtonWidth),
                this->childButtonOriginY + idy * (this->childButtonDistanceY + this->childButtonHeight),
                this->scale_x, this->scale_y,
                &this->font, it.first.substr(1), (int)(scale_y * 16.f),
                sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(240, 180, 10, 255),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(150, 150, 150, 255),
                1, this->childButtonWidth, this->childButtonHeight);
        }
        this->childButtons["Theme"]["1Standard"]->instantTrigger = true;
        this->childButtons["Theme"]["2Sky"]->instantTrigger = true;
        this->childButtons["Theme"]["3Desert"]->instantTrigger = true;
    };

    auto init_initialize = [&]()
    {
        ++idy;
        this->childButtons["Initialize"].insert({"1Empty", nullptr});
        this->childButtons["Initialize"].insert({"2Random", nullptr});
        this->childButtons["Initialize"].insert({"3Load File", nullptr});

        int idx = 0;
        for (auto &it : this->childButtons["Initialize"])
        {
            it.second = new Button(
                this->childButtonOriginX + (idx++) * (this->childButtonDistanceX + this->childButtonWidth),
                this->childButtonOriginY + idy * (this->childButtonDistanceY + this->childButtonHeight),
                this->scale_x, this->scale_y,
                &this->font, it.first.substr(1), (int)(scale_y * 16.f),
                sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(240, 180, 10, 255),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(150, 150, 150, 255),
                1, this->childButtonWidth, this->childButtonHeight);
        }
        this->childButtons["Initialize"]["1Empty"]->instantTrigger = true;
        this->childButtons["Initialize"]["3Load File"]->instantTrigger = true;
    };

    auto init_add = [&]() {
    };

    auto init_delete = [&]() {
    };

    auto init_update = [&]() {
    };

    auto init_search = [&]() {
    };

    init_theme();
    init_initialize();
    init_add();
    init_delete();
    init_update();
    init_search();
}

void AVL::initInputFields()
{
    int idy = -1;

    auto init_initialize = [&]()
    {
        ++idy;
        this->inputFields["Initialize"].insert({"1Empty", nullptr});
        this->inputFields["Initialize"].insert({"2Random", nullptr});
        this->inputFields["Initialize"].insert({"3Load File", nullptr});

        int idx = 0;
        for (auto &it : this->inputFields["Initialize"])
        {
            it.second = new InputField(this->inputFieldOriginX + (idx++) * (this->inputFieldWidth + this->inputFieldDistanceX),
                                       this->inputFieldOriginY + idy * (this->inputFieldHeight + this->inputFieldDistanceY),
                                       this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                       &this->font, this->inputFieldCharacterSize,
                                       sf::Color::White, sf::Color::White, sf::Color::Black);
        }

        this->inputFields["Initialize"]["1Empty"]->disabled = true;
        this->inputFields["Initialize"]["3Load File"]->disabled = true;
    };

    auto init_add = [&]()
    {
        ++idy;
        this->inputFields["Add"]["1Head"] = new InputField(this->inputFieldOriginX,
                                                           this->inputFieldOriginY + (idy - 1) * (this->inputFieldHeight + this->inputFieldDistanceY),
                                                           this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                                           &this->font, this->inputFieldCharacterSize,
                                                           sf::Color::White, sf::Color::White, sf::Color::Black);
    };

    auto init_delete = [&]()
    {
        ++idy;
        this->inputFields["Delete"]["1Head"] = new InputField(this->inputFieldOriginX,
                                                              this->inputFieldOriginY + (idy - 1) * (this->inputFieldHeight + this->inputFieldDistanceY),
                                                              this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                                              &this->font, this->inputFieldCharacterSize,
                                                              sf::Color::White, sf::Color::White, sf::Color::Black);
    };

    auto init_update = [&]()
    {
        ++idy;
        this->inputFields["Update"]["1Update"] = new InputField(this->inputFieldOriginX,
                                                                this->inputFieldOriginY + (idy - 1) * (this->inputFieldHeight + this->inputFieldDistanceY),
                                                                this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                                                &this->font, this->inputFieldCharacterSize,
                                                                sf::Color::White, sf::Color::White, sf::Color::Black);
    };

    auto init_search = [&]()
    {
        ++idy;
        this->inputFields["Search"]["1Search"] = new InputField(this->inputFieldOriginX,
                                                                this->inputFieldOriginY + (idy - 1) * (this->inputFieldHeight + this->inputFieldDistanceY),
                                                                this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                                                &this->font, this->inputFieldCharacterSize,
                                                                sf::Color::White, sf::Color::White, sf::Color::Black);
    };

    init_initialize();
    init_add();
    init_delete();
    init_update();
    init_search();
}

void AVL::initAnimation()
{
    this->animation = new AnimationAVL(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationAVL = dynamic_cast<AnimationAVL *>(this->animation);
    assert(animationAVL != nullptr);
    this->animationAVL->animationTime = float(speedGap * maxSpeed) / currentSpeed;
}

void AVL::initHighlightCode()
{
    codeHighlight = new CodeHighlight(scale_x, scale_y, &Colors);
}

void AVL::button_theme()
{

    if (this->choosingChildButton == "1Standard")
    {
        this->newStepTriggered = 0;
        this->DataStructureThemeStandard();
        for (auto &it : Nodes)
            it->updateColor();
        this->choosingButton = "";
        return;
    }
    if (this->choosingChildButton == "2Sky")
    {
        this->newStepTriggered = 0;
        this->DataStructureThemeSky();
        for (auto &it : Nodes)
            it->updateColor();
        this->choosingButton = "";
        return;
    }
    if (this->choosingChildButton == "3Desert")
    {
        this->newStepTriggered = 0;
        this->DataStructureThemeDesert();
        for (auto &it : Nodes)
            it->updateColor();
        this->choosingButton = "";
        return;
    }

    return;
}

/* Instruction Buttons */
void AVL::button_initialize()
{
    auto createNewNode = [&](int newValue)
    {
        // if (this->head == nullptr)
        // {
        //     this->head = new AVLNode(this->start_x, this->start_y, this->scale_x, this->scale_y, 12, &this->font, &this->Colors);
        //     this->Nodes.push_back(this->head);
        //     ++this->numberNode;

        //     this->head->val = newValue;
        //     this->tail = head;
        //     return;
        // }
        // /* Add to tail */
        // AVLNode *newNode = new AVLNode(this->start_x, this->start_y, this->scale_x, this->scale_y, 12, &this->font, &this->Colors);
        // this->Nodes.push_back(newNode);
        // ++this->numberNode;

        // newNode->val = newValue;
        // this->tail->next = newNode;
        // this->tail = newNode;
    };

    if (this->choosingChildButton == "1Empty")
    {
        if (!this->newStepTriggered)
            return;
        this->newStepTriggered = 0;

        this->reset();
        return;
    }

    if (this->choosingChildButton == "2Random")
    {
        if (this->newStepTriggered)
        {
            this->newStepTriggered = 0;
            this->inputGuide.setString("");
            if (this->valueFirst > maxNode)
            {
                this->inputWarning.setString("Sorry, the maximum size is " + std::to_string(maxNode));
                return;
            }
        }
        else
        {
            this->inputGuide.setString("Input a size");
            return;
        }

        this->reset();
        prepareNewInstruction();

        auto addHighlightCodes = [&]
        {
            codeHighlight->introText.setString("Random AVLTree with " + std::to_string(valueFirst) + " node" + (valueFirst > 1 ? "s" : ""));
            codeHighlight->codeStrings.resize(100); // fake highlight
            this->codeHighlight->updateTexts();
        };
        std::vector<int> values(200);
        for (int i = 0; i < 200; ++i)
            values[i] = i + 1;
        std::shuffle(values.begin(), values.end(), this->randomize);
        for (int i = 0; i < this->valueFirst; ++i)
        {
            int newValue = values[i];
            assert(this->exist[newValue] == 0);
            this->exist[newValue] = 1;
    
            this->animationAVL->newInstruction(this->root->next[0], this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
            addHighlightCodes();
            insertAVLNode(root, root, newValue);
        }
        // this->animationAVL->updateNodePosition(this->root, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
        return;
    }

    if (this->choosingChildButton == "3Load File")
    {
        if (!this->newStepTriggered)
            return;
        this->newStepTriggered = 0;

        this->reset();
        prepareNewInstruction();

        auto addHighlightCodes = [&]
        {
            codeHighlight->introText.setString("Load tree from file");
            codeHighlight->codeStrings.resize(100); // fake highlight
            this->codeHighlight->updateTexts();
        };

        std::ifstream inp;
        inp.open("InputFiles/inputAVL.txt");
        int newValue = 0;
        while (inp >> newValue)
        {
            if (this->exist[newValue])
            {
                this->inputWarning.setString("No duplicate vertex allowed!");
                return;
            }
            this->exist[newValue] = 1;
            this->animationAVL->newInstruction(this->root->next[0], this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
            addHighlightCodes();
            insertAVLNode(root, root, newValue);
        }
        inp.close();

        // this->animationAVL->updateNodePosition(this->head, this->tail, this->start_x, this->start_y, this->nodeDistanceX);
        return;
    }
}

void AVL::button_add()
{
    this->choosingChildButton = "1Head";

    if (this->newStepTriggered)
    {
        this->newStepTriggered = 0;
        this->inputGuide.setString("");

        /* Use thread because the animation should run parallel to Rendering*/
        // this->thread_operation = new sf::Thread(&operation_add, std::ref(this->valueFirst));
        // this->thread_operation = new sf::Thread([this]() { operation_add(this->valueFirst); });
        // this->thread_operation->launch();
        this->operation_add(this->valueFirst);

        return;
    }
    else
    {
        this->inputGuide.setString("Input a value");
    }
}

void AVL::button_delete()
{
    this->choosingChildButton = "1Head";

    if (this->newStepTriggered)
    {
        this->newStepTriggered = 0;
        this->inputGuide.setString("");
        this->operation_delete(this->valueFirst);
        return;
    }
    else
    {
        this->inputGuide.setString("Input a value");
    }
}

void AVL::button_update()
{
    this->choosingChildButton = "1Update";

    if (this->newStepTriggered)
    {
        this->newStepTriggered = 0;
        this->inputGuide.setString("");
        this->operation_update(this->valueFirst, this->valueSecond);
        return;
    }
    else
    {
        this->inputGuide.setString("Input [old value, new value] to update");
    }
}

void AVL::button_search()
{
    this->choosingChildButton = "1Search";

    if (this->newStepTriggered)
    {
        this->newStepTriggered = 0;
        this->inputGuide.setString("");
        this->operation_search(this->valueFirst);
        return;
    }
    else
    {
        this->inputGuide.setString("Input a value to search");
    }
}

void AVL::button_quit()
{
    this->endState();
}

// AVL Operations
int AVL::heightAVL(AVLNode *node)
{
    if (node == NULL)
        return 0;
    return node->heightAVL;
}

AVLNode *AVL::newAVLNode(int key, AVLNode *parentNode)
{
    int posX = start_x, posY = start_y;
    if (numberNode > 0)
    {
        posX -= 3 * nodeDistanceX;
    }

    AVLNode *newNode = new AVLNode(posX, posY, scale_x, scale_y, key, &font, &Colors);
    newNode->key = key;
    newNode->heightAVL = 1;
    this->Nodes.push_back(newNode);
    this->animationAVL->instructions.push_back({[this, newNode]()
                                                { this->animationAVL->showNode(newNode, "1", this->numberNode, {0}); },
                                                [this, parentNode]()
                                                { this->animationAVL->highlightCurrentNode(parentNode, "normal", {0}); }});
    waitAnimation();

    return (newNode);
}

AVLNode *AVL::rightRotate(AVLNode *y, int codeLine)
{
    AVLNode *x = y->next[0];
    AVLNode *T2 = x->next[1];

    x->next[1] = y;
    y->next[0] = T2;
    /* connect function will be called immediately after this */

    y->heightAVL = std::max(heightAVL(y->next[0]),
                            heightAVL(y->next[1])) +
                   1;
    x->heightAVL = std::max(heightAVL(x->next[0]),
                            heightAVL(x->next[1])) +
                   1;

    this->animationAVL->instructions.push_back({[this, x, y, codeLine]()
                                                { this->animationAVL->connectNodes(x, y, 1, {codeLine}); },
                                                [this, y, T2, codeLine]()
                                                { this->animationAVL->connectNodes(y, T2, 0, {codeLine}); },
                                                [this, x, codeLine]()
                                                { this->animationAVL->changeNodeLabel(x, std::to_string(x->heightAVL), {codeLine}); },
                                                [this, y, codeLine]()
                                                { this->animationAVL->changeNodeLabel(y, std::to_string(y->heightAVL), {codeLine}); }});
    waitAnimation();

    // this->animationAVL->instructions.push_back({[this, y, T2]()
    //                                             { this->animationAVL->connectNodes(y, T2, 0, {1}); }});
    // waitAnimation();

    return x;
}

AVLNode *AVL::leftRotate(AVLNode *x, int codeLine)
{
    AVLNode *y = x->next[1];
    AVLNode *T2 = y->next[0];

    y->next[0] = x;
    x->next[1] = T2;

    x->heightAVL = std::max(heightAVL(x->next[0]),
                            heightAVL(x->next[1])) +
                   1;
    y->heightAVL = std::max(heightAVL(y->next[0]),
                            heightAVL(y->next[1])) +
                   1;

    this->animationAVL->instructions.push_back({[this, y, x, codeLine]()
                                                { this->animationAVL->connectNodes(y, x, 0, {codeLine}); },
                                                [this, x, T2, codeLine]()
                                                { this->animationAVL->connectNodes(x, T2, 1, {codeLine}); },
                                                [this, x, codeLine]()
                                                { this->animationAVL->changeNodeLabel(x, std::to_string(x->heightAVL), {codeLine}); },
                                                [this, y, codeLine]()
                                                { this->animationAVL->changeNodeLabel(y, std::to_string(y->heightAVL), {codeLine}); }});
    waitAnimation();

    // this->animationAVL->instructions.push_back({[this, x, T2]()
    //                                             { this->animationAVL->connectNodes(x, T2, 1, {1}); }});
    // waitAnimation();

    return y;
}

int AVL::getBalanceFactor(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return heightAVL(N->next[0]) -
           heightAVL(N->next[1]);
}

AVLNode *AVL::insertAVLNode(AVLNode *curNode, AVLNode *parentNode, int key)
{
    // Find the correct postion and insert the curNode
    if (curNode == NULL)
    {
        return (newAVLNode(key, parentNode));
    }

    /* Highlight path */
    this->animationAVL->instructions.push_back({[this, curNode]()
                                                { this->animationAVL->highlightCurrentNode(curNode, "newColor", {}); },
                                                [this, parentNode]()
                                                { this->animationAVL->highlightCurrentNode(parentNode, "normal", {}); }});
    waitAnimation();

    /* Move down to its subtree and connect */
    if (key == curNode->key) return curNode;
    int direction = (key > curNode->key);
    // curNode->next[direction] = insertAVLNode(curNode->next[direction], key);
    auto *temp = insertAVLNode(curNode->next[direction], curNode, key);
    /* Make connection and highlight current node */
    std::string passColor = (curNode == root) ? "reachColor" : "normal"; // highlight real root node
    this->animationAVL->instructions.push_back({[this, curNode, temp, direction]()
                                                { this->animationAVL->connectNodes(curNode, temp, direction, {direction ? 4 : 2}); },
                                                [this, curNode]()
                                                { this->animationAVL->highlightCurrentNode(curNode, "newColor", {}); },
                                                [this, temp, passColor]()
                                                { this->animationAVL->highlightCurrentNode(temp, passColor, {}); }});
    waitAnimation();

    /* Call animation for update balance factor, then call balancing animation */
    /* If no need balancing => relayout, else simultaneously rotate (only make arrow) and relayout */

    // Update the balance factor of curNode and
    // balance the tree
    curNode->heightAVL = 1 + std::max(heightAVL(curNode->next[0]),
                                      heightAVL(curNode->next[1]));
    this->animationAVL->instructions.push_back({[this, curNode]()
                                                { this->animationAVL->changeNodeLabel(curNode, std::to_string(curNode->heightAVL), {6}); },
                                                [this, curNode]()
                                                { this->animationAVL->highlightCurrentNode(curNode, "normal", {6}); },
                                                [this]()
                                                { this->animationAVL->Relayout((numberNode == 0), root->next[0], start_x, start_y, nodeDistanceX, nodeDistanceY, {6}); }});
    waitAnimation();

    if (curNode == root)
        return nullptr;

    int balanceFactor = getBalanceFactor(curNode);
    if (balanceFactor > 1)
    {
        if (key < curNode->next[0]->key)
        {
            return rightRotate(curNode, 9);
        }
        else if (key > curNode->next[0]->key)
        {
            curNode->next[0] = leftRotate(curNode->next[0], 11);
            return rightRotate(curNode, 12);
        }
    }
    if (balanceFactor < -1)
    {
        if (key > curNode->next[1]->key)
        {
            return leftRotate(curNode, 15);
        }
        else if (key < curNode->next[1]->key)
        {
            curNode->next[1] = rightRotate(curNode->next[1], 17);
            return leftRotate(curNode, 18);
        }
    }
    return curNode;
}

AVLNode *AVL::AVLNodeWithMaxValue(AVLNode *curNode)
{
    AVLNode *current = curNode;
    this->animationAVL->instructions.push_back({[this, curNode]()
                                                { this->animationAVL->highlightCurrentNode(curNode, "passedColor", {5}); }});
    while (current->next[1] != NULL)
    {
        this->animationAVL->instructions.push_back({[this, curNode]()
                                                    { this->animationAVL->highlightCurrentNode(curNode, "normal", {5}); },
                                                    [this, nextNode = curNode->next[1]]()
                                                    { this->animationAVL->highlightCurrentNode(nextNode, "passedColor", {5}); }});
        waitAnimation();
        current = current->next[1];
    }
    return current;
}

AVLNode *AVL::deleteAVLNode(AVLNode *curNode, AVLNode *parentNode, int key)
{
    // Find the AVLNode and delete it
    if (curNode == NULL)
        return curNode;

    std::string currentColor = (key != curNode->key) ? "newColor" : "deleteColor";
    /* Highlight path, also relayout for inverse direction */
    this->animationAVL->instructions.push_back({[this, curNode, currentColor]()
                                                { this->animationAVL->highlightCurrentNode(curNode, currentColor, {5}); },
                                                [this, parentNode]()
                                                { this->animationAVL->highlightCurrentNode(parentNode, "normal", {5}); }, 
                                                [this]()
                                                { this->animationAVL->Relayout((numberNode == 0), root->next[0], start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});
    waitAnimation();

    int direction = (key > curNode->key);

    if (key != curNode->key)
    {
        auto *temp = deleteAVLNode(curNode->next[direction], curNode, key);

        /* Make connection and highlight current node */
        std::string passColor = (curNode == root) ? "reachColor" : "normal"; // highlight real root node

        std::vector<std::function<void()>> temp_vec = {
            [this, curNode, temp, direction]()
            { this->animationAVL->connectNodes(curNode, temp, direction, {5}); },
            [this, curNode]()
            { this->animationAVL->highlightCurrentNode(curNode, "newColor", {5}); }};

        if (temp != nullptr)
            temp_vec.push_back([this, temp, passColor]()
                               { this->animationAVL->highlightCurrentNode(temp, passColor, {5}); });

        this->animationAVL->instructions.push_back(temp_vec);
        waitAnimation();
    }
    else
    {
        if ((curNode->next[0] == NULL) ||
            (curNode->next[1] == NULL))
        {
            AVLNode *temp = curNode->next[0] ? curNode->next[0] : curNode->next[1];
            if (temp == NULL)
            {
                // temp = curNode;
                // curNode = NULL;

                this->animationAVL->instructions.push_back({[this, curNode]()
                                                            { this->animationAVL->hideNode(curNode, numberNode, {5}); }});
                waitAnimation();
                return nullptr;
            }
            else
            {
                //*curNode = *temp;
                this->animationAVL->instructions.push_back({[this, curNode]()
                                                            { this->animationAVL->hideNode(curNode, numberNode, {5}); }});
                waitAnimation();
                return temp;
            }
            // free(temp);
        }
        else
        {
            AVLNode *maxNode = AVLNodeWithMaxValue(curNode->next[0]);
            // curNode->key = maxNode->key;
            this->animationAVL->instructions.push_back({[this, curNode, newVal = maxNode->key]()
                                                        { this->animationAVL->changeNodeValue(curNode, newVal, {5}); },
                                                        [this, curNode, maxNode]()
                                                        { this->animationAVL->highlightCurrentNode(maxNode, "normal", {5}); }});
            waitAnimation();

            // curNode->next[0] = deleteAVLNode(curNode->next[0], curNode, maxNode->key);
            auto *temp = deleteAVLNode(curNode->next[0], curNode, maxNode->key);
            /* Make connection and highlight current node */
            std::string passColor = (curNode == root) ? "reachColor" : "normal"; // highlight real root node
            std::vector<std::function<void()>> temp_vec = {
                [this, curNode, temp]()
                { this->animationAVL->connectNodes(curNode, temp, 0, {5}); },
                [this, curNode]()
                { this->animationAVL->highlightCurrentNode(curNode, "newColor", {5}); }};

            if (temp != nullptr)
                temp_vec.push_back([this, temp, passColor]()
                                   { this->animationAVL->highlightCurrentNode(temp, passColor, {5}); });
            this->animationAVL->instructions.push_back(temp_vec);
            waitAnimation();
        }
    }

    if (curNode == nullptr)
        return curNode;

    // Update the balance factor of each AVLNode and
    // balance the tree
    curNode->heightAVL = 1 + std::max(heightAVL(curNode->next[0]),
                                      heightAVL(curNode->next[1]));
    this->animationAVL->instructions.push_back({[this, curNode]()
                                                { this->animationAVL->changeNodeLabel(curNode, std::to_string(curNode->heightAVL), {5}); },
                                                [this, curNode]()
                                                { this->animationAVL->highlightCurrentNode(curNode, "normal", {5}); },
                                                [this]()
                                                { this->animationAVL->Relayout((numberNode == 0), root->next[0], start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});
    waitAnimation();

    if (curNode == root)
        return nullptr;
    int balanceFactor = getBalanceFactor(curNode);
    if (balanceFactor > 1)
    {
        if (getBalanceFactor(curNode->next[0]) >= 0)
        {
            return rightRotate(curNode);
        }
        else
        {
            curNode->next[0] = leftRotate(curNode->next[0]);
            return rightRotate(curNode);
        }
    }
    if (balanceFactor < -1)
    {
        if (getBalanceFactor(curNode->next[1]) <= 0)
        {
            return leftRotate(curNode);
        }
        else
        {
            curNode->next[1] = rightRotate(curNode->next[1]);
            return leftRotate(curNode);
        }
    }
    return curNode;
}


void AVL::operation_add(int nodeValue)
{
    this->prepareNewInstruction();
    this->button_play();

    auto preCheck = [&]()
    {
        if (nodeValue == -1)
        {
            this->inputWarning.setString("Wrong input format");
            return false;
        }
        if (nodeValue < 1 || nodeValue > 200)
        {
            this->inputWarning.setString("Value should be in range [1..200]");
            return false;
        }

        if (numberNode + 1 > maxNode)
        {
            this->inputWarning.setString("Sorry, maximum size is " + std::to_string(maxNode));
            return false;
        }

        // if (this->exist[nodeValue])
        // {
        //     this->inputWarning.setString("No duplicate vertex allowed!");
        //     return false;
        // }
        return true;
    };
    if (!preCheck())
    {
        return;
    }
    
    this->exist[nodeValue] = 1;

    auto addHighlightCodes = [&]
    {
        codeHighlight->introText.setString("Insert " + std::to_string(nodeValue));
        codeHighlight->codeStrings.push_back("if (node == NULL) return (newNode(key))");   // 0
        codeHighlight->codeStrings.push_back("if (key < node->key)");                      // 1
        codeHighlight->codeStrings.push_back("   node->left = insert(node->left, key)");   // 2
        codeHighlight->codeStrings.push_back("else if (key > node->key)");                 // 3
        codeHighlight->codeStrings.push_back("   node->right = insert(node->right, key)"); // 4
        codeHighlight->codeStrings.push_back("else return node");                          // 5
        codeHighlight->codeStrings.push_back("update node->height");                       // 6
        codeHighlight->codeStrings.push_back("if (balanceFactor > 1)");                    // 7
        codeHighlight->codeStrings.push_back(" if (key < node->left->key)");               // 8
        codeHighlight->codeStrings.push_back("   return rightRotate(node)");               // 9
        codeHighlight->codeStrings.push_back(" else if (key > node->left->key)");          // 10
        codeHighlight->codeStrings.push_back("   node->left = leftRotate(node->left)");    // 11
        codeHighlight->codeStrings.push_back("   return rightRotate(node)");               // 12

        codeHighlight->codeStrings.push_back("if (balanceFactor < -1)");                   // 13
        codeHighlight->codeStrings.push_back(" if (key > node->right->key)");              // 14
        codeHighlight->codeStrings.push_back("   return leftRotate(node)");                // 15
        codeHighlight->codeStrings.push_back(" else if (key < node->right->key)");         // 16
        codeHighlight->codeStrings.push_back("   node->right = rightRotate(node->right)"); // 17
        codeHighlight->codeStrings.push_back("   return leftRotate(node)");                // 18

        codeHighlight->codeStrings.push_back("// Relayout, not in actual operation"); // 19
        this->codeHighlight->updateTexts();
    };
    addHighlightCodes();

    insertAVLNode(this->root, this->root, nodeValue);

    endOperation();
    return;
}

void AVL::operation_delete(int nodeValue)
{
    this->prepareNewInstruction();
    this->button_play();

    auto preCheck = [&]()
    {
        if (nodeValue == -1)
        {
            this->inputWarning.setString("Wrong input format");
            return false;
        }
        if (nodeValue < 1 || nodeValue > 200)
        {
            this->inputWarning.setString("Value should be in range [1..200]");
            return false;
        }

        if (numberNode + 1 > maxNode)
        {
            this->inputWarning.setString("Sorry, the maximum size is " + std::to_string(maxNode));
            return false;
        }

        // if (!this->exist[nodeValue])
        // {
        //     this->inputWarning.setString("No node exist!");
        //     return false;
        // }
        return true;
    };
    if (!preCheck())
    {
        return;
    }

    this->exist[nodeValue] = 0;

    auto addHighlightCodes = [&]
    {
        codeHighlight->introText.setString("Delete " + std::to_string(nodeValue));
        codeHighlight->codeStrings.push_back("Node cur = head");                      // 0
        codeHighlight->codeStrings.push_back("for (i = 0; i < index - 1; ++i)");      // 1
        codeHighlight->codeStrings.push_back("   cur = cur.next");                    // 2
        codeHighlight->codeStrings.push_back("Node nxt = cur.next");                  // 3
        codeHighlight->codeStrings.push_back("Node newNode = new Node(v)");           // 4
        codeHighlight->codeStrings.push_back("newNode.next = nxt");                   // 5
        codeHighlight->codeStrings.push_back("cur.next = newNode");                   // 6
        codeHighlight->codeStrings.push_back("// Relayout, not in actual operation"); // 7
        this->codeHighlight->updateTexts();
    };
    addHighlightCodes();

    // this->animationAVL->instructions.push_back({[this]()
    //                                             { this->animationAVL->Relayout((numberNode == 0), root->next[0], start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});

    deleteAVLNode(this->root, this->root, nodeValue);

    // this->animationAVL->instructions.push_back({[this]()
    //                                             { this->animationAVL->Relayout((numberNode == 0), root->next[0], start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});

    endOperation();
    return;
}

void AVL::operation_search(int nodeValue)
{      
    this->prepareNewInstruction();
    this->button_play();

    auto preCheck = [&]()
    {
        if (nodeValue == -1)
        {
            this->inputWarning.setString("Wrong input format");
            return false;
        }
        if (nodeValue < 1 || nodeValue > 200)
        {
            this->inputWarning.setString("Value should be in range [1..200]");
            return false;
        }

        // if (this->exist[nodeValue])
        // {
        //     this->inputWarning.setString("No duplicate vertex allowed!");
        //     return false;
        // }
        return true;
    };
    if (!preCheck())
    {
        return;
    }

    auto addHighlightCodes = [&]
    {
        codeHighlight->introText.setString("Insert " + std::to_string(nodeValue));
        codeHighlight->codeStrings.push_back("Node cur = head");                      // 0
        codeHighlight->codeStrings.push_back("for (i = 0; i < index - 1; ++i)");      // 1
        codeHighlight->codeStrings.push_back("   cur = cur.next");                    // 2
        codeHighlight->codeStrings.push_back("Node nxt = cur.next");                  // 3
        codeHighlight->codeStrings.push_back("Node newNode = new Node(v)");           // 4
        codeHighlight->codeStrings.push_back("newNode.next = nxt");                   // 5
        codeHighlight->codeStrings.push_back("cur.next = newNode");                   // 6
        codeHighlight->codeStrings.push_back("// Relayout, not in actual operation"); // 7
        this->codeHighlight->updateTexts();
    };
    addHighlightCodes();

    AVLNode *curNode = root;
    while (curNode != nullptr)
    {
        if (curNode->key == nodeValue)
        {
            // this->animationAVL->instructions.push_back({[this, curNode]()
            //                                     { this->animationAVL->highlightCurrentNode(curNode, "reachColor", {5}); }});

            break;
        }

        int direction = (nodeValue > curNode->key);

        if (!curNode->next[direction])
        {
            this->animationAVL->instructions.push_back({[this, curNode]()
                                                        { this->animationAVL->highlightCurrentNode(curNode, "normal", {5}); }});
            waitAnimation();
            break;
        }
        std::string nextColor = (curNode->next[direction]->key == nodeValue) ? "reachColor" : "newColor";

        this->animationAVL->instructions.push_back({[this, curNode]()
                                                    { this->animationAVL->highlightCurrentNode(curNode, "normal", {5}); },
                                                    [this, curNode, direction, nextColor]()
                                                    { this->animationAVL->highlightCurrentNode(curNode->next[direction], nextColor, {5}); }});
        waitAnimation();
        curNode = curNode->next[direction];
    }

    endOperation();
    return;
}

void AVL::operation_update(int oldValue, int newValue)
{
    this->prepareNewInstruction();
    this->button_play();

    auto preCheck = [&]()
    {
        if (oldValue == -1 || newValue == -1)
        {
            this->inputWarning.setString("Wrong input format");
            return false;
        }
        if (oldValue < 1 || oldValue > 200 || newValue < 1 || newValue > 200)
        {
            this->inputWarning.setString("Value should be in range [1..200]");
            return false;
        }

        if (!this->exist[oldValue])
        {
            this->inputWarning.setString("Old value not found!");
            return false;
        }

        if (this->exist[newValue])
        {
            this->inputWarning.setString("New value existed!");
            return false;
        }
        return true;
    };
    if (!preCheck())
    {
        return;
    }
    this->exist[oldValue] = 0;
    this->exist[newValue] = 1;

    // auto addHighlightCodes = [&]
    // {
    //     codeHighlight->introText.setString("Update " + std::to_string(oldValue) + " to " + std::to_string(newValue));
    //     codeHighlight->codeStrings.push_back("Delete " + std::to_string(oldValue));         
    //     codeHighlight->codeStrings.push_back("Insert " + std::to_string(newValue));       
    //     this->codeHighlight->updateTexts();
    // };
    // addHighlightCodes();

    this->deleteAVLNode(root, root, oldValue);
    this->insertAVLNode(root, root, newValue);
    endOperation();
    return;
}

void AVL::prepareNewInstruction()
{
    // std::cout << "Prepare new\n";
    this->animation->finishStep();
    bool trash = 0;
    this->animationAVL->last(trash, &this->stepText);
    this->animationAVL->newInstruction(this->root->next[0], this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
    this->animationAVL->animationTime = 0.001; /* Do all instruction quickly first, then activate replay mode */
    this->codeHighlight->reset();
}

/* Update and Render */
void AVL::updateButtons()
{
    /* Update all the buttons */
    for (auto it : this->buttons)
    {
        if (it.second->isPressed())
        {
            if (this->choosingButton != it.first)
            {
                this->choosingChildButton = "";
            }
            this->choosingButton = it.first;

            if (it.second->instantTrigger)
            {
                this->newStepTriggered = true;
            }
        }
    }
}

void AVL::updateChildButtons()
{
    if (this->choosingButton != "")
    {
        for (auto it : this->childButtons[this->choosingButton])
        {
            if (it.second->isPressed())
            {
                if (this->choosingChildButton != it.first)
                {
                }
                this->choosingChildButton = it.first;

                if (it.second->instantTrigger)
                {
                    this->newStepTriggered = true;
                }
                // this->triggerChildFunction[it.first];
            }
        }
    }
}

void AVL::updateInputFields()
{
    if (this->choosingButton != "" && this->choosingChildButton != "")
    {
        if (inputFields.find(choosingButton) != inputFields.end() &&
            inputFields[choosingButton].find(choosingChildButton) != inputFields[choosingButton].end())
        {
            this->inputFields[this->choosingButton][this->choosingChildButton]->update(mousePosView);
        }
    }
}

void AVL::updateSFMLEvents(const float &dt, sf::Event &event)
{
    // for Buttons
    for (auto &it : this->buttons)
    {
        it.second->updateSFMLEvents(dt, event, this->mousePosView);
    }

    // for Child Buttons
    if (this->choosingButton != "")
    {
        for (auto &it : this->childButtons[this->choosingButton])
        {
            it.second->updateSFMLEvents(dt, event, this->mousePosView);
        }
    }

    // for InputField
    if (this->choosingButton != "" && this->choosingChildButton != "")
    {
        if (inputFields.find(choosingButton) != inputFields.end() &&
            inputFields[choosingButton].find(choosingChildButton) != inputFields[choosingButton].end())
        {
            auto readingInput = [&]()
            {
                bool hitEnter = 0;
                std::string str;
                this->inputFields[this->choosingButton][this->choosingChildButton]->updateSFMLEvents(dt, event, str, hitEnter);

                std::function<std::pair<int, int>()> checkString = [&]()
                {
                    int x = -1, y = -1;
                    if (str.size() == 0)
                        return std::make_pair(x, y);

                    int numComma = 0, indexComma = -1;
                    for (int i = 0; i < (int)str.size(); ++i)
                    {
                        if (str[i] == ',')
                        {
                            indexComma = i;
                            ++numComma;
                        }
                    }
                    if (numComma > 1 || indexComma == 0 || indexComma == (int)str.size() - 1)
                        return std::make_pair(x, y);

                    if (numComma != 0)
                    {
                        std::string sx = str.substr(0, indexComma);
                        std::string sy = str.substr(indexComma + 1);
                        std::stringstream ss;
                        ss << sx;
                        ss >> x;
                        ss.clear();

                        ss << sy;
                        ss >> y;
                        ss.clear();
                    }
                    else
                    {
                        std::stringstream ss;
                        ss << str;
                        ss >> x;
                        ss.clear();
                    }
                    return std::make_pair(x, y);
                };

                if (!hitEnter)
                    return;
                hitEnter = 0;

                // if (!this->doneAnimation)
                // {
                //     this->inputWarning.setString("Sorry, the animationAVL is running...");
                //     return;
                // }
                valueFirst = valueSecond = -1;

                std::pair<int, int> p = checkString();
                int x = p.first, y = p.second;
                if (x == -1)
                {
                    this->inputWarning.setString("Wrong input format");
                    hitEnter = 0;
                    return;
                }

                this->inputWarning.setString("");
                this->newStepTriggered = 1;
                this->valueFirst = x;
                this->valueSecond = y;
            };
            readingInput();
        }
    }
}

void AVL::update(const float &dt)
{
    this->window->setTitle("AVL");
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateTexts();

    this->updateCursor();
    this->updateButtons();
    this->updateChildButtons();
    this->updateInputFields();

    if (this->choosingButton != "")
        this->triggerFunction[this->choosingButton]();
}

void AVL::enable_replayButton()
{
    /* Show Replay button */
    this->buttons["Play"]->disabled = 1;
    this->buttons["Pause"]->disabled = 1;
    this->buttons["Replay"]->disabled = 0;
}

void AVL::renderButtons(sf::RenderTarget *target)
{
    /* Render parent buttons */
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }

    /* Render child buttons */

    if (this->choosingButton != "")
    {
        for (auto &it : this->childButtons[this->choosingButton])
        {
            it.second->render(target);
        }
    }

    /* Render Input Fields */
    if (this->choosingButton != "" && this->choosingChildButton != "")
    {
        if (inputFields.find(choosingButton) != inputFields.end() &&
            inputFields[choosingButton].find(choosingChildButton) != inputFields[choosingButton].end())
        {
            this->inputFields[this->choosingButton][this->choosingChildButton]->render(target);
        }
    }
}

void AVL::renderNode(sf::RenderTarget *target)
{
    for (AVLNode *node : this->Nodes)
    {
        node->render(target);
    }
}

void AVL::renderAnimation()
{
    // std::cout<<"runState="<<runState<<'\n';
    if (this->doneAnimation)
    {
        runState = "";
        return;
    }

    // auto enable_replayButton = [&]()
    // {
    //     /* Show Replay button */
    //     this->buttons["Play"]->disabled = 1;
    //     this->buttons["Pause"]->disabled = 1;
    //     this->buttons["Replay"]->disabled = 0;
    // };
    if (this->runState == "play")
    {
        this->animationAVL->play(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "pause")
    {
        this->animationAVL->pause(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "prev")
    {
        this->animationAVL->prev(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "next")
    {
        this->animationAVL->next(this->doneAnimation, &this->stepText);
        if (this->doneAnimation && this->animationAVL->curIndex == (int)this->animationAVL->instructions.size())
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "first")
    {
        this->animationAVL->first(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "last")
    {
        this->animationAVL->last(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }
}

void AVL::renderHighlightCode(sf::RenderTarget *target)
{
    codeHighlight->render(target);
}

void AVL::render(sf::RenderTarget *target)
{
    if (!target)
    {
        target = this->window;
    }
    target->draw(this->background);

    this->renderAnimation();
    this->renderHighlightCode(target);

    this->renderButtons(target);
    this->renderTexts(target);
    this->renderNode(target);
}

void AVL::reset()
{   
    this->exist.resize(1005);
    exist.assign((int)exist.size(), 0);
    
    this->DeleteNodePointers();
    this->root = new AVLNode(0, 0, scale_x, scale_y, 100000, &font, &Colors);
    this->numberNode = 0;

    delete (this->animation);

    this->codeHighlight->reset();
    this->animation = new AnimationAVL(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationAVL = dynamic_cast<AnimationAVL *>(this->animation);
    assert(animationAVL != nullptr);

    this->newStepTriggered = 0;
    this->doneAnimation = 1;
    this->choosingButton = "";
    this->choosingChildButton = "";
    inputWarning.setString("");
    inputGuide.setString("");
    exist.assign((int)exist.size(), 0);
    runState = "";
}

void AVL::waitAnimation()
{
    /* This function is called immediately after pushing new Animation */
    this->doneAnimation = 0;
    while (!this->doneAnimation)
    {
        this->animationAVL->play(this->doneAnimation, &this->stepText);
    }
    return;
}

void AVL::endOperation()
{
    this->animationAVL->animationTime = float(speedGap * maxSpeed) / currentSpeed;

    // At the beginning of each operator, we go through all animation immediately, then trigger replay mode
    button_replay();
    return;
}
