#ifndef Trie_H
#define Trie_H

#pragma once

#include "DataStructure.h"
#include "TrieNode.h"
#include "AnimationTrie.h"

class Trie : public DataStructure
{
private:
    // Variables
    float start_x = 180, start_y = 110;
    int maxNode = 50;
    int numberNode = 0;
    int maxSizeInput = 8;

    float nodeDistanceX = 60.f;
    float nodeDistanceY = 80.f;

    std::string inputStr = ""; // for input string

    TrieNode *root; // parent of real root, root->next[0] = real root
    // std::vector<TrieNode *> stack_root;
    
    AnimationTrie *animationTrie;
    std::vector<TrieNode *> Nodes;

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
    void button_update();
    void button_search();
    void button_quit();

    
    // Trie operations
    void insertTrieNode(TrieNode *curNode, std::string newStr);
    void deleteTrieNode(TrieNode *root, std::string delStr);

    void operation_add(std::string newStr);
    void operation_delete(std::string delStr);
    void operation_search(std::string findStr);

    void prepareNewInstruction();

public:
    Trie(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    ~Trie();

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
};

#endif