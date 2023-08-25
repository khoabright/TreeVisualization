#ifndef AnimationGraph_H
#define AnimationGraph_H

#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "GraphNode.h"
#include "GraphEdge.h"
#include "CodeHighlight.h"
#include "Animation.h"

class AnimationGraph : public Animation
{
private:
public:
    AnimationGraph(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight);
    ~AnimationGraph();

    // Initialize

    // Animation

    void addCodeLines(std::vector<int> codeLines); //do nothing but adding codeLines

    // void changeRoot(int &idx_root, std::vector<GraphNode *> array_root, GraphNode* new_root, GraphNode* root, std::vector<int> codeLines);

    void showNode(GraphNode *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines);
    void hideNode(GraphNode *targetNode, GraphNode *parentNode, int next_index, int &numberNode, std::vector<int> codeLines);
    
    void changeNodeLabel(GraphNode *targetNode, std::string targetLabel, std::vector<int> codeLines);
    void changeNodeValue(GraphNode *targetNode, int newValue, std::vector<int> codeLines);

    void connectNodes(GraphNode *targetNode, GraphNode *nextNode, GraphEdge *edge, std::vector<int> codeLines);

    /* Use color as string because we want to modified later */
    void highlightCurrentNode(GraphNode *targetNode, std::string fillColor, std::string outlineColor, std::vector<int> codeLines);

    void moveNode(GraphNode *targetNode, float x1, float y1);

    //Reset
    void newInstruction(std::vector<GraphNode *> Nodes, std::vector<GraphEdge *> Edges);
};

#endif