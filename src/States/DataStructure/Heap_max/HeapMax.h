#ifndef HeapMax_H
#define HeapMax_H

#pragma once

#include "DataStructure.h"
#include "HeapMaxNode.h"
#include "AnimationHeapMax.h"

class HeapMax : public DataStructure
{
private:
    // Variables
    float start_x = 600, start_y = 150;
    int maxNode = 31;
    int numberNode = 0;

    float nodeDistanceX = 32.f;
    float nodeDistanceY = 70.f;

    HeapMaxNode *root; // parent of real root, root->next[0] = real root
    // std::vector<HeapMaxNode *> stack_root;
    
    AnimationHeapMax *animationHeapMax;
    std::vector<HeapMaxNode *> Nodes;
    std::vector<HeapMaxNode *> arrNode;

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

    
    // HeapMax operations


    /// @brief Build whole tree initially
    /// @param cur current Node 
    void buildHeapMaxTree(HeapMaxNode *cur);

    HeapMaxNode *newHeapMaxNode(int key, HeapMaxNode *parentNode);
    void insertHeapMaxNode(int key);

    HeapMaxNode *deleteHeapMaxNode();

    void operation_add(int nodeValue);
    void operation_delete();
    void operation_top();
    void operation_size();

    void prepareNewInstruction();

public:
    HeapMax(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    ~HeapMax();

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