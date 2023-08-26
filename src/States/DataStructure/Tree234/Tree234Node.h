#ifndef Tree234NODE_H
#define Tree234NODE_H

#pragma once

#include "SFML/Graphics.hpp"

#include <bits/stdc++.h>
#include <functional>

const int numChild234 = 4;

struct Tree234Node
{   
    Tree234Node *next[numChild234];
    float arrayDistanceX = 39.f, arrayDistanceY = 100.f; // array positions is set permanently 

    int heightTree234, depthTree234 = 0; // depth compared to root
    std::vector<int> key;
    float layout_width;
    int amountLR[numChild234] = {}; // amount of nodes visualized to the left/right (not include other side of root and root)
    int subTreeSize = 0; // number of Node in its subtree (including itself)

    float scale_x, scale_y, x, y, width, height; // height of the node
    float standard_width = 40.f, standard_height = 40.f; /* Dimension I used in 800x600 and radius = 40 */
    float x_center, y_center;
    float radius = 15.f;
    float side = 34.f; // side for array

    float labelTextSize = 18.f; // text for label
    float textSize = 20.f; // Text for key

    std::map<std::string, sf::Color> *Colors;
    std::vector<std::string> array_outlineColor;
    std::vector<std::string> array_fillColor;
    std::vector<std::string> array_label;
    std::vector<Tree234Node*> array_next[numChild234];
    std::vector<std::vector<int>> array_key;
    std::vector<sf::Vector2f> array_pos;

    int idx_outlineColor = -1;
    int idx_fillColor = -1;
    int idx_label = -1;
    int idx_next[numChild234] = {-1, -1, -1, -1};
    int idx_key = -1;
    int idx_pos = -1;

    sf::RectangleShape shape;
    sf::RectangleShape arrow[numChild234];
    sf::Texture arrow_img;

    sf::Text labelArray;
    sf::Text text[numChild234];
    sf::Font *font;

    //Label
    std::string labelString;
    sf::Text labelText; // label for heightTree234
    sf::Color labelColor; // Yellow orange

    bool showNode = 0;
    bool showArrow[numChild234] = {};
    bool showLabel = 0;

    Tree234Node();
    Tree234Node(float x, float y, float scale_x, float scale_y, std::vector<int> _key, sf::Font *_font, std::map<std::string, sf::Color>* Colors);

    void reset();

    void updateShape();

    //Next
    void updateNext(int next_index);
    void newNext(Tree234Node* new_next, int next_index);
    void prevNext(int next_index);
    void nextNext(int next_index);

    //Key
    void updateKey();
    void newKey(std::vector<int> new_val);
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
    void renderArrow(sf::RenderTarget *target); // seperate function to call first, making arrow be shaded by node
    void renderNode(sf::RenderTarget *target);
};

void makeArrow234(sf::RectangleShape *node1, sf::RectangleShape *node2, sf::RectangleShape *targetArrow);
void RecalTreeAmountLeftRight(Tree234Node *root, int direction = 1, bool isRoot = 1); // direction = -1/1 is calculating amountLeft/Right
void RecalTreePosition(Tree234Node *root, float &start_x, float start_y, float distance_x, float distance_y, bool isRoot = 1); 
void ResetTree(Tree234Node *root);

/* get position of node after correctly layout */
sf::Vector2f getPositionNode(Tree234Node *root, Tree234Node *node, float start_x, float start_y, float distance_x, float distance_y);
// void updateBalanceFactor(Tree234Node *root);

// //Root
// void updateRoot(int idx_root, Tree234Node* &root, std::vector<Tree234Node*>& array_root);
// void newRoot(Tree234Node* root, std::vector<Tree234Node*>& array_root);
// void prevRoot(int &idx_root, Tree234Node* &root, std::vector<Tree234Node*>& array_root);
// void nextRoot(int &idx_root, Tree234Node* &root, std::vector<Tree234Node*>& array_root);

#endif