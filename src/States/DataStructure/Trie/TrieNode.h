#ifndef TrieNODE_H
#define TrieNODE_H

#pragma once

#include "SFML/Graphics.hpp"

#include <bits/stdc++.h>
#include <functional>

const int numChild = 26;

struct TrieNode
{   
    TrieNode *next[numChild] = {};

    int key, heightTrie, depthTrie = 0; // depth compared to root
    int amountLR[numChild] = {}; // amount of nodes visualized to the left/right (not include other side of root and root)
    int subTreeSize = 0; // number of Node in its subtree (including itself)
    int balanceFactor = 0;
    bool isEnd = 0;
    
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
    std::vector<TrieNode*> array_next[numChild];
    std::vector<int> array_key;
    std::vector<sf::Vector2f> array_pos;

    int idx_outlineColor = -1;
    int idx_fillColor = -1;
    int idx_label = -1;
    int idx_next[numChild];
    int idx_key = -1;
    int idx_pos = -1;

    sf::CircleShape shape;
    sf::RectangleShape arrow[numChild];
    sf::Texture arrow_img;

    sf::Text text;
    sf::Font *font;

    //Label
    std::string labelString;
    sf::Text labelText; // label for heightTrie
    sf::Color labelColor; // Yellow orange

    bool showNode = 0;
    bool showArrow[numChild] = {};
    bool showLabel = 1;

    TrieNode();
    TrieNode(float x, float y, float scale_x, float scale_y, int _val, sf::Font *_font, std::map<std::string, sf::Color>* Colors);

    void reset();

    /// @brief check if node is a leaf (has no child)
    /// @return true/false
    bool isLeaf();

    //Next
    void updateNext(int next_index);
    void newNext(TrieNode* new_next, int next_index);
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

void makeArrow(sf::CircleShape *node1, sf::CircleShape *node2, sf::RectangleShape *targetArrow);
void RecalTreeAmountLeftRight(TrieNode *root, bool isRoot = 1); // direction = -1/1 is calculating amountLeft/Right
void RecalTreePosition(TrieNode *root, float start_x, float start_y, float distance_x, float distance_y); 
void ResetTree(TrieNode *root);

/* get position of node after correctly layout */
sf::Vector2f getPositionNode(TrieNode *root, TrieNode *node, float start_x, float start_y, float distance_x, float distance_y);
// void updateBalanceFactor(TrieNode *root);

// //Root
// void updateRoot(int idx_root, TrieNode* &root, std::vector<TrieNode*>& array_root);
// void newRoot(TrieNode* root, std::vector<TrieNode*>& array_root);
// void prevRoot(int &idx_root, TrieNode* &root, std::vector<TrieNode*>& array_root);
// void nextRoot(int &idx_root, TrieNode* &root, std::vector<TrieNode*>& array_root);

#endif