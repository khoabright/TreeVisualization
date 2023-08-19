#ifndef AnimationTrie_H
#define AnimationTrie_H

#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "TrieNode.h"
#include "CodeHighlight.h"
#include "Animation.h"

class AnimationTrie : public Animation
{
private:
public:
    AnimationTrie(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight);
    ~AnimationTrie();

    // Initialize

    // Animation

    void addCodeLines(std::vector<int> codeLines); //do nothing but adding codeLines

    // void changeRoot(int &idx_root, std::vector<TrieNode *> array_root, TrieNode* new_root, TrieNode* root, std::vector<int> codeLines);

    void showNode(TrieNode *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines);
    void hideNode(TrieNode *targetNode, int &numberNode, std::vector<int> codeLines);
    
    void changeNodeLabel(TrieNode *targetNode, std::string targetLabel, std::vector<int> codeLines);
    void changeNodeValue(TrieNode *targetNode, int newValue, std::vector<int> codeLines);

    void connectNodes(TrieNode *targetNode, TrieNode *nextNode, int next_index, std::vector<int> codeLines);

    /* Use color as string because we want to modified later */
    void highlightCurrentNode(TrieNode *targetNode, std::string targetColor, std::vector<int> codeLines);

    void moveNode(TrieNode *targetNode, float x1, float y1);

    void Relayout(bool emptyList, TrieNode *root, float start_x, float start_y, float distance_x, float distance_y, std::vector<int> codeLines);

    //Reset
    void updateNodePosition(TrieNode *root, float start_x, float start_y, float distance_x, float distance_y);
    void newInstruction(TrieNode *root, float start_x, float start_y, float distance_x, float distance_y);
};

#endif