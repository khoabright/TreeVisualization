#ifndef AVLNODE_H
#define AVLNODE_H

#pragma once

#include "SFML/Graphics.hpp"

#include <bits/stdc++.h>

const int numChild = 2;

struct AVLNode
{   
    AVLNode *next[numChild];

    int key, heightAVL;
    float scale_x, scale_y, x, y, width, height;
    float standard_width = 40.f, standard_height = 40.f; /* Dimension I used in 800x600 and radius = 40 */
    float x_center, y_center;
    float radius = 20.f;

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
    sf::Text labelText;
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

#endif