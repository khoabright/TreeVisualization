#ifndef AnimationTree234_H
#define AnimationTree234_H

#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Tree234Node.h"
#include "CodeHighlight.h"
#include "Animation.h"

class AnimationTree234 : public Animation
{
private:
public:
    AnimationTree234(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight);
    ~AnimationTree234();

    // Initialize

    // Animation

    void addCodeLines(std::vector<int> codeLines); //do nothing but adding codeLines

    // void changeRoot(int &idx_root, std::vector<Tree234Node *> array_root, Tree234Node* new_root, Tree234Node* root, std::vector<int> codeLines);

    void showNode(Tree234Node *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines);
    void hideNode(Tree234Node *targetNode, Tree234Node *parentNode, int next_index, int &numberNode, std::vector<int> codeLines);
    
    void changeNodeLabel(Tree234Node *targetNode, std::string targetLabel, std::vector<int> codeLines);
    void changeNodeValue(Tree234Node *targetNode, std::vector<int> newValue, std::vector<int> codeLines);

    void connectNodes(Tree234Node *targetNode, Tree234Node *nextNode, int next_index, std::vector<int> codeLines);

    /* Use color as string because we want to modified later */
    void highlightCurrentNode(Tree234Node *targetNode, std::string fillColor, std::string outlineColor, std::vector<int> codeLines);

    void moveNode(Tree234Node *targetNode, float x1, float y1);

    void Relayout(bool emptyList, Tree234Node *root, float start_x, float start_y, float distance_x, float distance_y, std::vector<int> codeLines);

    //Reset
    void updateNodePosition(Tree234Node *root, int numberNode, float start_x, float start_y, float distance_x, float distance_y);
    void newInstruction(Tree234Node *root, int numberNode, float start_x, float start_y, float distance_x, float distance_y);
};

#endif