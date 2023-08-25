#include "GraphEdge.h"

GraphEdge::GraphEdge(GraphNode* node1, GraphNode* node2, float _cost, sf::Font *_font, std::map<std::string, sf::Color> *Colors)
{
    this->cost = _cost;
    this->from = node1->key;
    this->to = node2->key;
    this->Colors = Colors;
    this->font = _font;   
    edgeFirst_img.loadFromFile("Resources/Images/edgeOrange.png");
    edgeSecond_img.loadFromFile("Resources/Images/edgeGreen.png");
    edgeFirst.setTexture(&edgeFirst_img);
    edgeSecond.setTexture(&edgeSecond_img);
    edgeFirst.setSize(sf::Vector2f(100.f, 40.f));
    edgeSecond.setSize(sf::Vector2f(100.f, 40.f));
    
    makeArrow(&node1->shape, &node2->shape, &edgeFirst);
    makeArrow(&node1->shape, &node2->shape, &edgeSecond);

    auto setTextPosition = [&]() {
        int x1 = node1->x_center;
        int y1 = node1->y_center;
        int x2 = node2->x_center;
        int y2 = node2->y_center;

        labelText.setPosition((x1 + x2) / 2, (y1 + y2) / 2);
        labelText.setString(std::to_string(cost));
        labelColor = Colors->at("labelColor");
        labelText.setCharacterSize(labelSize);
        labelText.setFont(*font);
        labelText.setFillColor(labelColor);
        // labelText.setStyle(sf::Text::Bold);
    };
    setTextPosition();

    reset();
}


GraphEdge::~GraphEdge()
{

}

void GraphEdge::render(sf::RenderTarget *target)
{
    if (this->showFirst) {
        target->draw(this->edgeFirst);
    }
    if (this->showSecond) {
        target->draw(this->edgeSecond);
    }

    if (this->showLabel)
        target->draw(this->labelText);
}

void GraphEdge::reset() {
    showFirst = 1, showSecond = 0;
    showLabel = 1;
}