#include "Hash.h"

Hash::Hash(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : DataStructure(window, supportedKeys, states)
{
    auto HashScale = [&]()
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
    HashScale();

    ReInitButtons();
    this->initHighlightCode();
    this->initTriggerFunction();
    this->initChildButtons();
    this->initInputFields();
    this->initAnimation();

    reset();
}

Hash::~Hash()
{
    this->DeleteNodePointers();
    delete (this->animationHash);
}

void Hash::DeleteNodePointers()
{
    for (int i = 0; i < (int)Nodes.size(); ++i)  {
        for (auto &v : this->Nodes[i])
        {
            delete (v);
        }
        this->Nodes[i].clear();
    }
    Nodes.clear();
}

/* Init */
void Hash::initTriggerFunction()
{
    auto InstructionButtons = [&]()
    {
        this->triggerFunction["Theme"] = std::bind(&Hash::button_theme, this);
        this->triggerFunction["Initialize"] = std::bind(&Hash::button_initialize, this);
        this->triggerFunction["Add"] = std::bind(&Hash::button_add, this);
        this->triggerFunction["Delete"] = std::bind(&Hash::button_delete, this);
        this->triggerFunction["Search"] = std::bind(&Hash::button_search, this);
        this->triggerFunction["Quit"] = std::bind(&Hash::button_quit, this);
        this->triggerFunction["SpeedMinus"] = std::bind(&Hash::button_SpeedMinus, this);
        this->triggerFunction["SpeedPlus"] = std::bind(&Hash::button_SpeedPlus, this);
        this->triggerFunction["CodeSwitch"] = std::bind(&Hash::button_CodeSwitch, this);
    };

    auto RunButtons = [&]()
    {
        this->triggerFunction["First"] = std::bind(&Hash::button_first, this);
        this->triggerFunction["Prev"] = std::bind(&Hash::button_prev, this);
        this->triggerFunction["Pause"] = std::bind(&Hash::button_pause, this);
        this->triggerFunction["Play"] = std::bind(&Hash::button_play, this);
        this->triggerFunction["Replay"] = std::bind(&Hash::button_replay, this);
        this->triggerFunction["Next"] = std::bind(&Hash::button_next, this);
        this->triggerFunction["Last"] = std::bind(&Hash::button_last, this);
    };

    InstructionButtons();
    RunButtons();
}

void Hash::initChildButtons()
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

void Hash::initInputFields()
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
    init_search();
}

void Hash::initAnimation()
{
    this->animation = new AnimationHash(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationHash = dynamic_cast<AnimationHash *>(this->animation);
    assert(animationHash != nullptr);
    this->animationHash->animationTime = float(speedGap * maxSpeed) / currentSpeed;
}

void Hash::initHighlightCode()
{
    codeHighlight = new CodeHighlight(scale_x, scale_y, &Colors);
}

void Hash::button_theme()
{

    if (this->choosingChildButton == "1Standard")
    {
        this->newStepTriggered = 0;
        this->DataStructureThemeStandard();
        for (int i = 0; i < M_hash; ++i) {
            for (auto &it : Nodes[i])
                it->updateColor();
        }
        this->choosingButton = "";
        return;
    }
    if (this->choosingChildButton == "2Sky")
    {
        this->newStepTriggered = 0;
        this->DataStructureThemeSky();

        for (int i = 0; i < M_hash; ++i) {
            for (auto &it : Nodes[i])
                 it->updateColor();
        }
        this->choosingButton = "";
        return;
    }
    if (this->choosingChildButton == "3Desert")
    {
        this->newStepTriggered = 0;
        this->DataStructureThemeDesert();
        for (int i = 0; i < M_hash; ++i) {
            for (auto &it : Nodes[i])
                it->updateColor();
        }
        this->choosingButton = "";
        return;
    }

    return;
}

/* Instruction Buttons */
void Hash::button_initialize()
{
    auto createNewNode = [&](int newValue)
    {
        // if (this->head == nullptr)
        // {
        //     this->head = new HashNode(this->start_x, this->start_y, this->scale_x, this->scale_y, 12, &this->font, &this->Colors);
        //     this->Nodes.push_back(this->head);
        //     ++this->numberNode;

        //     this->head->val = newValue;
        //     this->tail = head;
        //     return;
        // }
        // /* Add to tail */
        // HashNode *newNode = new HashNode(this->start_x, this->start_y, this->scale_x, this->scale_y, 12, &this->font, &this->Colors);
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
            if (this->valueFirst > maxM)
            {
                this->inputWarning.setString("Sorry, maximum modulo is " + std::to_string(maxM));
                return;
            }
            if (this->valueSecond > maxNode)
            {
                this->inputWarning.setString("Sorry, maximum size is " + std::to_string(maxNode));
                return;
            }
        }
        else
        {
            this->inputGuide.setString("Input [mod, size]");
            return;
        }

        this->reset();
        prepareNewInstruction();

        auto addHighlightCodes = [&]
        {
            // codeHighlight->introText.setString("Random HashTree with " + std::to_string(valueFirst) + " node" + (valueFirst > 1 ? "s" : ""));
            codeHighlight->codeStrings.resize(100); // fake highlight
            this->codeHighlight->updateTexts();
        };
        initHash(valueFirst);
        std::vector<int> values(200);
        for (int i = 0; i < 200; ++i)
            values[i] = i + 1;
        std::shuffle(values.begin(), values.end(), this->randomize);
        for (int i = 0; i < this->valueSecond; ++i)
        {
            int newValue = values[i];
    
            this->animationHash->newInstruction(Nodes, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
            addHighlightCodes();
            insertHashNode(newValue);
        }
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
            codeHighlight->introText.setString("Load Hash Table from file");
            codeHighlight->codeStrings.resize(100); // fake highlight
            this->codeHighlight->updateTexts();
        };

        std::ifstream inp;
        inp.open("InputFiles/inputHash.txt");
        int newValue = 0;
        inp >> numberNode >> M_hash;
        initHash(M_hash);
        while (inp >> newValue)
        {
            this->animationHash->newInstruction(Nodes, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
            addHighlightCodes();
            insertHashNode(newValue);
        }
        inp.close();

        // this->animationHash->updateNodePosition(this->head, this->tail, this->start_x, this->start_y, this->nodeDistanceX);
        return;
    }
}

void Hash::button_add()
{
    this->choosingChildButton = "1Head";

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

void Hash::button_delete()
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

void Hash::button_search()
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

void Hash::button_quit()
{
    this->endState();
}

// Hash Operations

void Hash::insertHashNode(int nodeValue)
{
    int hashCode = nodeValue % M_hash;
    HashNode *cur = Nodes[hashCode][0];

    for (;; cur = cur->next) {
        if (cur->next == nullptr) {
            HashNode *newNode = new HashNode(cur->x, cur->y + nodeDistanceY, scale_x, scale_y, nodeValue, &font, &Colors);
            Nodes[hashCode].push_back(newNode);
            this->animationHash->instructions.push_back({[this, newNode]()
                                                         { this->animationHash->showNode(newNode, "", {1}); },
                                                         [this, cur, newNode]()
                                                         { this->animationHash->connectNodes(cur, newNode, {}); }});
            waitAnimation();
            break;
        }
    }
}

void Hash::deleteHashNode(int nodeValue)
{
    int hashCode = nodeValue % M_hash;
    HashNode *tmp_head = Nodes[hashCode][0];
    HashNode *cur = tmp_head;

    for (; cur != nullptr && cur->next != nullptr; cur = cur->next) {
        if (cur != tmp_head) {
            this->animationHash->instructions.push_back({[this, cur]()
                                                         { this->animationHash->highlightCurrentNode(cur, "", "normal", {1}); },
                                                         [this, nxt = cur->next]()
                                                         { this->animationHash->highlightCurrentNode(nxt, "", "currentColor", {1}); }});
        }
        else {
            this->animationHash->instructions.push_back({[this, nxt = cur->next]()
                                                         { this->animationHash->highlightCurrentNode(nxt, "", "currentColor", {1}); }});
        }

        if (cur->next->key == nodeValue) {
            HashNode *tmp = cur->next;
    
            this->animationHash->instructions.push_back({[this, cur, nxt = cur->next->next]()
                                                         { this->animationHash->connectNodes(cur, nxt, {1}); }});

            this->animationHash->instructions.push_back({[this, tmp]()
                                                         { this->animationHash->hideNode(tmp, {1}); },
                                                         [this, tmp_head]()
                                                         { this->animationHash->Relayout(0, tmp_head, tmp_head->x, tmp_head->y, nodeDistanceX, nodeDistanceY, {}); }});
            waitAnimation();
            break;
        }
        if (cur->next->next == nullptr) {
            this->animationHash->instructions.push_back({[this, nxt = cur->next]()
                                                         { this->animationHash->highlightCurrentNode(nxt, "", "normal", {1}); }});
        }
    }
}

void Hash::initHash(int M)
{   
    M_hash = M;
    Nodes.resize(M);
    for (int i = 0; i < M; ++i) {
        Nodes[i].resize(1);
        Nodes[i][0] = new HashNode(start_x + i * nodeDistanceX, start_y, scale_x, scale_y, -1, &font, &Colors);
        Nodes[i][0]->showNode = 1;
        Nodes[i][0]->newColor("newColor", "newColor");
        Nodes[i][0]->nextColor();

        Nodes[i][0]->newLabel(std::to_string(i));
        Nodes[i][0]->nextLabel();
    }
}

void Hash::operation_add(int nodeValue)
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

    insertHashNode(nodeValue);
    endOperation();
    return;
}

void Hash::operation_delete(int nodeValue)
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

        return true;
    };
    if (!preCheck())
    {
        return;
    }

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

    deleteHashNode(nodeValue);

    endOperation();
    return;
}

void Hash::operation_search(int nodeValue)
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

    int hashCode = nodeValue % M_hash;
    HashNode *tmp_head = Nodes[hashCode][0];
    HashNode *cur = tmp_head;

    for (; cur != nullptr && cur->next != nullptr; cur = cur->next) {
        if (cur != tmp_head)
        {
            this->animationHash->instructions.push_back({[this, cur]()
                                                         { this->animationHash->highlightCurrentNode(cur, "", "normal", {1}); },
                                                         [this, nxt = cur->next, nodeValue]()
                                                         { this->animationHash->highlightCurrentNode(nxt, "", (nxt->key == nodeValue) ? "reachColor" : "currentColor", {1}); }});
        }
        else
        {
            this->animationHash->instructions.push_back({[this, nxt = cur->next, nodeValue]()
                                                         { this->animationHash->highlightCurrentNode(nxt, "", (nxt->key == nodeValue) ? "reachColor" : "currentColor", {1}); }});
        }

        if (cur->next->key == nodeValue) {
            break;
        }
        if (cur->next->next == nullptr) {
            this->animationHash->instructions.push_back({[this, nxt = cur->next]()
                                                         { this->animationHash->highlightCurrentNode(nxt, "", "normal", {1}); }});
        }
    }

    endOperation();
    return;
}

void Hash::prepareNewInstruction()
{
    // std::cout << "Prepare new\n";
    this->animation->finishStep();
    bool trash = 0;
    this->animationHash->last(trash, &this->stepText);
    this->animationHash->newInstruction(Nodes, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
    this->animationHash->animationTime = 0.001; /* Do all instruction quickly first, then activate replay mode */
    this->codeHighlight->reset();
}

/* Update and Render */
void Hash::updateButtons()
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

void Hash::updateChildButtons()
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

void Hash::updateInputFields()
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

void Hash::updateSFMLEvents(const float &dt, sf::Event &event)
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
                //     this->inputWarning.setString("Sorry, the animationHash is running...");
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

void Hash::update(const float &dt)
{
    this->window->setTitle("Hash");
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

void Hash::enable_replayButton()
{
    /* Show Replay button */
    this->buttons["Play"]->disabled = 1;
    this->buttons["Pause"]->disabled = 1;
    this->buttons["Replay"]->disabled = 0;
}

void Hash::renderButtons(sf::RenderTarget *target)
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

void Hash::renderNode(sf::RenderTarget *target)
{
    for (int i = 0; i < (int)Nodes.size(); ++i)
    {
        for (HashNode *node : this->Nodes[i])
        { 
            node->render(target);
        }
    }
}

void Hash::renderAnimation()
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
        this->animationHash->play(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "pause")
    {
        this->animationHash->pause(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "prev")
    {
        this->animationHash->prev(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "next")
    {
        this->animationHash->next(this->doneAnimation, &this->stepText);
        if (this->doneAnimation && this->animationHash->curIndex == (int)this->animationHash->instructions.size())
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "first")
    {
        this->animationHash->first(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "last")
    {
        this->animationHash->last(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }
}

void Hash::renderHighlightCode(sf::RenderTarget *target)
{
    codeHighlight->render(target);
}

void Hash::render(sf::RenderTarget *target)
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

void Hash::reset()
{   
    this->DeleteNodePointers();
    // this->root = new HashNode(0, 0, scale_x, scale_y, 100000, &font, &Colors);
    this->numberNode = 0, M_hash = 0;
    initHash(20); 
    
    //init HashTable

    delete (this->animation);

    this->codeHighlight->reset();
    this->animation = new AnimationHash(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationHash = dynamic_cast<AnimationHash *>(this->animation);
    assert(animationHash != nullptr);

    this->newStepTriggered = 0;
    this->doneAnimation = 1;
    this->choosingButton = "";
    this->choosingChildButton = "";
    inputWarning.setString("");
    inputGuide.setString("");
    runState = "";
}

void Hash::waitAnimation()
{
    /* This function is called immediately after pushing new Animation */
    this->doneAnimation = 0;
    while (!this->doneAnimation)
    {
        this->animationHash->play(this->doneAnimation, &this->stepText);
    }
    return;
}

void Hash::endOperation()
{
    this->animationHash->animationTime = float(speedGap * maxSpeed) / currentSpeed;

    // At the beginning of each operator, we go through all animation immediately, then trigger replay mode
    button_replay();
    return;
}

void Hash::ReInitButtons()
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

    return;
}