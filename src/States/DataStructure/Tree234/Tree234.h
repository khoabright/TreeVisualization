#ifndef Tree234_H
#define Tree234_H

#pragma once

#include "DataStructure.h"
#include "Tree234Node.h"
#include "AnimationTree234.h"

class Tree234 : public DataStructure
{
private:
    // Variables
    float start_x = 200, start_y = 150;
    int maxNode = 31;
    int numberNode = 0;

    float nodeDistanceX = 20.f;
    float nodeDistanceY = 70.f;

    Tree234Node *root; // parent of real root, root->next[0] = real root
    // std::vector<Tree234Node *> stack_root;
    
    AnimationTree234 *animationTree234;
    std::vector<Tree234Node *> Nodes;
    std::vector<Tree234Node *> arrNode;

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
    void button_add();
    void button_delete();
    void button_top();
    void button_size();
    void button_quit();

    
    // Tree234 operations


    /// @brief Build whole tree initially
    /// @param cur current Node 
    void buildTree234Tree(Tree234Node *cur);

    Tree234Node *newTree234Node(int key, Tree234Node *parentNode);
    void insertTree234Node(int key, Tree234Node *curNode, Tree234Node *parentNode, bool isRecursing = 0);

    Tree234Node *deleteTree234Node();

    void operation_add(int nodeValue);
    void operation_delete();
    void operation_top();
    void operation_size();

    void prepareNewInstruction();

public:
    Tree234(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    ~Tree234();

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