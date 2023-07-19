#include "AVLNode.h"

AVLNode::AVLNode()
{
}

AVLNode::AVLNode(float x, float y, float scale_x, float scale_y, int _key, sf::Font *_font, std::map<std::string, sf::Color> *Colors)
{
    this->Colors = Colors;
    /* parameters are already scaled */

    /* just scale predeclared sizes */
    auto scaleSize = [&]()
    {
        this->radius *= scale_x;
        this->standard_width *= scale_x;
        this->standard_height *= scale_y;
    };

    scaleSize();

    //Variables
    
    for (int i = 0; i < numChild; ++i) {
        newNext(nullptr, i);
        nextNext(i);
    }

    newKey(_key);
    nextKey();

    this->font = _font;
    this->scale_x = scale_x;
    this->scale_y = scale_y;
    this->x = x;
    this->y = y;
    this->x_center = x + this->radius;
    this->y_center = y + this->radius;
    newPos(sf::Vector2f(x, y));
    nextPos();

    //Shape
    shape.setRadius(this->radius);
    this->width = shape.getGlobalBounds().width;
    this->height = shape.getGlobalBounds().height;

    shape.setPosition(x, y);
    shape.setOutlineThickness(3);


    //Color
    this->setNormalColor();
    newColor("normalFillColor", "normalOutlineColor");
    nextColor();

    //Arrow
    arrow_img.loadFromFile("Resources/Images/rightArrow.png");

    for (int i = 0; i < numChild; ++i) {
        arrow[i].setTexture(&arrow_img);
        arrow[i].setSize(sf::Vector2f(100.f, 40.f));
    }

    //Text
    text.setFont(*font);
    text.setCharacterSize(25 * scale_x * scale_y);
    text.setFillColor(Colors->at("characterColor"));
    
    //Label
    labelColor = Colors->at("labelColor");
    labelText.setFont(*font);
    labelText.setCharacterSize(20 * scale_x * scale_y);
    labelText.setFillColor(this->labelColor);
    labelText.setStyle(sf::Text::Bold);
    newLabel("");
    nextLabel();

    this->updateText();
}

void AVLNode::reset()
{   
    this->x_center = this->x + this->radius;
    this->y_center = this->y + this->radius;

    array_fillColor.clear();
    array_outlineColor.clear();
    array_label.clear();
    for (int i = 0; i < numChild; ++i) array_next[i].clear(); 
    array_key.clear();
    array_pos.clear();

    idx_fillColor = -1;
    idx_outlineColor = -1;
    idx_label = -1;
    for (int i = 0; i < numChild; ++i) idx_next[i] = -1;
    idx_key = -1;
    idx_pos = -1;

    this->setNormalColor();

    newColor("normalFillColor", "normalOutlineColor");
    nextColor();

    newLabel(this->labelString);
    nextLabel();

    for (int i = 0; i < numChild; ++i) {
        newNext(this->next[i], i);
        nextNext(i);
    }

    newKey(this->key);
    nextKey();

    newPos(sf::Vector2f(this->x, this->y));
    nextPos();
}

/* Update along time */

//Next
void AVLNode::updateNext(int next_index)
{
    this->next[next_index] = array_next[next_index][idx_next[next_index]];  /* next_index is index of current childNode, idx_next is idx of array_next */
}

void AVLNode::newNext(AVLNode *new_next, int next_index)
{
    if (this->idx_next[next_index] == (int)this->array_next[next_index].size() - 1) {
        this->array_next[next_index].push_back(new_next);
    }
}

void AVLNode::prevNext(int next_index)
{
    this->idx_next[next_index]--;
    this->updateNext(next_index);
}

void AVLNode::nextNext(int next_index)
{
    this->idx_next[next_index]++;
    this->updateNext(next_index);
}

//key
void AVLNode::updateKey()
{
    this->key = array_key[idx_key];
}

void AVLNode::newKey(int new_key)
{
    if (this->idx_key == (int)this->array_key.size() - 1) {
        this->array_key.push_back(new_key);
    }
}

void AVLNode::prevKey()
{   
    this->idx_key--;
    this->updateKey();
}

void AVLNode::nextKey()
{
    this->idx_key++;
    this->updateKey();
}


//Color
void AVLNode::setNormalColor()
{
    this->shape.setOutlineColor(this->Colors->at("normalOutlineColor"));
    this->shape.setFillColor(this->Colors->at("normalFillColor"));
}

void AVLNode::newColor(std::string fillColor, std::string outlineColor)
{
    assert(this->idx_fillColor == this->idx_outlineColor);
    if (this->idx_fillColor == (int)this->array_fillColor.size() - 1) {
        this->array_fillColor.push_back(fillColor);
        this->array_outlineColor.push_back(outlineColor);
    }
}

void AVLNode::updateColor()
{
    this->shape.setFillColor(Colors->at(array_fillColor[idx_fillColor]));
    this->shape.setOutlineColor(Colors->at(array_outlineColor[idx_outlineColor]));
    this->labelColor = Colors->at("labelColor");
    this->text.setFillColor(Colors->at("characterColor"));
    this->labelText.setFillColor(labelColor);
}

void AVLNode::prevColor()
{
    this->idx_fillColor--;
    this->idx_outlineColor--;
    this->updateColor();
}

void AVLNode::nextColor()
{
    this->idx_fillColor++;
    this->idx_outlineColor++;
    this->updateColor();
}

//Text & Label
void AVLNode::updateText()
{
    this->text.setString(std::to_string(key));
    float cur_x = shape.getPosition().x;
    float cur_y = shape.getPosition().y;
    float cur_w = shape.getGlobalBounds().width;
    float cur_h = shape.getGlobalBounds().height;

    this->text.setPosition(cur_x + cur_w / 2 - this->text.getGlobalBounds().width / 2 - 3.f * cur_w / this->standard_width,
                           cur_y + cur_h / 2 - this->text.getGlobalBounds().height / 2 - 8.f * cur_h / this->standard_height);
}

void AVLNode::newLabel(std::string new_label)
{
    if (this->idx_label == (int)this->array_label.size() - 1) {
        this->array_label.push_back(new_label);
    }
}

void AVLNode::updateLabel()
{   
    float cur_x = shape.getPosition().x;
    float cur_y = shape.getPosition().y;
    float cur_w = shape.getGlobalBounds().width;
    float cur_h = shape.getGlobalBounds().height;

    this->labelString = array_label[idx_label];
    this->labelText.setString(this->labelString);

    this->labelText.setPosition(cur_x + cur_w / 2 - labelText.getGlobalBounds().width / 2,
                                cur_y + cur_h + 5.f * cur_h / this->standard_height);
}

void AVLNode::prevLabel()
{
    this->idx_label--;
    this->updateLabel();
}

void AVLNode::nextLabel()
{
    this->idx_label++;
    this->updateLabel();
}

// Pos
void AVLNode::updatePos()
{   
    this->x = array_pos[idx_pos].x;
    this->y = array_pos[idx_pos].y;
    this->x_center = this->x + this->radius;
    this->y_center = this->y + this->radius;

    this->shape.setPosition(this->x, this->y);
}

void AVLNode::newPos(sf::Vector2f new_pos)
{
    if (this->idx_pos == (int)this->array_pos.size() - 1) {
        this->array_pos.push_back(new_pos);
    }
}

void AVLNode::prevPos()
{
    this->idx_pos--;
    this->updatePos();
}

void AVLNode::nextPos()
{
    this->idx_pos++;
    this->updatePos();
}

//Render
void AVLNode::renderAnimation()
{
}

void AVLNode::render(sf::RenderTarget *target)
{
    this->updateText();
    this->updateLabel();

    if (this->showNode) {
        target->draw(this->shape);
        target->draw(this->text);
    }

    for (int i = 0; i <= 1; ++i)
        if (this->showArrow[i])
            target->draw(this->arrow[i]);

    if (this->showLabel)
        target->draw(this->labelText);
}
