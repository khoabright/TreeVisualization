#ifndef HEAPNODE_H
#define HEAPNODE_H

#pragma once

#include "SFML/Graphics.hpp"

#include <bits/stdc++.h>
#include <functional>

const int numChildHeap = 2;

struct HeapNode
{   
    HeapNode *next[numChildHeap];
    float array_start_x = 15, array_start_y = 75;
    float arrayDistanceX = 39.f, arrayDistanceY = 100.f; // array positions is set permanently 

    int key, heightHeap, depthHeap = 0; // depth compared to root
    int amountLR[numChildHeap] = {}; // amount of nodes visualized to the left/right (not include other side of root and root)
    int subTreeSize = 0; // number of Node in its subtree (including itself)
    int balanceFactor = 0;
    int idxArray = -1; // index in array

    float scale_x, scale_y, x, y, width, height; // height of the node
    float standard_width = 40.f, standard_height = 40.f; /* Dimension I used in 800x600 and radius = 40 */
    float x_center, y_center;
    float radius = 15.f;
    float side = 34.f; // side for array

    float labelTextSize = 18.f; // text for label
    float textSize = 13.f; // Text for key

    std::map<std::string, sf::Color> *Colors;
    std::vector<std::string> array_outlineColor;
    std::vector<std::string> array_fillColor;
    std::vector<std::string> array_label;
    std::vector<HeapNode*> array_next[numChildHeap];
    std::vector<int> array_key;
    std::vector<sf::Vector2f> array_pos;

    int idx_outlineColor = -1;
    int idx_fillColor = -1;
    int idx_label = -1;
    int idx_next[numChildHeap] = {-1, -1};
    int idx_key = -1;
    int idx_pos = -1;

    sf::CircleShape shape;
    sf::RectangleShape shapeArray; // shape for square in array
    sf::RectangleShape arrow[numChildHeap];
    sf::Texture arrow_img;

    sf::Text text, textArray, labelArray;
    sf::Font *font;

    //Label
    std::string labelString;
    sf::Text labelText; // label for heightHeap
    sf::Color labelColor; // Yellow orange

    bool showNode = 0;
    bool showArrow[numChildHeap] = {};
    bool showLabel = 0;
    bool showTextArray = 0; 

    HeapNode();
    HeapNode(float x, float y, float scale_x, float scale_y, int _key, int idx_array, sf::Font *_font, std::map<std::string, sf::Color>* Colors);

    void reset();

    //Next
    void updateNext(int next_index);
    void newNext(HeapNode* new_next, int next_index);
    void prevNext(int next_index);
    void nextNext(int next_index);

    //Key
    void updateKey();
    void newKey(int new_val);
    void prevKey();
    void nextKey();

    //Color
    void setNormalColor();
    void newColor(std::string fillColor, std::string outlineColor);
    void updateColor();
    void prevColor();
    void nextColor();

    //Text & Label
    void updateText();
    void newLabel(std::string new_label);
    void updateLabel();
    void prevLabel();
    void nextLabel();

    //Pos
    void updatePos();
    void newPos(sf::Vector2f new_pos);
    void prevPos();
    void nextPos();

    //Render
    void renderAnimation();
    void render(sf::RenderTarget *target);
};

void makeArrowHeap(sf::CircleShape *node1, sf::CircleShape *node2, sf::RectangleShape *targetArrow);
void RecalTreeAmountLeftRight(HeapNode *root, int direction = 1, bool isRoot = 1); // direction = -1/1 is calculating amountLeft/Right
void RecalTreePosition(HeapNode *root, float start_x, float start_y, float distance_x, float distance_y, int direction = 1); 
void ResetTree(HeapNode *root);

/* get position of node after correctly layout */
sf::Vector2f getPositionNode(HeapNode *root, HeapNode *node, float start_x, float start_y, float distance_x, float distance_y);
// void updateBalanceFactor(HeapNode *root);

// //Root
// void updateRoot(int idx_root, HeapNode* &root, std::vector<HeapNode*>& array_root);
// void newRoot(HeapNode* root, std::vector<HeapNode*>& array_root);
// void prevRoot(int &idx_root, HeapNode* &root, std::vector<HeapNode*>& array_root);
// void nextRoot(int &idx_root, HeapNode* &root, std::vector<HeapNode*>& array_root);

#endif