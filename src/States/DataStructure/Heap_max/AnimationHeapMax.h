#ifndef AnimationHeapMax_H
#define AnimationHeapMax_H

#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "HeapMaxNode.h"
#include "CodeHighlight.h"
#include "Animation.h"

class AnimationHeapMax : public Animation
{
private:
public:
    AnimationHeapMax(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight);
    ~AnimationHeapMax();

    // Initialize

    // Animation

    void addCodeLines(std::vector<int> codeLines); //do nothing but adding codeLines

    // void changeRoot(int &idx_root, std::vector<HeapMaxNode *> array_root, HeapMaxNode* new_root, HeapMaxNode* root, std::vector<int> codeLines);

    void showNode(HeapMaxNode *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines);
    void hideNode(HeapMaxNode *targetNode, HeapMaxNode *parentNode, int next_index, int &numberNode, std::vector<int> codeLines);
    
    void changeNodeLabel(HeapMaxNode *targetNode, std::string targetLabel, std::vector<int> codeLines);
    void changeNodeValue(HeapMaxNode *targetNode, int newValue, std::vector<int> codeLines);

    void connectNodes(HeapMaxNode *targetNode, HeapMaxNode *nextNode, int next_index, std::vector<int> codeLines);

    /* Use color as string because we want to modified later */
    void highlightCurrentNode(HeapMaxNode *targetNode, std::string targetColor, std::vector<int> codeLines);

    void moveNode(HeapMaxNode *targetNode, float x1, float y1);

    void Relayout(bool emptyList, HeapMaxNode *root, float start_x, float start_y, float distance_x, float distance_y, std::vector<int> codeLines);

    //Reset
    void updateNodePosition(HeapMaxNode *root, std::vector<HeapMaxNode*> arrNode, int numberNode, float start_x, float start_y, float distance_x, float distance_y);
    void newInstruction(HeapMaxNode *root, std::vector<HeapMaxNode*> arrNode, int numberNode, float start_x, float start_y, float distance_x, float distance_y);
};

#endif