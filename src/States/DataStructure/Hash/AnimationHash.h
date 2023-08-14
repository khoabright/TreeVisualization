#ifndef AnimationHash_H
#define AnimationHash_H

#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "HashNode.h"
#include "CodeHighlight.h"
#include "Animation.h"

class AnimationHash : public Animation
{
private:
public:
    AnimationHash(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight);
    ~AnimationHash();

    // Initialize

    // Animation

    void addCodeLines(std::vector<int> codeLines); //do nothing but adding codeLines

    void changeHead(HashNode *&head, HashNode *old_head, HashNode *targetNode, std::vector<int> codeLines); /* current lines of code for highlighting */
    void changeTail(HashNode *&tail, HashNode *old_tail, HashNode *targetNode, std::vector<int> codeLines);

    void showNode(HashNode *targetNode, std::string targetLabel, std::vector<int> codeLines);
    void hideNode(HashNode *targetNode, std::vector<int> codeLines);
    
    void changeNodeLabel(HashNode *targetNode, std::string targetLabel, std::vector<int> codeLines);
    void changeNodeValue(HashNode *targetNode, int newValue, std::vector<int> codeLines);

    void connectNodes(HashNode *targetNode, HashNode *nextNode, std::vector<int> codeLines);

    /* Use color as string because we want to modified later */
    void highlightCurrentNode(HashNode *targetNode, std::string targetLabel, std::string targetColor, std::vector<int> codeLines);
    void highlightPassedNode(HashNode *targetNode, std::string passedLabel, std::string currentLabel, std::string passedColor, std::string currentColor, std::vector<int> codeLines);

    void moveNode(HashNode *targetNode, float x1, float y1);
    void makeArrow(sf::CircleShape *node1, sf::CircleShape *node2, sf::RectangleShape *targetArrow);

    void Relayout(bool emptyList, HashNode *head, float start_x, float start_y, float distance_x, float distance_y, std::vector<int> codeLines);

    //Reset
    void updateNodePosition(HashNode *head, HashNode *tail, float start_x, float start_y, float distance);
    void newInstruction(std::vector<std::vector<HashNode *>> &Nodes, float start_x, float start_y, float distance_x, float distance_y);
};

#endif