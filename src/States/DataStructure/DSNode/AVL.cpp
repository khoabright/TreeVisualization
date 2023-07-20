#include "AVL.h"

AVL::AVL(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : DataStructure(window, supportedKeys, states)
{
    this->root = nullptr;
    this->exist.resize(105);

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

    auto init_add = [&]()
    {
        ++idy;
        this->childButtons["Add"].insert({"1Head", nullptr});
        this->childButtons["Add"].insert({"2Tail", nullptr});
        this->childButtons["Add"].insert({"3Middle", nullptr});

        int idx = 0;
        for (auto &it : this->childButtons["Add"])
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
    };

    auto init_delete = [&]()
    {
        ++idy;
        this->childButtons["Delete"].insert({"1Head", nullptr});
        this->childButtons["Delete"].insert({"2Tail", nullptr});
        this->childButtons["Delete"].insert({"3Middle", nullptr});

        int idx = 0;
        for (auto &it : this->childButtons["Delete"])
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
        this->childButtons["Delete"]["1Head"]->instantTrigger = true;
        this->childButtons["Delete"]["2Tail"]->instantTrigger = true;
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
        this->inputFields["Add"].insert({"1Head", nullptr});
        this->inputFields["Add"].insert({"2Tail", nullptr});
        this->inputFields["Add"].insert({"3Middle", nullptr});

        int idx = 0;
        for (auto &it : this->inputFields["Add"])
        {
            it.second = new InputField(this->inputFieldOriginX + (idx++) * (this->inputFieldWidth + this->inputFieldDistanceX),
                                       this->inputFieldOriginY + idy * (this->inputFieldHeight + this->inputFieldDistanceY),
                                       this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                       &this->font, this->inputFieldCharacterSize,
                                       sf::Color::White, sf::Color::White, sf::Color::Black);
        }
    };

    auto init_delete = [&]()
    {
        ++idy;
        this->inputFields["Delete"].insert({"1Head", nullptr});
        this->inputFields["Delete"].insert({"2Tail", nullptr});
        this->inputFields["Delete"].insert({"3Middle", nullptr});

        int idx = 0;
        for (auto &it : this->inputFields["Delete"])
        {
            it.second = new InputField(this->inputFieldOriginX + (idx++) * (this->inputFieldWidth + this->inputFieldDistanceX),
                                       this->inputFieldOriginY + idy * (this->inputFieldHeight + this->inputFieldDistanceY),
                                       this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                       &this->font, this->inputFieldCharacterSize,
                                       sf::Color::White, sf::Color::White, sf::Color::Black);
        }
    };

    auto init_update = [&]()
    {
        this->inputFields["Update"]["1Update"] = new InputField(this->inputFieldOriginX, 663.f * this->scale_y,
                                                                this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                                                &this->font, this->inputFieldCharacterSize,
                                                                sf::Color::White, sf::Color::White, sf::Color::Black);
    };

    auto init_search = [&]()
    {
        this->inputFields["Search"]["1Search"] = new InputField(this->inputFieldOriginX, 693.f * this->scale_y,
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
    this->animationAVL->animationTime = speedGap * (float)maxSpeed;
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
        /* if (this->newStepTriggered)
        {
            this->newStepTriggered = 0;
            this->inputGuide.setString("");
            if (this->valueFirst > maxNode)
            {
                this->inputWarning.setString("Sorry, the std::maximum size is " + std::to_string(maxNode));
                return;
            }
        }
        else
        {
            this->inputGuide.setString("Input a size");
            return;
        }

        this->reset();
        std::vector<int> values(99);
        for (int i = 0; i < 99; ++i)
            values[i] = i + 1;
        std::shuffle(values.begin(), values.end(), this->randomize);
        for (int i = 0; i < this->valueFirst; ++i)
        {
            int newValue = values[i];
            assert(this->exist[newValue] == 0);
            this->exist[newValue] = 1;
            createNewNode(newValue);
        }
        this->animationAVL->updateNodePosition(this->head, this->tail, this->start_x, this->start_y, this->nodeDistanceX); */
        return;
    }

    if (this->choosingChildButton == "3Load File")
    {
        /* if (!this->newStepTriggered)
            return;
        this->newStepTriggered = 0;

        this->reset();
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
            createNewNode(newValue);
        }
        inp.close();

        this->animationAVL->updateNodePosition(this->head, this->tail, this->start_x, this->start_y, this->nodeDistanceX); */
        return;
    }
}

void AVL::button_add()
{
    if (this->choosingChildButton == "1Head")
    {
        if (this->newStepTriggered)
        {
            this->newStepTriggered = 0;
            this->inputGuide.setString("");
            this->operation_add(this->valueFirst);
            return;
        }
        else
        {
            this->inputGuide.setString("Input a value");
        }
    }
}

void AVL::button_delete()
{
}


void AVL::button_search()
{
    // this->choosingChildButton = "1Search";

    // if (this->newStepTriggered)
    // {
    //     this->newStepTriggered = 0;
    //     this->inputGuide.setString("");
    //     this->searchNode(this->valueFirst);
    //     return;
    // }
    // else
    // {
    //     this->inputGuide.setString("Input a value to search");
    // }
}

void AVL::button_quit()
{
    this->endState();
}

// AVL Operations
int AVL::heightAVL(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return N->heightAVL;
}

AVLNode *AVL::newAVLNode(int key)
{
    AVLNode *newNode = new AVLNode(start_x, start_y, scale_x, scale_y, key, &font, &Colors);
    newNode->key = key;
    newNode->heightAVL = 1;
    this->Nodes.push_back(newNode);
    return (newNode);
}

AVLNode *AVL::rightRotate(AVLNode *y)
{
    AVLNode *x = y->next[0];
    AVLNode *T2 = x->next[1];
    x->next[1] = y;
    y->next[0] = T2;
    y->heightAVL = std::max(heightAVL(y->next[0]),
                         heightAVL(y->next[1])) +
                1;
    x->heightAVL = std::max(heightAVL(x->next[0]),
                         heightAVL(x->next[1])) +
                1;
    return x;
}

AVLNode *AVL::leftRotate(AVLNode *x)
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
    return y;
}

int AVL::getBalanceFactor(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return heightAVL(N->next[0]) -
           heightAVL(N->next[1]);
}

AVLNode *AVL::insertAVLNode(AVLNode *AVLNode, int key)
{
    // Find the correct postion and insert the AVLNode
    if (AVLNode == NULL) {
        return (newAVLNode(key));
    }

    if (key < AVLNode->key)
        AVLNode->next[0] = insertAVLNode(AVLNode->next[0], key);
    else if (key > AVLNode->key)
        AVLNode->next[1] = insertAVLNode(AVLNode->next[1], key);
    else
        return AVLNode;

    // Update the balance factor of each AVLNode and
    // balance the tree
    AVLNode->heightAVL = 1 + std::max(heightAVL(AVLNode->next[0]),
                                   heightAVL(AVLNode->next[1]));
    int balanceFactor = getBalanceFactor(AVLNode);
    if (balanceFactor > 1)
    {
        if (key < AVLNode->next[0]->key)
        {
            return rightRotate(AVLNode);
        }
        else if (key > AVLNode->next[0]->key)
        {
            AVLNode->next[0] = leftRotate(AVLNode->next[0]);
            return rightRotate(AVLNode);
        }
    }
    if (balanceFactor < -1)
    {
        if (key > AVLNode->next[1]->key)
        {
            return leftRotate(AVLNode);
        }
        else if (key < AVLNode->next[1]->key)
        {
            AVLNode->next[1] = rightRotate(AVLNode->next[1]);
            return leftRotate(AVLNode);
        }
    }
    return AVLNode;
}

AVLNode *AVL::AVLNodeWithMimumValue(AVLNode *node)
{
    AVLNode *current = node;
    while (current->next[0] != NULL)
        current = current->next[0];
    return current;
}

AVLNode *AVL::deleteAVLNode(AVLNode *root, int key)
{
    // Find the AVLNode and delete it
    if (root == NULL)
        return root;
    if (key < root->key)
        root->next[0] = deleteAVLNode(root->next[0], key);
    else if (key > root->key)
        root->next[1] = deleteAVLNode(root->next[1], key);
    else
    {
        if ((root->next[0] == NULL) ||
            (root->next[1] == NULL))
        {
            AVLNode *temp = root->next[0] ? root->next[0] : root->next[1];
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            AVLNode *temp = AVLNodeWithMimumValue(root->next[1]);
            root->key = temp->key;
            root->next[1] = deleteAVLNode(root->next[1],
                                        temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each AVLNode and
    // balance the tree
    root->heightAVL = 1 + std::max(heightAVL(root->next[0]),
                                heightAVL(root->next[1]));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1)
    {
        if (getBalanceFactor(root->next[0]) >= 0)
        {
            return rightRotate(root);
        }
        else
        {
            root->next[0] = leftRotate(root->next[0]);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1)
    {
        if (getBalanceFactor(root->next[1]) <= 0)
        {
            return leftRotate(root);
        }
        else
        {
            root->next[1] = rightRotate(root->next[1]);
            return leftRotate(root);
        }
    }
    return root;
}

// Add

void AVL::operation_add(int nodeValue)
{
    /* Complete all animations */
    this->prepareNewInstruction();
    this->button_play();

    auto preCheck = [&]()
    {
        if (nodeValue == -1)
        {
            this->inputWarning.setString("Wrong input format");
            return;
        }
        if (nodeValue < 1 || nodeValue > 99)
        {
            this->inputWarning.setString("Value should be in range [1..99]");
            return;
        }

        if (numberNode + 1 > maxNode)
        {
            this->inputWarning.setString("Sorry, the std::maximum size is " + std::to_string(maxNode));
            return;
        }

        if (this->exist[nodeValue])
        {
            this->inputWarning.setString("No duplicate vertex allowed!");
            return;
        }
    };
    preCheck();
    this->exist[nodeValue] = 1;

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

    if (root == nullptr) {
        root = newAVLNode(nodeValue);
        this->animationAVL->instructions.push_back({[this]()
                                                 { this->animationAVL->showNode(root, "root", numberNode, {0}); }});
        return;
    }

    insertAVLNode(this->root, nodeValue);
}

// Delete

void AVL::deleteMiddle(int index)
{

}

void AVL::prepareNewInstruction()
{
    this->animation->finishStep();
    bool trash = 0;
    this->animationAVL->last(trash, &this->stepText);
    this->animationAVL->newInstruction(this->root, this->start_x, this->start_y, this->nodeDistanceX);
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
    this->window->setTitle("Singly Linked List");
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
    if (this->doneAnimation)
    {
        this->runState = "";
        return;
    }

    auto enable_replayButton = [&]()
    {
        /* Show Replay button */
        this->buttons["Play"]->disabled = 1;
        this->buttons["Pause"]->disabled = 1;
        this->buttons["Replay"]->disabled = 0;
    };

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
    exist.assign((int)exist.size(), 0);
    this->DeleteNodePointers();
    this->root = nullptr;
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
