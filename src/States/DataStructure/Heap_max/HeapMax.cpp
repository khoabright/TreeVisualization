#include "HeapMax.h"

HeapMax::HeapMax(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : DataStructure(window, supportedKeys, states)
{
    auto HeapMaxScale = [&]()
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
    HeapMaxScale();

    this->ReInitButtons();
    this->initHighlightCode();
    this->initTriggerFunction();
    this->initChildButtons();
    this->initInputFields();
    this->initAnimation();

    reset();
}

HeapMax::~HeapMax()
{
    this->DeleteNodePointers();
    delete (this->animationHeapMax);
}

void HeapMax::DeleteNodePointers()
{
    for (auto &v : this->Nodes)
    {
        delete (v);
    }
    this->Nodes.clear();
}

/* Init */
void HeapMax::initTriggerFunction()
{
    auto InstructionButtons = [&]()
    {
        this->triggerFunction["Theme"] = std::bind(&HeapMax::button_theme, this);
        this->triggerFunction["Initialize"] = std::bind(&HeapMax::button_initialize, this);
        this->triggerFunction["Add"] = std::bind(&HeapMax::button_add, this);
        this->triggerFunction["Delete"] = std::bind(&HeapMax::button_delete, this);
        this->triggerFunction["Top"] = std::bind(&HeapMax::button_top, this);
        this->triggerFunction["Size"] = std::bind(&HeapMax::button_size, this);
        this->triggerFunction["Quit"] = std::bind(&HeapMax::button_quit, this);
        this->triggerFunction["SpeedMinus"] = std::bind(&HeapMax::button_SpeedMinus, this);
        this->triggerFunction["SpeedPlus"] = std::bind(&HeapMax::button_SpeedPlus, this);
        this->triggerFunction["CodeSwitch"] = std::bind(&HeapMax::button_CodeSwitch, this);
    };

    auto RunButtons = [&]()
    {
        this->triggerFunction["First"] = std::bind(&HeapMax::button_first, this);
        this->triggerFunction["Prev"] = std::bind(&HeapMax::button_prev, this);
        this->triggerFunction["Pause"] = std::bind(&HeapMax::button_pause, this);
        this->triggerFunction["Play"] = std::bind(&HeapMax::button_play, this);
        this->triggerFunction["Replay"] = std::bind(&HeapMax::button_replay, this);
        this->triggerFunction["Next"] = std::bind(&HeapMax::button_next, this);
        this->triggerFunction["Last"] = std::bind(&HeapMax::button_last, this);
    };

    InstructionButtons();
    RunButtons();
}

void HeapMax::initChildButtons()
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

    init_theme();
    init_initialize();
}

void HeapMax::initInputFields()
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

    init_initialize();
    init_add();
}

void HeapMax::initAnimation()
{
    this->animation = new AnimationHeapMax(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationHeapMax = dynamic_cast<AnimationHeapMax *>(this->animation);
    assert(animationHeapMax != nullptr);
    this->animationHeapMax->animationTime = float(speedGap * maxSpeed) / currentSpeed;
}

void HeapMax::initHighlightCode()
{
    codeHighlight = new CodeHighlight(scale_x, scale_y, &Colors);
}

void HeapMax::button_theme()
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
void HeapMax::button_initialize()
{
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
                this->inputWarning.setString("Sorry, maximum size is " + std::to_string(maxNode));
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
            codeHighlight->introText.setString("Random HeapMaxTree with " + std::to_string(valueFirst) + " node" + (valueFirst > 1 ? "s" : ""));
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
            this->animationHeapMax->newInstruction(this->root, arrNode, numberNode, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
            addHighlightCodes();
            insertHeapMaxNode(newValue);
        }
        // this->animationHeapMax->updateNodePosition(this->root, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
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
        inp.open("InputFiles/inputHeapMax.txt");
        int newValue = 0;
        while (inp >> newValue)
        {
            this->animationHeapMax->newInstruction(this->root, arrNode, numberNode, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
            addHighlightCodes();
            insertHeapMaxNode(newValue);
        }
        inp.close();

        // this->animationHeapMax->updateNodePosition(this->head, this->tail, this->start_x, this->start_y, this->nodeDistanceX);
        return;
    }
}

void HeapMax::button_add()
{
    this->choosingChildButton = "1Head";

    if (this->newStepTriggered)
    {
        this->operation_add(this->valueFirst);
        return;
    }
    else
    {
        this->inputGuide.setString("Input a value");
    }
}

void HeapMax::button_delete()
{
    this->operation_delete();
    return;
}

void HeapMax::button_top()
{
    operation_top();
    return;
}

void HeapMax::button_size()
{
    operation_size();
    return;
}

void HeapMax::button_quit()
{
    this->endState();
}

// HeapMax Operations

void HeapMax::buildHeapMaxTree(HeapMaxNode *cur)
{      
    Nodes.push_back(cur);
    int idx = cur->idxArray;
    arrNode[idx] = cur;
    if (2 * idx <= maxNode) {
        cur->next[0] = new HeapMaxNode(0, 0, scale_x, scale_y, 2 * idx, 2 * idx, &font, &Colors);
        buildHeapMaxTree(cur->next[0]);
    }
    if (2 * idx + 1 <= maxNode) {
        cur->next[1] = new HeapMaxNode(0, 0, scale_x, scale_y, 2 * idx + 1, 2 * idx + 1, &font, &Colors);
        buildHeapMaxTree(cur->next[1]);
    }
}

HeapMaxNode *HeapMax::newHeapMaxNode(int key, HeapMaxNode *parentNode)
{
    int posX = start_x, posY = start_y;
    if (numberNode > 0)
    {
        posX -= 3 * nodeDistanceX;
    }

    HeapMaxNode *newNode = new HeapMaxNode(posX, posY, scale_x, scale_y, key, 1, &font, &Colors);
    newNode->key = key;
    newNode->heightHeapMax = 1;
    this->Nodes.push_back(newNode);
    this->animationHeapMax->instructions.push_back({[this, newNode]()
                                                { this->animationHeapMax->showNode(newNode, "", this->numberNode, {1}); },
                                                [this, parentNode]()
                                                { this->animationHeapMax->highlightCurrentNode(parentNode, "normal", {5}); }});
    waitAnimation();

    return (newNode);
}

void HeapMax::insertHeapMaxNode(int key)
{   
    ++numberNode;
    arrNode[numberNode]->newKey(key);
    arrNode[numberNode]->nextKey();

    std::vector<std::function<void()>> temp_vec = {[this]()
                                                   { this->animationHeapMax->showNode(arrNode[numberNode], "", numberNode, {1}); }};
    
    if (numberNode > 1)
        temp_vec.push_back([this]()
                           { this->animationHeapMax->connectNodes(arrNode[numberNode / 2], arrNode[numberNode], numberNode % 2, {1}); });
    this->animationHeapMax->instructions.push_back(temp_vec);
    waitAnimation();

    int curIdx = numberNode;
    while (curIdx > 1)
    {   
        bool swapped = 0;
        this->animationHeapMax->instructions.push_back({[this, curIdx]()
                                                     { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx], "reachColor", {5}); },
                                                     [this, curIdx]()
                                                     { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx / 2], "reachColor", {5}); }});
        waitAnimation();

        if (arrNode[curIdx]->key > arrNode[curIdx / 2]->key) {
            swapped = 1;
            int val1 = arrNode[curIdx]->key;
            int val2 = arrNode[curIdx / 2]->key;

            this->animationHeapMax->instructions.push_back({[this, curIdx, val2]()
                                                         { this->animationHeapMax->changeNodeValue(arrNode[curIdx], val2, {5}); },
                                                         [this, curIdx, val1]()
                                                         { this->animationHeapMax->changeNodeValue(arrNode[curIdx / 2], val1, {5}); }});
            waitAnimation();
        }

        this->animationHeapMax->instructions.push_back({[this, curIdx]()
                                                        { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx], "normal", {5}); },
                                                        [this, curIdx]()
                                                        { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx / 2], "normal", {5}); }});
        waitAnimation();
        if (!swapped) break;

        curIdx /= 2;
    }

    return;
}

HeapMaxNode *HeapMax::deleteHeapMaxNode()
{
    int val1 = arrNode[1]->key;
    int val2 = arrNode[numberNode]->key;
    this->animationHeapMax->instructions.push_back({[this, val2]()
                                                 { this->animationHeapMax->changeNodeValue(arrNode[1], val2, {5}); }});
    waitAnimation();

    this->animationHeapMax->instructions.push_back({[this, sz = this->numberNode]()
                                                 { this->animationHeapMax->hideNode(arrNode[sz], arrNode[sz / 2], sz % 2, numberNode, {5}); }});
    waitAnimation();

    --numberNode;
    int curIdx = 1;
    while (curIdx * 2 <= numberNode) {
        if (curIdx * 2 + 1 <= numberNode) // compare only when exist 2 children
        {
            this->animationHeapMax->instructions.push_back({[this, curIdx]()
                                                         { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx * 2], "reachColor", {5}); },
                                                         [this, curIdx]()
                                                         { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx * 2 + 1], "reachColor", {5}); }});
            waitAnimation();
        }

        int child = (curIdx * 2 + 1 <= numberNode && arrNode[curIdx * 2 + 1]->key > arrNode[curIdx * 2]->key); // which child is smaller

        this->animationHeapMax->instructions.push_back({[this, curIdx]()
                                                     { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx], "reachColor", {5}); },
                                                     [this, curIdx, child]()
                                                     { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx * 2 + 1 - child], "normal", {5}); },
                                                     [this, curIdx, child]()
                                                     { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx * 2 + child], "reachColor", {5}); }});

        waitAnimation();

        std::vector<std::function<void()>> temp_vec = {[this, curIdx]()
                                                     { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx], "normal", {5}); },
                                                     [this, curIdx, child]()
                                                     { this->animationHeapMax->highlightCurrentNode(arrNode[curIdx * 2 + child], "normal", {5}); }};

        bool swapped = 0;
        if (arrNode[curIdx]->key < arrNode[curIdx * 2 + child]->key) {
            swapped = 1;
            int val1 = arrNode[curIdx]->key;
            int val2 = arrNode[curIdx * 2 + child]->key;

            temp_vec.push_back([this, curIdx, val2]()
                               { this->animationHeapMax->changeNodeValue(arrNode[curIdx], val2, {5}); });
            temp_vec.push_back([this, curIdx, child, val1]()
                               { this->animationHeapMax->changeNodeValue(arrNode[curIdx * 2 + child], val1, {5}); });
        }
        this->animationHeapMax->instructions.push_back(temp_vec);
        waitAnimation();

        if (!swapped) break;
        curIdx = curIdx * 2 + child;
    }
}

void HeapMax::operation_add(int nodeValue)
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

    insertHeapMaxNode(nodeValue);

    endOperation();
    return;
}

void HeapMax::operation_delete()
{
    this->prepareNewInstruction();
    this->button_play();

    auto preCheck = [&]()
    {
        if (this->numberNode < 1)
        {
            this->inputWarning.setString("Empty Tree");
            return false;
        }
        return true;
    };
    if (!preCheck())
    {
        return;
    }


    auto addHighlightCodes = [&]
    {
        codeHighlight->introText.setString("Delete root node");
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

    // this->animationHeapMax->instructions.push_back({[this]()
    //                                             { this->animationHeapMax->Relayout((numberNode == 0), root->next[0], start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});

    deleteHeapMaxNode();

    // this->animationHeapMax->instructions.push_back({[this]()
    //                                             { this->animationHeapMax->Relayout((numberNode == 0), root->next[0], start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});

    endOperation();
    return;
}

void HeapMax::operation_top()
{
    this->prepareNewInstruction();
    this->button_play();

    if (numberNode == 0) {
        this->inputWarning.setString("Empty tree");
        return;
    }

    auto addHighlightCodes = [&]
    {
        codeHighlight->introText.setString("Get top");
        this->codeHighlight->updateTexts();
    };
    addHighlightCodes();

    this->animationHeapMax->instructions.push_back({[this]()
                                                     { this->animationHeapMax->highlightCurrentNode(root, "reachColor", {}); }});

    return;
}

void HeapMax::operation_size()
{
    this->prepareNewInstruction();
    this->button_play();
    this->inputWarning.setString("Size = " + std::to_string(numberNode));
    return;
}

void HeapMax::prepareNewInstruction()
{
    // std::cout << "Prepare new\n";
    this->animation->finishStep();
    bool trash = 0;
    this->animationHeapMax->last(trash, &this->stepText);
    this->animationHeapMax->newInstruction(this->root, arrNode, numberNode, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
    this->animationHeapMax->animationTime = 0.001; /* Do all instruction quickly first, then activate replay mode */
    this->codeHighlight->reset();
}

/* Update and Render */
void HeapMax::updateButtons()
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

void HeapMax::updateChildButtons()
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

void HeapMax::updateInputFields()
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

void HeapMax::updateSFMLEvents(const float &dt, sf::Event &event)
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
                //     this->inputWarning.setString("Sorry, the animationHeapMax is running...");
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

void HeapMax::update(const float &dt)
{
    this->window->setTitle("HeapMax");
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

void HeapMax::enable_replayButton()
{
    /* Show Replay button */
    this->buttons["Play"]->disabled = 1;
    this->buttons["Pause"]->disabled = 1;
    this->buttons["Replay"]->disabled = 0;
}

void HeapMax::renderButtons(sf::RenderTarget *target)
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

void HeapMax::renderNode(sf::RenderTarget *target)
{
    for (HeapMaxNode *node : this->Nodes)
    {
        node->render(target);
    }
}

void HeapMax::renderAnimation()
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
        this->animationHeapMax->play(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "pause")
    {
        this->animationHeapMax->pause(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "prev")
    {
        this->animationHeapMax->prev(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "next")
    {
        this->animationHeapMax->next(this->doneAnimation, &this->stepText);
        if (this->doneAnimation && this->animationHeapMax->curIndex == (int)this->animationHeapMax->instructions.size())
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "first")
    {
        this->animationHeapMax->first(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "last")
    {
        this->animationHeapMax->last(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }
}

void HeapMax::renderHighlightCode(sf::RenderTarget *target)
{
    codeHighlight->render(target);
}

void HeapMax::render(sf::RenderTarget *target)
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

void HeapMax::reset()
{   
    this->exist.resize(1005);
    exist.assign((int)exist.size(), 0);
    arrNode.resize(maxNode + 2);
    
    this->DeleteNodePointers();

    /* Init Tree */
    this->root = new HeapMaxNode(0, 0, scale_x, scale_y, 1, 1, &font, &Colors);
    HeapMaxNode* rubbish = new HeapMaxNode(0, 0, scale_x, scale_y, -1, 0, &font, &Colors);
    rubbish->showTextArray = 1;
    arrNode[0] = rubbish;
    Nodes.push_back(rubbish); // index 0 is inf

    buildHeapMaxTree(root);
    RecalTreeAmountLeftRight(root);
    RecalTreePosition(root, start_x, start_y, nodeDistanceX, nodeDistanceY);

    this->numberNode = 0;

    delete (this->animation);

    this->codeHighlight->reset();
    this->animation = new AnimationHeapMax(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationHeapMax = dynamic_cast<AnimationHeapMax *>(this->animation);
    assert(animationHeapMax != nullptr);

    this->newStepTriggered = 0;
    this->doneAnimation = 1;
    this->choosingButton = "";
    this->choosingChildButton = "";
    inputWarning.setString("");
    inputGuide.setString("");
    exist.assign((int)exist.size(), 0);
    runState = "";
}

void HeapMax::waitAnimation()
{
    /* This function is called immediately after pushing new Animation */
    this->doneAnimation = 0;
    while (!this->doneAnimation)
    {
        this->animationHeapMax->play(this->doneAnimation, &this->stepText);
    }
    return;
}

void HeapMax::endOperation()
{
    this->animationHeapMax->animationTime = float(speedGap * maxSpeed) / currentSpeed;

    // At the beginning of each operator, we go through all animation immediately, then trigger replay mode
    button_replay();
    return;
}

void HeapMax::ReInitButtons()
{
    delete (this->buttons["Update"]);
    delete (this->buttons["Search"]);
    this->buttons.erase(buttons.find("Update"));
    this->buttons.erase(buttons.find("Search"));

    this->buttons["Top"] = new Button(
        insButtonX, insButtonY + 4 * insButtonDistanceY, scale_x, scale_y,
        &this->font, "Top", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(240, 180, 10, 255),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(150, 150, 150, 255),
        1, insButtonSizeX, insButtonSizeY);


    this->buttons["Size"] = new Button(
        insButtonX, insButtonY + 5 * insButtonDistanceY, scale_x, scale_y,
        &this->font, "Size", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(240, 180, 10, 255),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(150, 150, 150, 255),
        1, insButtonSizeX, insButtonSizeY);

    return;
}