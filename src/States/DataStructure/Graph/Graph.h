#ifndef Graph_H
#define Graph_H

#pragma once

#include "DataStructure.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "AnimationGraph.h"

class Graph : public DataStructure
{
private:
    // Variables
    float start_x = 200, start_y = 200, end_x = 900, end_y = 500; 
    int maxNode = 31;
    int numberNode = 0;
    std::vector<std::vector<int>> adj_matrix; // adjacent matrix 

    float nodeDistanceX = 32.f;
    float nodeDistanceY = 70.f;

    GraphNode *root; // parent of real root, root->next[0] = real root
    // std::vector<GraphNode *> stack_root;
    
    AnimationGraph *animationGraph;
    std::vector<GraphNode *> Nodes;
    std::vector<GraphNode *> arrNode;
    std::vector<GraphEdge *> Edges;

    // Child Buttons
    float childButtonOriginX = 125.f;
    float childButtonOriginY = 545.f; // last is 375
    float childButtonWidth = 80.f;
    float childButtonHeight = 25.f;
    float childButtonCharacterSize = 16.f;
    float childButtonDistanceX = 5.f;
    float childButtonDistanceY = 5.f;

    // Input Fields
    float inputFieldOriginX = 125.f;
    float inputFieldOriginY = 603.f; // last is 433
    float inputFieldWidth = 80.f;
    float inputFieldHeight = 25.f;
    float inputFieldCharacterSize = 16.f;
    float inputFieldDistanceX = 5.f;
    float inputFieldDistanceY = 5.f;

    // Buttons
    void initTriggerFunction();
    void initChildButtons();
    void initInputFields();
    void initAnimation();
    void initHighlightCode();

    // Instruction Buttons
    void button_theme();
    void button_initialize();
    void button_bfs();
    void button_MST();
    void button_dijkstra();
    void button_quit();

    
    // Graph operations
    
    /// @brief Graph layout using Forced-base Algorithm
    /// @param iterations Number of iterations
    /// @param k repulsive constant
    /// @param c attractive constant
    /// @param l ideal spring length for edge
    void GraphLayout(int iterations = 5, float k = 1.0, float c = 0.001, float l = 30.f);
    void buildGraph();

    /// @brief Connected component
    void operation_bfs();

    /// @brief Find MST using Prim's Algorithm
    /// @param startNode start node
    void operation_MST(int startNode);

    /// @brief Find shortest path from start node to others
    /// @param startNode start node
    void operation_dijkstra(int startNode);

    void prepareNewInstruction();

public:
    Graph(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    ~Graph();

    // Reset
    void DeleteNodePointers();

    // Functions
    // Init

    // Update
    void updateButtons();
    void updateChildButtons();
    void updateInputFields();
    void updateSFMLEvents(const float &dt, sf::Event &event);
    void update(const float &dt);
    
    void enable_replayButton();
    void renderButtons(sf::RenderTarget *target = NULL);
    void renderNode(sf::RenderTarget *target);
    void renderEdge(sf::RenderTarget *target);
    void renderAnimation();
    void renderHighlightCode(sf::RenderTarget *target);
    void render(sf::RenderTarget *target = NULL);
    void reset();

    /// @brief Wait until animation done to process next step
    void waitAnimation();

    /// @brief Called right before ending a operation, to reset some variables
    void endOperation();

    void ReInitButtons();
};

#endif