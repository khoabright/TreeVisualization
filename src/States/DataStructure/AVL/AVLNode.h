#ifndef AVLNODE_H
#define AVLNODE_H

#pragma once

#include "SFML/Graphics.hpp"

#include <bits/stdc++.h>
#include <functional>

const int numChild = 2;

struct AVLNode
{   
    AVLNode *next[numChild];

    int key, heightAVL, depthAVL = 0; // depth compared to root
    int amountLR[numChild] = {}; // amount of nodes visualized to the left/right (not include other side of root and root)
    int subTreeSize = 0; // number of Node in its subtree (including itself)
    int balanceFactor = 0;

    float scale_x, scale_y, x, y, width, height; // height of the node
    float standard_width = 40.f, standard_height = 40.f; /* Dimension I used in 800x600 and radius = 40 */
    float x_center, y_center;
    float radius = 15.f;
    float labelTextSize = 18.f; // text for label
    float textSize = 13.f; // Text for key

    std::map<std::string, sf::Color> *Colors;
    std::vector<std::string> array_outlineColor;
    std::vector<std::string> array_fillColor;
    std::vector<std::string> array_label;
    std::vector<AVLNode*> array_next[numChild];
    std::vector<int> array_key;
    std::vector<sf::Vector2f> array_pos;

    int idx_outlineColor = -1;
    int idx_fillColor = -1;
    int idx_label = -1;
    int idx_next[numChild] = {-1, -1};
    int idx_key = -1;
    int idx_pos = -1;

    sf::CircleShape shape;
    sf::RectangleShape arrow[numChild];
    sf::Texture arrow_img;

    sf::Text text;
    sf::Font *font;

    //Label
    std::string labelString;
    sf::Text labelText; // label for heightAVL
    sf::Color labelColor; // Yellow orange

    bool showNode = 0;
    bool showArrow[numChild] = {};
    bool showLabel = 1;

    AVLNode();
    AVLNode(float x, float y, float scale_x, float scale_y, int _val, sf::Font *_font, std::map<std::string, sf::Color>* Colors);

    void reset();

    //Next
    void updateNext(int next_index);
    void newNext(AVLNode* new_next, int next_index);
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

void makeArrowAVL(sf::CircleShape *node1, sf::CircleShape *node2, sf::RectangleShape *targetArrow);
void RecalTreeAmountLeftRight(AVLNode *root, int direction = 1, bool isRoot = 1); // direction = -1/1 is calculating amountLeft/Right
void RecalTreePosition(AVLNode *root, float start_x, float start_y, float distance_x, float distance_y, int direction = 1); 
void ResetTree(AVLNode *root);

/* get position of node after correctly layout */
sf::Vector2f getPositionNode(AVLNode *root, AVLNode *node, float start_x, float start_y, float distance_x, float distance_y);
// void updateBalanceFactor(AVLNode *root);

// //Root
// void updateRoot(int idx_root, AVLNode* &root, std::vector<AVLNode*>& array_root);
// void newRoot(AVLNode* root, std::vector<AVLNode*>& array_root);
// void prevRoot(int &idx_root, AVLNode* &root, std::vector<AVLNode*>& array_root);
// void nextRoot(int &idx_root, AVLNode* &root, std::vector<AVLNode*>& array_root);

#endif