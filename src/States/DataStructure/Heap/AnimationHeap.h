#ifndef AnimationHeap_H
#define AnimationHeap_H

#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "HeapNode.h"
#include "CodeHighlight.h"
#include "Animation.h"

class AnimationHeap : public Animation
{
private:
public:
    AnimationHeap(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight);
    ~AnimationHeap();

    // Initialize

    // Animation

    void addCodeLines(std::vector<int> codeLines); //do nothing but adding codeLines

    // void changeRoot(int &idx_root, std::vector<HeapNode *> array_root, HeapNode* new_root, HeapNode* root, std::vector<int> codeLines);

    void showNode(HeapNode *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines);
    void hideNode(HeapNode *targetNode, HeapNode *parentNode, int next_index, int &numberNode, std::vector<int> codeLines);
    
    void changeNodeLabel(HeapNode *targetNode, std::string targetLabel, std::vector<int> codeLines);
    void changeNodeValue(HeapNode *targetNode, int newValue, std::vector<int> codeLines);

    void connectNodes(HeapNode *targetNode, HeapNode *nextNode, int next_index, std::vector<int> codeLines);

    /* Use color as string because we want to modified later */
    void highlightCurrentNode(HeapNode *targetNode, std::string targetColor, std::vector<int> codeLines);

    void moveNode(HeapNode *targetNode, float x1, float y1);

    void Relayout(bool emptyList, HeapNode *root, float start_x, float start_y, float distance_x, float distance_y, std::vector<int> codeLines);

    //Reset
    void updateNodePosition(HeapNode *root, std::vector<HeapNode*> arrNode, int numberNode, float start_x, float start_y, float distance_x, float distance_y);
    void newInstruction(HeapNode *root, std::vector<HeapNode*> arrNode, int numberNode, float start_x, float start_y, float distance_x, float distance_y);
};

#endif