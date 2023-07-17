#ifndef AnimationAVL_H
#define AnimationAVL_H

#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "AVLNode.h"
#include "CodeHighlight.h"
#include "Animation.h"

class AnimationAVL : public Animation
{
private:
public:
    AnimationAVL(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight);
    ~AnimationAVL();

    // Initialize

    // Animation

    void addCodeLines(std::vector<int> codeLines); //do nothing but adding codeLines

    void changeHead(AVLNode *&head, AVLNode *old_head, AVLNode *targetNode, std::vector<int> codeLines); /* current lines of code for highlighting */
    void changeTail(AVLNode *&tail, AVLNode *old_tail, AVLNode *targetNode, std::vector<int> codeLines);

    void showNode(AVLNode *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines);
    void hideNode(AVLNode *targetNode, int &numberNode, std::vector<int> codeLines);
    
    void changeNodeLabel(AVLNode *targetNode, std::string targetLabel, std::vector<int> codeLines);
    void changeNodeValue(AVLNode *targetNode, int newValue, std::vector<int> codeLines);

    void connectNodes(AVLNode *targetNode, AVLNode *nextNode, std::vector<int> codeLines);

    /* Use color as string because we want to modified later */
    void highlightCurrentNode(AVLNode *targetNode, std::string targetLabel, std::string targetColor, std::vector<int> codeLines);
    void highlightPassedNode(AVLNode *targetNode, std::string passedLabel, std::string currentLabel, std::string passedColor, std::string currentColor, std::vector<int> codeLines);

    void moveNode(AVLNode *targetNode, float x1, float y1);
    void makeArrow(sf::CircleShape *node1, sf::CircleShape *node2, sf::RectangleShape *targetArrow);

    void Relayout(bool emptyList, AVLNode *head, AVLNode *tail, float start_x, float start_y, float distance, std::vector<int> codeLines);

    //Reset
    void updateNodePosition(AVLNode *head, AVLNode *tail, float start_x, float start_y, float distance);
    void newInstruction(AVLNode *head, AVLNode *tail, float start_x, float start_y, float distance);
};

#endif