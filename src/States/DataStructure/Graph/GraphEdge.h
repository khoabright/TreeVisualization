#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#pragma once

#include "SFML/Graphics.hpp"
#include "GraphNode.h"
#include <bits/stdc++.h>

struct GraphEdge
{   
    GraphEdge(GraphNode* node1, GraphNode* node2, float _cost, sf::Font *_font, std::map<std::string, sf::Color> *Colors);
    ~GraphEdge();

    sf::RectangleShape edgeFirst, edgeSecond;
    sf::Texture edgeFirst_img, edgeSecond_img;

    sf::Font *font;
    std::map<std::string, sf::Color> *Colors;

    int from, to, cost;

    //Label
    sf::Text labelText; // cost
    sf::Color labelColor;
    float labelSize = 18.f;

    bool showFirst = 1, showSecond = 0;
    bool showLabel = 1;

    void render(sf::RenderTarget *target);
    void reset();
};

#endif