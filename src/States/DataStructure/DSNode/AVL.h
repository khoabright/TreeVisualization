#ifndef AVL_H
#define AVL_H

#pragma once

#include "DataStructure.h"
#include "AVLNode.h"

class AVL : public DataStructure
{
private:
    // Variables
    float start_x = 580, start_y = 110;
    int maxNode = 100;
    int numberNode = 0;

    float nodeDistanceX = 50.f;
    float nodeDistanceY = 70.f;

    AVLNode *root; // parent of real root, root->next[0] = real root
    // std::vector<AVLNode *> stack_root;
    
    AnimationAVL *animationAVL;
    std::vector<AVLNode *> Nodes;

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

    
    // AVL operations
    int heightAVL(AVLNode *N);
    AVLNode *newAVLNode(int key, AVLNode *parentNode);
    AVLNode *rightRotate(AVLNode *y);
    AVLNode *leftRotate(AVLNode *x);
    int getBalanceFactor(AVLNode *N);
    AVLNode *insertAVLNode(AVLNode *curNode, AVLNode *parentNode, int key);
    AVLNode *AVLNodeWithMimumValue(AVLNode *AVLNode);
    AVLNode *deleteAVLNode(AVLNode *root, AVLNode *parentNode, int key);

    // Add
    void operation_add(int nodeValue);

    // Delete
    void operation_delete(int nodeValue);

    void prepareNewInstruction();

public:
    AVL(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    ~AVL();

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