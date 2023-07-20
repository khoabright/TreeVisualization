#ifndef AVL_H
#define AVL_H

#pragma once

#include "DataStructure.h"
#include "AVLNode.h"

class AVL : public DataStructure
{
private:
    // Variables
    float start_x = 90, start_y = 110;
    int maxNode = 12;
    int numberNode = 0;

    float nodeDistanceX = 100.f;
    float nodeDistanceY = 100.f;

    AVLNode *root;
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
    void button_search();
    void button_quit();

    
    // AVL operations
    int heightAVL(AVLNode *N);
    AVLNode *newAVLNode(int key);
    AVLNode *rightRotate(AVLNode *y);
    AVLNode *leftRotate(AVLNode *x);
    int getBalanceFactor(AVLNode *N);
    AVLNode *insertAVLNode(AVLNode *AVLNode, int key);
    AVLNode *AVLNodeWithMimumValue(AVLNode *AVLNode);
    AVLNode *deleteAVLNode(AVLNode *root, int key);

    // Add
    void operation_add(int nodeValue);

    // Delete
    void deleteMiddle(int index);

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
    void renderButtons(sf::RenderTarget *target = NULL);
    void renderNode(sf::RenderTarget *target);
    void renderAnimation();
    void renderHighlightCode(sf::RenderTarget *target);
    void render(sf::RenderTarget *target = NULL);
    void reset();
};

#endif