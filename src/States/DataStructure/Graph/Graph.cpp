#include "Graph.h"

Graph::Graph(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : DataStructure(window, supportedKeys, states)
{
    auto GraphScale = [&]()
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
    GraphScale();

    this->ReInitButtons();
    this->initHighlightCode();
    this->initTriggerFunction();
    this->initChildButtons();
    this->initInputFields();
    this->initAnimation();

    reset();
}

Graph::~Graph()
{
    this->DeleteNodePointers();
    delete (this->animationGraph);
}

void Graph::DeleteNodePointers()
{
    for (auto &v : this->Nodes)
    {
        delete (v);
    }
    this->Nodes.clear();
    for (auto &e : this->Edges){
        delete(e);
    }
    this->Edges.clear();
}

/* Init */
void Graph::initTriggerFunction()
{
    auto InstructionButtons = [&]()
    {
        this->triggerFunction["Theme"] = std::bind(&Graph::button_theme, this);
        this->triggerFunction["Initialize"] = std::bind(&Graph::button_initialize, this);
        this->triggerFunction["BFS"] = std::bind(&Graph::button_bfs, this);
        this->triggerFunction["MST"] = std::bind(&Graph::button_MST, this);
        this->triggerFunction["Dijkstra"] = std::bind(&Graph::button_dijkstra, this);
        this->triggerFunction["Quit"] = std::bind(&Graph::button_quit, this);
        this->triggerFunction["SpeedMinus"] = std::bind(&Graph::button_SpeedMinus, this);
        this->triggerFunction["SpeedPlus"] = std::bind(&Graph::button_SpeedPlus, this);
        this->triggerFunction["CodeSwitch"] = std::bind(&Graph::button_CodeSwitch, this);
    };

    auto RunButtons = [&]()
    {
        this->triggerFunction["First"] = std::bind(&Graph::button_first, this);
        this->triggerFunction["Prev"] = std::bind(&Graph::button_prev, this);
        this->triggerFunction["Pause"] = std::bind(&Graph::button_pause, this);
        this->triggerFunction["Play"] = std::bind(&Graph::button_play, this);
        this->triggerFunction["Replay"] = std::bind(&Graph::button_replay, this);
        this->triggerFunction["Next"] = std::bind(&Graph::button_next, this);
        this->triggerFunction["Last"] = std::bind(&Graph::button_last, this);
    };

    InstructionButtons();
    RunButtons();
}

void Graph::initChildButtons()
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

void Graph::initInputFields()
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

    auto init_bfs = [&]()
    {
        ++idy;
        this->inputFields["BFS"]["1BFS"] = new InputField(this->inputFieldOriginX,
                                                           this->inputFieldOriginY + (idy - 1) * (this->inputFieldHeight + this->inputFieldDistanceY),
                                                           this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                                           &this->font, this->inputFieldCharacterSize,
                                                           sf::Color::White, sf::Color::White, sf::Color::Black);
    };

    auto init_MST = [&]()
    {
        ++idy;
        this->inputFields["MST"]["1MST"] = new InputField(this->inputFieldOriginX,
                                                           this->inputFieldOriginY + (idy - 1) * (this->inputFieldHeight + this->inputFieldDistanceY),
                                                           this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                                           &this->font, this->inputFieldCharacterSize,
                                                           sf::Color::White, sf::Color::White, sf::Color::Black);
    };

    auto init_dijkstra = [&]()
    {
        ++idy;
        this->inputFields["Dijkstra"]["1Dijkstra"] = new InputField(this->inputFieldOriginX,
                                                           this->inputFieldOriginY + (idy - 1) * (this->inputFieldHeight + this->inputFieldDistanceY),
                                                           this->inputFieldWidth, this->inputFieldHeight, this->scale_x, this->scale_y,
                                                           &this->font, this->inputFieldCharacterSize,
                                                           sf::Color::White, sf::Color::White, sf::Color::Black);
    };

    init_initialize();
    init_bfs();
    init_MST();
    init_dijkstra();
}

void Graph::initAnimation()
{
    this->animation = new AnimationGraph(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationGraph = dynamic_cast<AnimationGraph *>(this->animation);
    assert(animationGraph != nullptr);
    this->animationGraph->animationTime = float(speedGap * maxSpeed) / currentSpeed;
}

void Graph::initHighlightCode()
{
    codeHighlight = new CodeHighlight(scale_x, scale_y, &Colors);
}

void Graph::button_theme()
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
void Graph::button_initialize()
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
        // if (this->newStepTriggered)
        // {
        //     this->newStepTriggered = 0;
        //     this->inputGuide.setString("");
        //     if (this->valueFirst > maxNode)
        //     {
        //         this->inputWarning.setString("Sorry, maximum size is " + std::to_string(maxNode));
        //         return;
        //     }
        // }
        // else
        // {
        //     this->inputGuide.setString("Input a size");
        //     return;
        // }

        // this->reset();
        // prepareNewInstruction();

        // auto addHighlightCodes = [&]
        // {
        //     codeHighlight->introText.setString("Random GraphTree with " + std::to_string(valueFirst) + " node" + (valueFirst > 1 ? "s" : ""));
        //     codeHighlight->codeStrings.resize(100); // fake highlight
        //     this->codeHighlight->updateTexts();
        // };
        // std::vector<int> values(200);
        // for (int i = 0; i < 200; ++i)
        //     values[i] = i + 1;
        // std::shuffle(values.begin(), values.end(), this->randomize);
        // for (int i = 0; i < this->valueFirst; ++i)
        // {
        //     int newValue = values[i];
        //     // this->animationGraph->newInstruction(this->root, arrNode, numberNode, this->start_x, this->start_y, this->nodeDistanceX, this->nodeDistanceY);
        //     addHighlightCodes();
        //     insertGraphNode(newValue);
        // }

        // return;
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
        inp.open("InputFiles/inputGraph.txt");
        int newValue = 0;
        inp >> numberNode;
        adj_matrix.resize(numberNode + 2, std::vector<int> (numberNode + 2));
        for (int x = 1; x <= numberNode; ++x)
        for (int y = 1; y <= numberNode; ++y)
        {
            inp >> adj_matrix[x][y];
        }
        buildGraph();
        inp.close();

        return;
    }
}

void Graph::button_bfs()
{
    operation_bfs();
    return;
}

void Graph::button_MST()
{   
    this->choosingChildButton = "1MST";

    if (this->newStepTriggered)
    {
        operation_MST(valueFirst);        
        return;
    }
    else
    {
        this->inputGuide.setString("Input start node");
    }
    return;
}

void Graph::button_dijkstra()
{
    this->choosingChildButton = "1Dijkstra";

    if (this->newStepTriggered)
    {
        operation_dijkstra(valueFirst);
        return;
    }
    else
    {
        this->inputGuide.setString("Input start node");
    }
    return;
}


void Graph::button_quit()
{
    this->endState();
}

// Graph Operations

void Graph::GraphLayout(int iterations, float k, float c, float l) {
    // Initialize positions within the specified bounds
    for (auto& node : Nodes) {
        if (node == nullptr) continue;
        node->x = start_x + (end_x - start_x) * static_cast<float>(rand()) / RAND_MAX;
        node->y = start_y + (end_y - start_y) * static_cast<float>(rand()) / RAND_MAX;
    }

    for (int iter = 0; iter < iterations; ++iter) {
        // Calculate repulsive forces
        for (auto& node1 : Nodes) {
            if (node1 == nullptr) continue;
            // node1->x = 0;
            // node1->y = 0;
            for (auto& node2 : Nodes) {
                if (node2 == nullptr) continue;
                if (node1 != node2) {
                    float dx = node1->x - node2->x;
                    float dy = node1->y - node2->y;
                    float dist = std::max(std::sqrt(dx * dx + dy * dy), 0.1f); // Avoid division by zero
                    float repulsive_force = l * l / dist;
                    node1->x += repulsive_force * dx / dist;
                    node1->y += repulsive_force * dy / dist;
                    // std::cout<<"repul x,y="<<node1->x<<' '<<node1->y<<'\n';
                }
            }
        }

        // Calculate attractive forces based on the adjacency matrix
        for (int i = 1; i <= numberNode; ++i) {
            for (int j = 1; j <= numberNode; ++j) {
                if (i != j && adj_matrix[i][j] > 0) {
                    float dx = Nodes[i]->x - Nodes[j]->x;
                    float dy = Nodes[i]->y - Nodes[j]->y;
                    float dist = std::max(std::sqrt(dx * dx + dy * dy), 0.1f);
                    float attractive_force = c * dist * dist / l;
                    Nodes[i]->x -= attractive_force * dx / dist;
                    Nodes[i]->y += attractive_force * dy / dist;

                    // std::cout<<"attract x,y="<<Nodes[i]->x<<' '<<Nodes[i]->y<<'\n';
                }
            }
        }
    }

    // Keep nodes within screen bounds
    // for (auto& node : Nodes) {
    //     if (node == nullptr) continue;
    //     node->x = std::max(start_x + node->radius, std::min(end_x - node->radius, node->x));
    //     node->y = std::max(start_y + node->radius, std::min(end_y - node->radius, node->y));
    // }
}

void Graph::buildGraph()
{      
    for (int i = 1; i <= numberNode; ++i) {
        float x = start_x + rand() % (int)(end_x - start_x);
        float y = start_y + rand() % (int)(end_y - start_y);
        // std::cout<<"i,x,y="<<i<<' '<<x<<' '<<y<<'\n';
        GraphNode* newNode = new GraphNode(x, y, scale_x, scale_y, i, &font, &Colors);
        Nodes.push_back(newNode);
    }
    GraphLayout();
    for (int i = 1; i <= numberNode; ++i) {
        if (Nodes[i] == nullptr) continue;
        Nodes[i]->newPos(sf::Vector2f(Nodes[i]->x, Nodes[i]->y));
        Nodes[i]->nextPos();
    }

    for (int x = 1; x <= numberNode; ++x)
    for (int y = x + 1; y <= numberNode; ++y)
    {
        if (adj_matrix[x][y] == 0) continue;
        GraphEdge *newEdge = new GraphEdge(Nodes[x], Nodes[y], adj_matrix[x][y], &font, &Colors);
        Edges.push_back(newEdge);
    }
}

void Graph::operation_bfs()
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
        codeHighlight->introText.setString("Count connected components");
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

    std::vector<bool> visited(numberNode + 2);

    auto bfs = [&](int startNode)
    {
        std::queue<GraphNode *> q;
        q.push(Nodes[startNode]);

        this->animationGraph->instructions.push_back({[this, node = Nodes[startNode]]()
                                                      { this->animationGraph->highlightCurrentNode(node, "normalFillColor", "newColor", {1}); }});
        waitAnimation();

        int lastVisit = 0; // for unhighlight last visit node

        while (!q.empty())
        {
            GraphNode *cur = q.front();

            this->animationGraph->instructions.push_back({[this, node = cur]()
                                                          { this->animationGraph->highlightCurrentNode(node, "newColor", "newColor", {1}); },
                                                          [this, lastNode = Nodes[lastVisit]]()
                                                          { this->animationGraph->highlightCurrentNode(lastNode, "normalFillColor", "reachColor", {1}); }});
            waitAnimation();

            q.pop();
            visited[cur->key] = 1;

            for (auto edge : Edges)
            {
                if (edge->from != cur->key && edge->to != cur->key)
                    continue;
                int v = (edge->from == cur->key) ? edge->to : edge->from;

                this->animationGraph->instructions.push_back({[this, now = cur, nxt = Nodes[v], _edge = edge]()
                                                              { this->animationGraph->connectNodes(now, nxt, _edge, {1}); }});
                if (visited[v])
                    continue;
                visited[v] = 1;
                q.push(Nodes[v]);

                this->animationGraph->instructions.push_back({[this, node = Nodes[v]]()
                                                              { this->animationGraph->highlightCurrentNode(node, "normalFillColor", "newColor", {1}); }});
                waitAnimation();
            }

            lastVisit = cur->key;
        }

        this->animationGraph->instructions.push_back({[this, lastNode = Nodes[lastVisit]]()
                                                      {
                                                          this->animationGraph->highlightCurrentNode(lastNode, "normalFillColor", "reachColor", {1});
                                                      }});
        waitAnimation();
    };

    for (int i = 1; i <= numberNode; ++i) {
        if (visited[i]) continue;
        bfs(i);
    };

    endOperation();
    return;
}

void Graph::operation_MST(int startNode)
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
        codeHighlight->introText.setString("Count connected components");
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

    std::vector<bool> visited(numberNode + 2);

    // queue<int> q;   
    // q.push(Nodes[startNode]);
    this->animationGraph->instructions.push_back({[this, node = Nodes[startNode]]()
                                                      { this->animationGraph->highlightCurrentNode(node, "normalFillColor", "newColor", {1}); }});
    this->animationGraph->instructions.push_back({[this, node = Nodes[startNode]]()
                                                      { this->animationGraph->highlightCurrentNode(node, "newColor", "newColor", {1}); }});
    waitAnimation();   
    visited[startNode] = 1;

    int lastVisit = startNode;

    while (1) // break when no update
    {
        std::pair<int, GraphEdge*> miniEdge = {1e9, nullptr};

        for (auto edge : Edges)
        {
            int u = edge->from, v = edge->to;
            if ((visited[u] && visited[v]) || (!visited[u] && !visited[v])) continue;
            miniEdge = min(miniEdge, {edge->cost, edge});
        }
        if (miniEdge.second == nullptr) break; // no update

        GraphEdge *edge = miniEdge.second;
        int u = edge->from, v = edge->to;
        assert(visited[u] || visited[v]);
        if (visited[v]) std::swap(u, v);

        this->animationGraph->instructions.push_back({[this, node_u = Nodes[u], node_v = Nodes[v], _edge = edge]()
                                                      { this->animationGraph->connectNodes(node_u, node_v, _edge, {1}); },
                                                      [this, lastNode = Nodes[lastVisit]]()
                                                      { this->animationGraph->highlightCurrentNode(lastNode, "normalFillColor", "reachColor", {1}); }});
        waitAnimation();

        this->animationGraph->instructions.push_back({[this, node = Nodes[v]]()
                                                        { this->animationGraph->highlightCurrentNode(node, "newColor", "newColor", {1}); }});
        waitAnimation();

        visited[u] = visited[v] = 1;
        lastVisit = v;
    }

    this->animationGraph->instructions.push_back({[this, lastNode = Nodes[lastVisit]]()
                                                    {
                                                        this->animationGraph->highlightCurrentNode(lastNode, "normalFillColor", "reachColor", {1});
                                                    }});
    waitAnimation();

    endOperation();
}

void Graph::operation_dijkstra(int startNode)
{
}

void Graph::prepareNewInstruction()
{
    // std::cout << "Prepare new\n";
    this->animation->finishStep();
    bool trash = 0;
    this->animationGraph->last(trash, &this->stepText);
    this->animationGraph->newInstruction(Nodes, Edges);
    this->animationGraph->animationTime = 0.001; /* Do all instruction quickly first, then activate replay mode */
    this->codeHighlight->reset();
}

/* Update and Render */
void Graph::updateButtons()
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

void Graph::updateChildButtons()
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

void Graph::updateInputFields()
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

void Graph::updateSFMLEvents(const float &dt, sf::Event &event)
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
                //     this->inputWarning.setString("Sorry, the animationGraph is running...");
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

void Graph::update(const float &dt)
{
    this->window->setTitle("Graph");
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

void Graph::enable_replayButton()
{
    /* Show Replay button */
    this->buttons["Play"]->disabled = 1;
    this->buttons["Pause"]->disabled = 1;
    this->buttons["Replay"]->disabled = 0;
}

void Graph::renderButtons(sf::RenderTarget *target)
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

void Graph::renderNode(sf::RenderTarget *target)
{   
    for (GraphNode *node : this->Nodes)
    {
        if (node == nullptr) continue;
        node->render(target);
    }
}

void Graph::renderEdge(sf::RenderTarget *target)
{
    for (GraphEdge *edge : this->Edges)
    {
        edge->render(target);
    }
}

void Graph::renderAnimation()
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
        this->animationGraph->play(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "pause")
    {
        this->animationGraph->pause(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "prev")
    {
        this->animationGraph->prev(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "next")
    {
        this->animationGraph->next(this->doneAnimation, &this->stepText);
        if (this->doneAnimation && this->animationGraph->curIndex == (int)this->animationGraph->instructions.size())
        {
            enable_replayButton();
        }
        return;
    }

    if (this->runState == "first")
    {
        this->animationGraph->first(this->doneAnimation, &this->stepText);
        return;
    }

    if (this->runState == "last")
    {
        this->animationGraph->last(this->doneAnimation, &this->stepText);
        if (this->doneAnimation)
        {
            enable_replayButton();
        }
        return;
    }
}

void Graph::renderHighlightCode(sf::RenderTarget *target)
{
    codeHighlight->render(target);
}

void Graph::render(sf::RenderTarget *target)
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
    this->renderEdge(target);
}

void Graph::reset()
{   
    this->exist.resize(1005);
    exist.assign((int)exist.size(), 0);
    arrNode.resize(maxNode + 2);
    
    this->DeleteNodePointers();

    /* Init Tree */
    GraphNode* rubbish = new GraphNode(-1, -1, scale_x, scale_y, 0, &font, &Colors);
    rubbish->showNode = 0;
    Nodes.push_back(rubbish); // negative coordinate to not be shown

    this->numberNode = 0;

    delete (this->animation);

    this->codeHighlight->reset();
    this->animation = new AnimationGraph(&this->Colors, (float)(maxSpeed * speedGap) / currentSpeed, codeHighlight);
    this->animationGraph = dynamic_cast<AnimationGraph *>(this->animation);
    assert(animationGraph != nullptr);

    this->newStepTriggered = 0;
    this->doneAnimation = 1;
    this->choosingButton = "";
    this->choosingChildButton = "";
    inputWarning.setString("");
    inputGuide.setString("");
    exist.assign((int)exist.size(), 0);
    runState = "";
}

void Graph::waitAnimation()
{
    /* This function is called immediately after pushing new Animation */
    this->doneAnimation = 0;
    while (!this->doneAnimation)
    {
        this->animationGraph->play(this->doneAnimation, &this->stepText);
    }
    return;
}

void Graph::endOperation()
{
    this->animationGraph->animationTime = float(speedGap * maxSpeed) / currentSpeed;

    // At the beginning of each operator, we go through all animation immediately, then trigger replay mode
    button_replay();
    return;
}

void Graph::ReInitButtons()
{
    delete (this->buttons["Add"]);
    delete (this->buttons["Delete"]);
    delete (this->buttons["Update"]);
    delete (this->buttons["Search"]);
    delete (this->buttons["Quit"]);
    this->buttons.erase(buttons.find("Add"));
    this->buttons.erase(buttons.find("Delete"));
    this->buttons.erase(buttons.find("Update"));
    this->buttons.erase(buttons.find("Search"));
    this->buttons.erase(buttons.find("Quit"));

    this->buttons["BFS"] = new Button(
        insButtonX, insButtonY + 2 * insButtonDistanceY, scale_x, scale_y,
        &this->font, "BFS", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(240, 180, 10, 255),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(150, 150, 150, 255),
        1, insButtonSizeX, insButtonSizeY);

    this->buttons["MST"] = new Button(
        insButtonX, insButtonY + 3 * insButtonDistanceY, scale_x, scale_y,
        &this->font, "MST", characterSize,
        sf::Color(255, 255, 255, 255), sf::Color(240, 180, 10, 255), sf::Color(240, 180, 10, 255),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(150, 150, 150, 255),
        1, insButtonSizeX, insButtonSizeY);

    this->buttons["Dijkstra"] = new Button(
        insButtonX, insButtonY + 4 * insButtonDistanceY, scale_x, scale_y,
        &this->font, "Dijkstra", characterSize,
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