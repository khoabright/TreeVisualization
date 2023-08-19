#include "Trie.h"

Trie::Trie(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : DataStructure(window, supportedKeys, states)
{
    auto TrieScale = [&]()
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
    TrieScale();

    this->initHighlightCode();
    this->initTriggerFunction();
    this->initChildButtons();
    this->initInputFields();
    this->initAnimation();

    reset();
}

Trie::~Trie()
{
    this->DeleteNodePointers();
    delete (this->animationTrie);
}

void Trie::DeleteNodePointers()
{
    for (auto &v : this->Nodes)
    {
        delete (v);
    }
    this->Nodes.clear();
}

/* Init */
void Trie::initTriggerFunction()
{
    auto InstructionButtons = [&]()
    {
        this->triggerFunction["Theme"] = std::bind(&Trie::button_theme, this);
        this->triggerFunction["Initialize"] = std::bind(&Trie::button_initialize, this);
        this->triggerFunction["Add"] = std::bind(&Trie::button_add, this);
        this->triggerFunction["Delete"] = std::bind(&Trie::button_delete, this);
        this->triggerFunction["Update"] = std::bind(&Trie::button_update, this);
        this->triggerFunction["Search"] = std::bind(&Trie::button_search, this);
        this->triggerFunction["Quit"] = std::bind(&Trie::button_quit, this);
        this->triggerFunction["SpeedMinus"] = std::bind(&Trie::button_SpeedMinus, this);
        this->triggerFunction["SpeedPlus"] = std::bind(&Trie::button_SpeedPlus, this);
        this->triggerFunction["CodeSwitch"] = std::bind(&Trie::button_CodeSwitch, this);
    };

    auto RunButtons = [&]()
    {
        this->triggerFunction["First"] = std::bind(&Trie::button_first, this);
        this->triggerFunction["Prev"] = std::bind(&Trie::button_prev, this);
        this->triggerFunction["Pause"] = std::bind(&Trie::button_pause, this);
        this->triggerFunction["Play"] = std::bind(&Trie::button_play, this);
        this->triggerFunction["Replay"] = std::bind(&Trie::button_replay, this);
        this->triggerFunction["Next"] = std::bind(&Trie::button_next, this);
        this->triggerFunction["Last"] = std::bind(&Trie::button_last, this);
    };

    InstructionButtons();
    RunButtons();
}

void Trie::initChildButtons()
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

void Trie::initInputFields()
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

void Trie::initAnimation()
{
    this->animation = new AnimationTrie(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationTrie = dynamic_cast<AnimationTrie *>(this->animation);
    assert(animationTrie != nullptr);
    this->animationTrie->animationTime = float(speedGap * maxSpeed) / currentSpeed;
}

void Trie::initHighlightCode()
{
    codeHighlight = new CodeHighlight(scale_x, scale_y, &Colors);
}

void Trie::button_theme()
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
void Trie::button_initialize()
{
    auto createNewNode = [&](int newValue)
    {
        // if (this->head == nullptr)
        // {
        //     this->head = new TrieNode(this->start_x, this->start_y, this->scale_x, this->scale_y, 12, &this->font, &this->Colors);
        //     this->Nodes.push_back(this->head);
        //     ++this->numberNode;

        //     this->head->val = newValue;
        //     this->tail = head;
        //     return;
        // }
        // /* Add to tail */
        // TrieNode *newNode = new TrieNode(this->start_x, this->start_y, this->scale_x, this->scale_y, 12, &this->font, &this->Colors);
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
            this->inputGuide.setString("Input number of words");
            return;
        }

        this->reset();
        prepareNewInstruction();

        auto addHighlightCodes = [&]
        {
            codeHighlight->introText.setString("Random Trie with " + std::to_string(valueFirst) + " word" + (valueFirst > 1 ? "s" : ""));
            codeHighlight->codeStrings.resize(100); // fake highlight
            this->codeHighlight->updateTexts();
        };
        // std::vector<int> values(200);
        // for (int i = 0; i < 200; ++i)
        //     values[i] = i + 1;
        // std::shuffle(values.begin(), values.end(), this->randomize);
        
        auto randomWord = [&]() {
            int sz = std::rand() % 4;
            std::string Str = "";
            for (int i = 0; i < sz; ++i) {
                int x = rand() % 4;
                Str += (x + 'A');
            }
            return Str;
        };

        for (int i = 0; i < this->valueFirst; ++i)
        {
            this->animationTrie->newInstruction(this->root, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
            addHighlightCodes();
            std::string newStr = randomWord();
            insertTrieNode(root, newStr);
        }
        // this->animationTrie->updateNodePosition(this->root, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
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
        inp.open("InputFiles/inputTrie.txt");
        std::string Str;
        while (inp >> Str)
        {
            this->animationTrie->newInstruction(this->root, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
            addHighlightCodes();
            insertTrieNode(root, Str);
        }
        inp.close();
        this->animationTrie->newInstruction(this->root, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
        return;
    }
}

void Trie::button_add()
{
    this->choosingChildButton = "1Head";

    if (this->newStepTriggered)
    {
        this->newStepTriggered = 0;
        this->inputGuide.setString("");
        this->operation_add(this->inputStr);

        return;
    }
    else
    {
        this->inputGuide.setString("Input a value");
    }
}

void Trie::button_delete()
{
    this->choosingChildButton = "1Head";

    if (this->newStepTriggered)
    {
        this->newStepTriggered = 0;
        this->inputGuide.setString("");
        this->operation_delete(this->inputStr);
        return;
    }
    else
    {
        this->inputGuide.setString("Input a value");
    }
}

void Trie::button_update()
{
}

void Trie::button_search()
{
    this->choosingChildButton = "1Search";

    if (this->newStepTriggered)
    {
        this->newStepTriggered = 0;
        this->inputGuide.setString("");
        this->operation_search(this->inputStr);
        return;
    }
    else
    {
        this->inputGuide.setString("Input a value to search");
    }
}

void Trie::button_quit()
{
    this->endState();
}

// Trie Operations

void Trie::insertTrieNode(TrieNode *curNode, std::string newStr)
{   
    TrieNode *now = curNode;
    this->animationTrie->instructions.push_back({[this, cur = now]()
                                                { this->animationTrie->highlightCurrentNode(cur, "reachColor", {5}); }});

    for(char c : newStr){
        int x = c - 'A';
        if(!now->next[x]) {
            TrieNode *newNode = new TrieNode(start_x - 2 * nodeDistanceX, start_y, scale_x, scale_y, x, &font, &Colors);
            this->Nodes.push_back(newNode);
            this->animationTrie->instructions.push_back({[this, newNode]()
                                                        { this->animationTrie->showNode(newNode, "0", this->numberNode, {1}); },
                                                        [this, parentNode = now]()
                                                        { this->animationTrie->highlightCurrentNode(parentNode, "normal", {5}); },
                                                        [this, parentNode = now, newNode, x]()
                                                        { this->animationTrie->connectNodes(parentNode, newNode, x, {5}); }});

            waitAnimation();
            this->animationTrie->instructions.push_back({[this, newNode]()
                                                        { this->animationTrie->Relayout(0, root, start_x, start_y, nodeDistanceX, nodeDistanceY, {1}); }});
            waitAnimation();
            // now->a[x]= new node;
        }
        else {
            this->animationTrie->instructions.push_back({[this, cur = now]()
                                                { this->animationTrie->highlightCurrentNode(cur, "normal", {5}); }, 
                                                [this, nxt = now->next[x]]()
                                                { this->animationTrie->highlightCurrentNode(nxt, "reachColor", {5}); }});
            waitAnimation();
        }
        now=now->next[x];
    }
    this->animationTrie->instructions.push_back({[this, cur = now]()
                                                 { this->animationTrie->changeNodeLabel(cur, "1", {}); }});
    waitAnimation();
    now->isEnd=true;
}

void Trie::deleteTrieNode(TrieNode *curNode, std::string delStr)
{
    TrieNode *now = curNode;

    std::stack<std::pair<TrieNode*, int>> st;
    this->animationTrie->instructions.push_back({[this, cur = now]()
                                                     { this->animationTrie->highlightCurrentNode(cur, "reachColor", {5}); }});

    for(char c : delStr){
        int x = c - 'A';
        
        st.push({now, x});

        if(!now->next[x]) {
            this->animationTrie->instructions.push_back({[this, cur = now]()
                                                     { this->animationTrie->highlightCurrentNode(cur, "normal", {5}); }});
            return;
        }

        this->animationTrie->instructions.push_back({[this, cur = now]()
                                                { this->animationTrie->highlightCurrentNode(cur, "normal", {5}); }, 
                                                [this, nxt = now->next[x]]()
                                                { this->animationTrie->highlightCurrentNode(nxt, "reachColor", {5}); }});

        now = now->next[x];
    }
    if (!now->isEnd) return;
    now->isEnd = 0;
    this->animationTrie->instructions.push_back({[this, cur = now]()
                                                 { this->animationTrie->changeNodeLabel(cur, "0", {}); }});

    while (!st.empty()) {
        TrieNode* node = st.top().first;
        int x = st.top().second;
        st.pop();
        assert(node->next[x] != nullptr);

        if (node->next[x]->isEnd == 0 && node->next[x]->isLeaf()) {
            this->animationTrie->instructions.push_back({[this, cur = node]()
                                                         { this->animationTrie->highlightCurrentNode(cur, "reachColor", {5}); },
                                                         [this, nxt = node->next[x]]()
                                                         { this->animationTrie->highlightCurrentNode(nxt, "normal", {5}); },
                                                         [this, nxt = node->next[x]]()
                                                         { this->animationTrie->hideNode(nxt, numberNode, {5}); },
                                                         [this, cur = node, idx_nxt = x]()
                                                         { this->animationTrie->connectNodes(cur, nullptr, idx_nxt, {5}); }});
            waitAnimation();
        }

        else {
            this->animationTrie->instructions.push_back({[this, cur = node]()
                                                    { this->animationTrie->highlightCurrentNode(cur, "reachColor", {5}); }, 
                                                    [this, nxt = node->next[x]]()
                                                    { this->animationTrie->highlightCurrentNode(nxt, "normal", {5}); }});
            waitAnimation();
        }
    }

    this->animationTrie->instructions.push_back({[this]()
                                                    { this->animationTrie->Relayout(0, root, start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});
    waitAnimation();

    return;
}

void Trie::operation_add(std::string newStr)
{
    this->prepareNewInstruction();
    this->button_play();

    auto preCheck = [&]()
    {
        if ((int)inputStr.size() > maxSizeInput)
        {
            this->inputWarning.setString("Maximum input length is " + std::to_string(maxSizeInput));
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
        codeHighlight->introText.setString("Insert " + newStr);
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

    insertTrieNode(this->root, newStr);

    endOperation();
    return;
}

void Trie::operation_delete(std::string delStr)
{
    this->prepareNewInstruction();
    this->button_play();

    auto preCheck = [&]()
    {
        return true;
    };
    if (!preCheck())
    {
        return;
    }

    auto addHighlightCodes = [&]
    {
        codeHighlight->introText.setString("Delete");
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

    // this->animationTrie->instructions.push_back({[this]()
    //                                             { this->animationTrie->Relayout((numberNode == 0), root, start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});

    deleteTrieNode(this->root, delStr);

    // this->animationTrie->instructions.push_back({[this]()
    //                                             { this->animationTrie->Relayout((numberNode == 0), root, start_x, start_y, nodeDistanceX, nodeDistanceY, {5}); }});

    endOperation();
    return;
}

void Trie::operation_search(std::string findStr)
{      
    this->prepareNewInstruction();
    this->button_play();

    auto preCheck = [&]()
    {
        return true;
    };
    if (!preCheck())
    {
        return;
    }

    auto addHighlightCodes = [&]
    {
        codeHighlight->introText.setString("Search");
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

    TrieNode *now = root;
    this->animationTrie->instructions.push_back({[this, cur = now]()
                                                { this->animationTrie->highlightCurrentNode(cur, "reachColor", {5}); }});

    for(char c : findStr){
        int x = c - 'A';
        if(!now->next[x]) {
            this->animationTrie->instructions.push_back({[this, cur = now]()
                                                        { this->animationTrie->highlightCurrentNode(cur, "normal", {5}); }});

            waitAnimation();
            break;
        }
        else {
            this->animationTrie->instructions.push_back({[this, cur = now]()
                                                { this->animationTrie->highlightCurrentNode(cur, "normal", {5}); }, 
                                                [this, nxt = now->next[x]]()
                                                { this->animationTrie->highlightCurrentNode(nxt, "reachColor", {5}); }});
            waitAnimation();
        }
        now=now->next[x];
    }

    std::string isFoundColor = (now->isEnd) ? "newColor" : "normal";
    this->animationTrie->instructions.push_back({[this, cur = now, isFoundColor]()
                                                 { this->animationTrie->highlightCurrentNode(cur, isFoundColor, {}); }});
    waitAnimation();

    endOperation();
    return;
}

void Trie::prepareNewInstruction()
{
    // std::cout << "Prepare new\n";
    this->animation->finishStep();
    bool trash = 0;
    this->animationTrie->last(trash, &this->stepText);
    this->animationTrie->newInstruction(this->root, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
    this->animationTrie->animationTime = 0.001; /* Do all instruction quickly first, then activate replay mode */
    this->codeHighlight->reset();
}

/* Update and Render */
void Trie::updateButtons()
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

void Trie::updateChildButtons()
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

void Trie::updateInputFields()
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

void Trie::updateSFMLEvents(const float &dt, sf::Event &event)
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
                        inputStr = str;
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
                //     this->inputWarning.setString("Sorry, the animationTrie is running...");
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

void Trie::update(const float &dt)
{
    this->window->setTitle("Trie");
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

void Trie::enable_replayButton()
{
    /* Show Replay button */
    this->buttons["Play"]->disabled = 1;
    this->buttons["Pause"]->disabled = 1;
    this->buttons["Replay"]->disabled = 0;
}

void Trie::renderButtons(sf::RenderTarget *target)
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

void Trie::renderNode(sf::RenderTarget *target)
{
    for (TrieNode *node : this->Nodes)
    {
        node->render(target);
    }
}

void Trie::renderAnimation()
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
        this->animationTrie->play(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "pause")
    {
        this->animationTrie->pause(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "prev")
    {
        this->animationTrie->prev(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "next")
    {
        this->animationTrie->next(this->doneAnimation, &this->stepText);
        if (this->doneAnimation && this->animationTrie->curIndex == (int)this->animationTrie->instructions.size())
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "first")
    {
        this->animationTrie->first(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "last")
    {
        this->animationTrie->last(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }
}

void Trie::renderHighlightCode(sf::RenderTarget *target)
{
    codeHighlight->render(target);
}

void Trie::render(sf::RenderTarget *target)
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

void Trie::reset()
{   
    this->exist.resize(1005);
    exist.assign((int)exist.size(), 0);
    
    this->DeleteNodePointers();
    this->root = new TrieNode(start_x, start_y, scale_x, scale_y, 100000, &font, &Colors);
    root->showNode = 1;
    Nodes.push_back(root);
    this->numberNode = 1;

    delete (this->animation);

    this->codeHighlight->reset();
    this->animation = new AnimationTrie(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationTrie = dynamic_cast<AnimationTrie *>(this->animation);
    assert(animationTrie != nullptr);

    this->newStepTriggered = 0;
    this->doneAnimation = 1;
    this->choosingButton = "";
    this->choosingChildButton = "";
    inputWarning.setString("");
    inputGuide.setString("");
    exist.assign((int)exist.size(), 0);
    runState = "";
}

void Trie::waitAnimation()
{
    /* This function is called immediately after pushing new Animation */
    this->doneAnimation = 0;
    while (!this->doneAnimation)
    {
        this->animationTrie->play(this->doneAnimation, &this->stepText);
    }
    return;
}

void Trie::endOperation()
{
    this->animationTrie->animationTime = float(speedGap * maxSpeed) / currentSpeed;

    // At the beginning of each operator, we go through all animation immediately, then trigger replay mode
    button_replay();
    return;
}
