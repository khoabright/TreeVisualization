#include "Tree234.h"

Tree234::Tree234(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : DataStructure(window, supportedKeys, states)
{
    auto Tree234Scale = [&]()
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
    Tree234Scale();

    this->ReInitButtons();
    this->initHighlightCode();
    this->initTriggerFunction();
    this->initChildButtons();
    this->initInputFields();
    this->initAnimation();

    reset();
}

Tree234::~Tree234()
{
    this->DeleteNodePointers();
    delete (this->animationTree234);
}

void Tree234::DeleteNodePointers()
{
    for (auto &v : this->Nodes)
    {
        delete (v);
    }
    this->Nodes.clear();
}

/* Init */
void Tree234::initTriggerFunction()
{
    auto InstructionButtons = [&]()
    {
        this->triggerFunction["Theme"] = std::bind(&Tree234::button_theme, this);
        this->triggerFunction["Initialize"] = std::bind(&Tree234::button_initialize, this);
        this->triggerFunction["Add"] = std::bind(&Tree234::button_add, this);
        this->triggerFunction["Delete"] = std::bind(&Tree234::button_delete, this);
        this->triggerFunction["Search"] = std::bind(&Tree234::button_search, this);
        this->triggerFunction["Quit"] = std::bind(&Tree234::button_quit, this);
        this->triggerFunction["SpeedMinus"] = std::bind(&Tree234::button_SpeedMinus, this);
        this->triggerFunction["SpeedPlus"] = std::bind(&Tree234::button_SpeedPlus, this);
        this->triggerFunction["CodeSwitch"] = std::bind(&Tree234::button_CodeSwitch, this);
    };

    auto RunButtons = [&]()
    {
        this->triggerFunction["First"] = std::bind(&Tree234::button_first, this);
        this->triggerFunction["Prev"] = std::bind(&Tree234::button_prev, this);
        this->triggerFunction["Pause"] = std::bind(&Tree234::button_pause, this);
        this->triggerFunction["Play"] = std::bind(&Tree234::button_play, this);
        this->triggerFunction["Replay"] = std::bind(&Tree234::button_replay, this);
        this->triggerFunction["Next"] = std::bind(&Tree234::button_next, this);
        this->triggerFunction["Last"] = std::bind(&Tree234::button_last, this);
    };

    InstructionButtons();
    RunButtons();
}

void Tree234::initChildButtons()
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

void Tree234::initInputFields()
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

void Tree234::initAnimation()
{
    this->animation = new AnimationTree234(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationTree234 = dynamic_cast<AnimationTree234 *>(this->animation);
    assert(animationTree234 != nullptr);
    this->animationTree234->animationTime = float(speedGap * maxSpeed) / currentSpeed;
}

void Tree234::initHighlightCode()
{
    codeHighlight = new CodeHighlight(scale_x, scale_y, &Colors);
}

void Tree234::button_theme()
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
void Tree234::button_initialize()
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
            codeHighlight->introText.setString("Random Tree234Tree with " + std::to_string(valueFirst) + " node" + (valueFirst > 1 ? "s" : ""));
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
            float tmp_start_x = start_x;
            addHighlightCodes();
            insertTree234Node(newValue, root, root);
            this->animationTree234->newInstruction(this->root, numberNode, tmp_start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
        }
        // this->animationTree234->updateNodePosition(this->root, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
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
        inp.open("InputFiles/inputTree234.txt");
        int newValue = 0;
        while (inp >> newValue)
        {   
            float tmp_start_x = start_x;
            addHighlightCodes();
            insertTree234Node(newValue, root, root);
            this->animationTree234->newInstruction(this->root, numberNode, tmp_start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
        }
        inp.close();

        // this->animationTree234->updateNodePosition(this->head, this->tail, this->start_x, this->start_y, this->nodeDistanceX);
        return;
    }
}

void Tree234::button_add()
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

void Tree234::button_delete()
{
    this->operation_delete();
    return;
}

void Tree234::button_search()
{
    operation_search();
    return;
}

void Tree234::button_quit()
{
    this->endState();
}

// Tree234 Operations

void Tree234::buildTree234Tree(Tree234Node *cur)
{      
    // Nodes.push_back(cur);
    // int idx = cur->idxArray;
    // arrNode[idx] = cur;
    // if (2 * idx <= maxNode) {
    //     cur->next[0] = new Tree234Node(0, 0, scale_x, scale_y, 2 * idx, 2 * idx, &font, &Colors);
    //     buildTree234Tree(cur->next[0]);
    // }
    // if (2 * idx + 1 <= maxNode) {
    //     cur->next[1] = new Tree234Node(0, 0, scale_x, scale_y, 2 * idx + 1, 2 * idx + 1, &font, &Colors);
    //     buildTree234Tree(cur->next[1]);
    // }
}

Tree234Node *Tree234::newTree234Node(int key, Tree234Node *parentNode)
{
}

void Tree234::insertTree234Node(int key, Tree234Node *curNode, Tree234Node *parentNode, bool isRecursing)
{
    waitAnimation();

    if (root == nullptr) {
        root = new Tree234Node(start_x, start_y, scale_x, scale_y, {key}, &font, &Colors);
        Nodes.push_back(root);
        this->animationTree234->instructions.push_back({[this, node = root]()
                                                        {
                                                            this->animationTree234->showNode(root, "", numberNode, {1});
                                                        }});
        waitAnimation();
        return;
    }

    this->animationTree234->instructions.push_back({[this, cur = curNode]()
                                                    {
                                                        this->animationTree234->highlightCurrentNode(cur, "normalFillColor", "reachColor", {1});
                                                    }});

    std::vector<int> v = curNode->key;

    if (v.size() < 3 || isRecursing) {
        if (curNode->next[0] == nullptr) { // leaf => insert
            v.push_back(key);
            std::sort(v.begin(), v.end());
            this->animationTree234->instructions.push_back({[this, cur = curNode, newKey = v]()
                                                            {
                                                                this->animationTree234->changeNodeValue(cur, newKey, {2});
                                                            },
                                                            [this, cur = curNode]()
                                                            {
                                                                this->animationTree234->highlightCurrentNode(cur, "normalFillColor", "normalOutlineColor", {1});
                                                            },
                                                            [this]()
                                                            { this->animationTree234->Relayout(0, root, start_x, start_y, nodeDistanceX, nodeDistanceY, {2}); }});

            waitAnimation();

            this->animationTree234->instructions.push_back({[this, cur = curNode]()
                                                            {
                                                                this->animationTree234->highlightCurrentNode(cur, "normal", "normal", {1});
                                                            }});
            waitAnimation();
            return;
        }

        // go to corresponding child
        int sz = curNode->key.size();
        for (int i = 0; i < sz; ++i) {
            if (key < curNode->key[i]) {
                this->animationTree234->instructions.push_back({[this, cur = curNode]()
                                                                {
                                                                    this->animationTree234->highlightCurrentNode(cur, "normal", "normal", {1});
                                                                }});
                insertTree234Node(key, curNode->next[i], curNode);
                return;
            }
        }
        assert(curNode->next[sz] != nullptr);
        this->animationTree234->instructions.push_back({[this, cur = curNode]()
                                                    {
                                                        this->animationTree234->highlightCurrentNode(cur, "normal", "normal", {1});
                                                    }});
        insertTree234Node(key, curNode->next[sz], curNode);
        return;
    }

    //spliting node anyway: isRoot->split, notRoot->send middle to parent
        
    if (curNode == root) { //split
        auto splitNode = [&]()
        {
            Tree234Node *newLeft = new Tree234Node(curNode->x - 50, curNode->y + 100, scale_x, scale_y, {v[0]}, &font, &Colors);
            Tree234Node *newRight = new Tree234Node(curNode->x + 50, curNode->y + 100, scale_x, scale_y, {v[2]}, &font, &Colors);
            Nodes.push_back(newLeft);
            Nodes.push_back(newRight);

            this->animationTree234->instructions.push_back({[this, cur = curNode, newKey = {v[1]}]()
                                                            {
                                                                this->animationTree234->changeNodeValue(cur, newKey, {1});
                                                            },
                                                            [this, cur = newLeft]()
                                                            {
                                                                this->animationTree234->showNode(cur, "", numberNode, {1});
                                                            },
                                                            [this, cur = newRight]()
                                                            {
                                                                this->animationTree234->showNode(cur, "", numberNode, {1});
                                                            },
                                                            [this, cur = newLeft, nxt = curNode->next[0]]()
                                                            {
                                                                this->animationTree234->connectNodes(cur, nxt, 0, {1});
                                                            },
                                                            [this, cur = newLeft, nxt = curNode->next[1]]()
                                                            {
                                                                this->animationTree234->connectNodes(cur, nxt, 1, {1});
                                                            },
                                                            [this, cur = newRight, nxt = curNode->next[2]]()
                                                            {
                                                                this->animationTree234->connectNodes(cur, nxt, 0, {1});
                                                            },
                                                            [this, cur = newRight, nxt = curNode->next[3]]()
                                                            {
                                                                this->animationTree234->connectNodes(cur, nxt, 1, {1});
                                                            },
                                                            [this, cur = curNode, nxt = newLeft]()
                                                            {
                                                                this->animationTree234->connectNodes(cur, nxt, 0, {1});
                                                            },
                                                            [this, cur = curNode, nxt = newRight]()
                                                            {
                                                                this->animationTree234->connectNodes(cur, nxt, 1, {1});
                                                            },
                                                            // the others must be nullptr
                                                            [this, cur = curNode, nxt = nullptr]()
                                                            {
                                                                this->animationTree234->connectNodes(cur, nxt, 2, {1});
                                                            },
                                                            [this, cur = curNode, nxt = nullptr]()
                                                            {
                                                                this->animationTree234->connectNodes(cur, nxt, 3, {1});
                                                            },
                                                            [this]()
                                                            {
                                                                this->animationTree234->Relayout(0, root, start_x, start_y, nodeDistanceX, nodeDistanceY, {1});
                                                            },
                                                            [this, cur = curNode]()
                                                            {
                                                                this->animationTree234->highlightCurrentNode(cur, "normalFillColor", "normalOutlineColor", {1});
                                                            }});
            waitAnimation();

            // this->animationTree234->instructions.push_back({[this, cur = newLeft, nxt = curNode->next[0]]()
            //                                                 {
            //                                                     this->animationTree234->connectNodes(cur, nxt, 0, {1});
            //                                                 },
            //                                                 [this, cur = newLeft, nxt = curNode->next[1]]()
            //                                                 {
            //                                                     this->animationTree234->connectNodes(cur, nxt, 1, {1});
            //                                                 },
            //                                                 [this, cur = newRight, nxt = curNode->next[2]]()
            //                                                 {
            //                                                     this->animationTree234->connectNodes(cur, nxt, 0, {1});
            //                                                 },
            //                                                 [this, cur = newRight, nxt = curNode->next[3]]()
            //                                                 {
            //                                                     this->animationTree234->connectNodes(cur, nxt, 1, {1});
            //                                                 },
            //                                                 [this, cur = curNode, nxt = newLeft]()
            //                                                 {
            //                                                     this->animationTree234->connectNodes(cur, nxt, 0, {1});
            //                                                 },
            //                                                 [this, cur = curNode, nxt = newRight]()
            //                                                 {
            //                                                     this->animationTree234->connectNodes(cur, nxt, 1, {1});
            //                                                 },
            //                                                 // the others must be nullptr
            //                                                 [this, cur = curNode, nxt = nullptr]()
            //                                                 {
            //                                                     this->animationTree234->connectNodes(cur, nxt, 2, {1});
            //                                                 },
            //                                                 [this, cur = curNode, nxt = nullptr]()
            //                                                 {
            //                                                     this->animationTree234->connectNodes(cur, nxt, 3, {1});
            //                                                 }});
            // waitAnimation();


            // this->animationTree234->instructions.push_back({[this]()
            //                                                 {
            //                                                     this->animationTree234->Relayout(0, root, start_x, start_y, nodeDistanceX, nodeDistanceY, {1});
            //                                                 }});

            // waitAnimation();

            return;
        };
        
        splitNode();
        insertTree234Node(key, curNode, parentNode, 1);
        return;
    }
    // send middle to parent
    assert(v.size() == 3);

    auto sendToPa = [&]()
    {
        std::vector<int> v_pa = parentNode->key;
        assert(v_pa.size() < 3);
        v_pa.push_back(v[1]);
        std::sort(v_pa.begin(), v_pa.end());

        Tree234Node *newRight = new Tree234Node(curNode->x, curNode->y, scale_x, scale_y, {v[2]}, &font, &Colors);
        Nodes.push_back(newRight);

        std::vector<std::function<void()>> newIns = {[this, parent = parentNode, newKey = v_pa]()
                                                        {
                                                            this->animationTree234->changeNodeValue(parent, newKey, {1});
                                                        },
                                                        [this, cur = curNode, newKey = {v[0]}]()
                                                        {
                                                            this->animationTree234->changeNodeValue(cur, newKey, {1});
                                                        },
                                                        //connect newLeft/Right (left(curNode) already connect to 0,1 set 2,3 null)
                                                        [this, cur = curNode, nxt = nullptr]()
                                                        {
                                                            this->animationTree234->connectNodes(cur, nxt, 2, {1});
                                                        },
                                                        [this, cur = curNode, nxt = nullptr]()
                                                        {
                                                            this->animationTree234->connectNodes(cur, nxt, 3, {1});
                                                        },
                                                        [this, cur = newRight, nxt = curNode->next[2]]()
                                                        {
                                                            this->animationTree234->connectNodes(cur, nxt, 0, {1});
                                                        },
                                                        [this, cur = newRight, nxt = curNode->next[3]]()
                                                        {
                                                            this->animationTree234->connectNodes(cur, nxt, 1, {1});
                                                        },
                                                        [this, cur = newRight]()
                                                        {
                                                            this->animationTree234->showNode(cur, "", numberNode, {1});
                                                        }};

        int idx_nxt = -1;
        for (int i = 0; i < numChild234; ++i)
        {
            if (parentNode->next[i] == curNode)
            {
                idx_nxt = i;
                break;
            }
        }
        assert(idx_nxt != -1);
        for (int i = numChild234 - 1; i > idx_nxt + 1; --i)
        {
            // parentNode->next[i] = parentNode->next[i - 1];
            newIns.push_back([this, parent = parentNode, nxt = parentNode->next[i - 1], idx = i]()
                                { this->animationTree234->connectNodes(parent, nxt, idx, {1}); });
        }
        // connect parentNode to newLeft(curNode), newRight
        newIns.push_back([this, parent = parentNode, nxt = curNode, idx = idx_nxt]()
                            { this->animationTree234->connectNodes(parent, nxt, idx, {5}); });

        newIns.push_back([this, parent = parentNode, nxt = newRight, idx = idx_nxt + 1]()
                            { this->animationTree234->connectNodes(parent, nxt, idx, {4}); });

        newIns.push_back([this]()
                         { this->animationTree234->Relayout(0, root, start_x, start_y, nodeDistanceX, nodeDistanceY, {2}); });

        newIns.push_back([this, cur = curNode]()
                         { this->animationTree234->highlightCurrentNode(cur, "normalFillColor", "normalOutlineColor", {3}); });

        this->animationTree234->instructions.push_back(newIns);
        
        waitAnimation();

        // this->animationTree234->instructions.push_back({[this]()
        //                                                 {
        //                                                     this->animationTree234->Relayout(0, root, start_x, start_y, nodeDistanceX, nodeDistanceY, {1});
        //                                                 }});
        // waitAnimation();
        return;
    };
    sendToPa();

    this->animationTree234->instructions.push_back({[this, cur = curNode]()
                                                    {
                                                        this->animationTree234->highlightCurrentNode(cur, "normal", "normal", {1});
                                                    }});

    insertTree234Node(key, parentNode, parentNode, 1);
    return;
}

Tree234Node *Tree234::deleteTree234Node()
{
}

void Tree234::operation_add(int nodeValue)
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

    insertTree234Node(nodeValue, root, root);

    endOperation();
    return;
}

void Tree234::operation_delete()
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

    // this->animationTree234->instructions.push_back({[this]()
    //                                             { this->animationTree234->Relayout((numberNode == 0), root->next[0], start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});

    deleteTree234Node();

    // this->animationTree234->instructions.push_back({[this]()
    //                                             { this->animationTree234->Relayout((numberNode == 0), root->next[0], start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});

    endOperation();
    return;
}

void Tree234::operation_search()
{
}

void Tree234::prepareNewInstruction()
{
    // std::cout << "Prepare new\n";
    this->animation->finishStep();
    bool trash = 0;
    this->animationTree234->last(trash, &this->stepText);
    float tmp_start_x = start_x;
    this->animationTree234->newInstruction(this->root, numberNode, tmp_start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
    this->animationTree234->animationTime = 0.001; /* Do all instruction quickly first, then activate replay mode */
    this->codeHighlight->reset();
}

/* Update and Render */
void Tree234::updateButtons()
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

void Tree234::updateChildButtons()
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

void Tree234::updateInputFields()
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

void Tree234::updateSFMLEvents(const float &dt, sf::Event &event)
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
                //     this->inputWarning.setString("Sorry, the animationTree234 is running...");
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

void Tree234::update(const float &dt)
{
    this->window->setTitle("Tree234");
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

void Tree234::enable_replayButton()
{
    /* Show Replay button */
    this->buttons["Play"]->disabled = 1;
    this->buttons["Pause"]->disabled = 1;
    this->buttons["Replay"]->disabled = 0;
}

void Tree234::renderButtons(sf::RenderTarget *target)
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

void Tree234::renderNode(sf::RenderTarget *target)
{
    for (Tree234Node *node : this->Nodes)
    {
        node->renderArrow(target);
    }
    for (Tree234Node *node : this->Nodes) {
        node->renderNode(target);
    }
}

void Tree234::renderAnimation()
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
        this->animationTree234->play(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "pause")
    {
        this->animationTree234->pause(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "prev")
    {
        this->animationTree234->prev(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "next")
    {
        this->animationTree234->next(this->doneAnimation, &this->stepText);
        if (this->doneAnimation && this->animationTree234->curIndex == (int)this->animationTree234->instructions.size())
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "first")
    {
        this->animationTree234->first(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "last")
    {
        this->animationTree234->last(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }
}

void Tree234::renderHighlightCode(sf::RenderTarget *target)
{
    codeHighlight->render(target);
}

void Tree234::render(sf::RenderTarget *target)
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

void Tree234::reset()
{   
    this->exist.resize(1005);
    exist.assign((int)exist.size(), 0);
    
    this->DeleteNodePointers();

    root = nullptr;

    this->numberNode = 0;

    delete (this->animation);

    this->codeHighlight->reset();
    this->animation = new AnimationTree234(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationTree234 = dynamic_cast<AnimationTree234 *>(this->animation);
    assert(animationTree234 != nullptr);

    this->newStepTriggered = 0;
    this->doneAnimation = 1;
    this->choosingButton = "";
    this->choosingChildButton = "";
    inputWarning.setString("");
    inputGuide.setString("");
    exist.assign((int)exist.size(), 0);
    runState = "";

    /* Init Tree */
    // this->root = new Tree234Node(0, 0, scale_x, scale_y, {1}, &font, &Colors);
    
    // Tree234Node* rubbish = new Tree234Node(100, 100, scale_x, scale_y, {2}, &font, &Colors);
    // Tree234Node* rubbish1 = new Tree234Node(100, 300, scale_x, scale_y, {3}, &font, &Colors);
    // Tree234Node* rubbish2 = new Tree234Node(400, 500, scale_x, scale_y, {2, 3, 4}, &font, &Colors);
    // rubbish->showNode = 1;
    // rubbish1->showNode = 1;
    // rubbish2->showNode = 1;
    // // rubbish->showTextArray = 1;
    // Nodes.push_back(rubbish); // index 0 is inf
    // Nodes.push_back(rubbish1); // index 0 is inf
    // Nodes.push_back(rubbish2); // index 0 is inf

    // rubbish->showArrow[0] = 1;
    // rubbish->newNext(rubbish1, 0);
    // makeArrow234(&rubbish->shape, &rubbish1->shape, &rubbish->arrow[0]);
}

void Tree234::waitAnimation()
{
    /* This function is called immediately after pushing new Animation */
    this->doneAnimation = 0;
    while (!this->doneAnimation)
    {
        this->animationTree234->play(this->doneAnimation, &this->stepText);
    }
    return;
}

void Tree234::endOperation()
{
    this->animationTree234->animationTime = float(speedGap * maxSpeed) / currentSpeed;

    // At the beginning of each operator, we go through all animation immediately, then trigger replay mode
    button_replay();
    return;
}

void Tree234::ReInitButtons()
{
    delete (this->buttons["Update"]);
    delete (this->buttons["Search"]);
    delete (this->buttons["Quit"]);
    this->buttons.erase(buttons.find("Update"));

    this->buttons["Search"] = new Button(
        insButtonX, insButtonY + 4 * insButtonDistanceY, scale_x, scale_y,
        &this->font, "Search", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(240, 180, 10, 255),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(150, 150, 150, 255),
        1, insButtonSizeX, insButtonSizeY);

    this->buttons["Quit"] = new Button(
        insButtonX, insButtonY + 5 * insButtonDistanceY, scale_x, scale_y,
        &this->font, "Quit", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(240, 180, 10, 255),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(150, 150, 150, 255),
        1, insButtonSizeX, insButtonSizeY);
}