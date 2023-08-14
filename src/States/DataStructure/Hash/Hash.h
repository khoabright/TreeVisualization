#ifndef Hash_H
#define Hash_H

#pragma once

#include "DataStructure.h"
#include "HashNode.h"
#include "AnimationHash.h"

class Hash : public DataStructure
{
private:
    // Variables
    float start_x = 100, start_y = 110;
    int maxNode = 100, maxM = 20;
    int numberNode = 0;
    int M_hash;

    float nodeDistanceX = 55.f;
    float nodeDistanceY = 70.f;

    HashNode *root; // parent of real root, root->next[0] = real root
    // std::vector<HashNode *> stack_root;
    
    AnimationHash *animationHash;
    std::vector<std::vector<HashNode *>> Nodes;

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
    void button_search();
    void button_quit();

    
    // Hash operations
    void insertHashNode(int nodeValue);
    void deleteHashNode(int nodeValue);

    /// @brief Init Hash table
    /// @param M Modulo 
    void initHash(int M);
    void operation_add(int nodeValue);
    void operation_delete(int nodeValue);
    void operation_search(int nodeValue);

    void prepareNewInstruction();

public:
    Hash(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    ~Hash();

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