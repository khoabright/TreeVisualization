#include "Tree234Node.h"

Tree234Node::Tree234Node()
{
}

Tree234Node::Tree234Node(float x, float y, float scale_x, float scale_y, std::vector<int> _key, sf::Font *_font, std::map<std::string, sf::Color> *Colors)
{
    this->Colors = Colors;
    /* parameters are already scaled */

    /* just scale predeclared sizes */
    auto scaleSize = [&]()
    {
        this->radius *= scale_x;
        this->side *= scale_x;
        this->standard_width *= scale_x;
        this->standard_height *= scale_y;
    };

    scaleSize();

    //Variables
    
    // key.resize(numChild234);

    for (int i = 0; i < numChild234; ++i) {
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
    shape.setOutlineColor(Colors->at("normalOutlineColor")); // will be set in reset()
    shape.setFillColor(Colors->at("normalFillColor"));
    updateShape();

    this->width = shape.getGlobalBounds().width;
    this->height = shape.getGlobalBounds().height;


    //Color
    // this->setNormalColor();
    newColor("normal", "normal");
    nextColor();

    //Arrow
    // arrow_img.loadFromFile("Resources/Images/rightArrow.png");

    for (int i = 0; i < numChild234; ++i) {
        // arrow[i].setTexture(&arrow_img);
        arrow[i].setSize(sf::Vector2f(100.f, 2.f));
    }

    //Text
    for (int i = 0; i < numChild234; ++i) {
        text[i].setFont(*font);
        text[i].setCharacterSize(textSize * scale_x * scale_y);
        text[i].setFillColor(Colors->at("characterColor"));
    }
    
    //Label
    labelColor = Colors->at("labelColor");
    labelText.setFont(*font);
    labelText.setCharacterSize(labelTextSize * scale_x * scale_y);
    labelText.setFillColor(this->labelColor);
    labelText.setStyle(sf::Text::Bold);
    newLabel("");
    nextLabel();

    this->updateText();
}

void Tree234Node::reset()
{   
    this->x_center = this->x + this->shape.getSize().x / 2;
    this->y_center = this->y + this->shape.getSize().y / 2;

    array_fillColor.clear();
    array_outlineColor.clear();
    array_label.clear();
    for (int i = 0; i < numChild234; ++i) array_next[i].clear(); 
    array_key.clear();
    array_pos.clear();

    idx_fillColor = -1;
    idx_outlineColor = -1;
    idx_label = -1;
    for (int i = 0; i < numChild234; ++i) idx_next[i] = -1;
    idx_key = -1;
    idx_pos = -1;

    // this->setNormalColor();

    newColor("normal", "normal");
    nextColor();

    newLabel(this->labelString);
    nextLabel();

    for (int i = 0; i < numChild234; ++i) {
        newNext(this->next[i], i);
        nextNext(i);
    }

    newKey(this->key);
    nextKey();

    newPos(sf::Vector2f(this->x, this->y));
    nextPos();
}

void Tree234Node::updateShape()
{   
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f((int)key.size() * side, side));
    shape.setOutlineThickness(2.5); // (distance - side) / 2
}

/* Update along time */

//Next
void Tree234Node::updateNext(int next_index)
{
    this->next[next_index] = array_next[next_index][idx_next[next_index]];  /* next_index is index of current childNode, idx_next is idx of array_next */
}

void Tree234Node::newNext(Tree234Node *new_next, int next_index)
{
    if (this->idx_next[next_index] == (int)this->array_next[next_index].size() - 1) {
        this->array_next[next_index].push_back(new_next);
    }
}

void Tree234Node::prevNext(int next_index)
{
    this->idx_next[next_index]--;
    this->updateNext(next_index);
}

void Tree234Node::nextNext(int next_index)
{
    this->idx_next[next_index]++;
    this->updateNext(next_index);
}

//key
void Tree234Node::updateKey()
{
    this->key = array_key[idx_key];
    updateShape();
    updateText();
}

void Tree234Node::newKey(std::vector<int> new_key)
{
    if (this->idx_key == (int)this->array_key.size() - 1) {
        this->array_key.push_back(new_key);
    }
}

void Tree234Node::prevKey()
{   
    this->idx_key--;
    this->updateKey();
}

void Tree234Node::nextKey()
{
    this->idx_key++;
    this->updateKey();
}


//Color
void Tree234Node::setNormalColor()
{
    this->shape.setOutlineColor(this->Colors->at("normalOutlineColor"));
    this->shape.setFillColor(this->Colors->at("normalFillColor"));
    this->shape.setOutlineColor(this->Colors->at("newColor"));
}

void Tree234Node::newColor(std::string fillColor, std::string outlineColor)
{
    assert(this->idx_fillColor == this->idx_outlineColor);
    if (this->idx_fillColor == (int)this->array_fillColor.size() - 1) {
        this->array_fillColor.push_back(fillColor);
        this->array_outlineColor.push_back(outlineColor);
    }
}

void Tree234Node::updateColor()
{   
    if (array_fillColor[idx_fillColor] == "normal") {
        this->shape.setFillColor(Colors->at("normalFillColor"));
        this->shape.setOutlineColor(Colors->at("normalOutlineColor"));    
    }
    else {
        this->shape.setFillColor(Colors->at(array_fillColor[idx_fillColor]));
        this->shape.setOutlineColor(Colors->at(array_outlineColor[idx_outlineColor]));
    }

    this->labelColor = Colors->at("labelColor");
    for (int i = 0; i < numChild234; ++i)
        arrow[i].setFillColor(Colors->at("normalOutlineColor"));

    for (int i = 0; i < (int)key.size(); ++i)
        this->text[i].setFillColor(Colors->at("characterColor"));
    this->labelText.setFillColor(labelColor);
}

void Tree234Node::prevColor()
{
    this->idx_fillColor--;
    this->idx_outlineColor--;
    this->updateColor();
}

void Tree234Node::nextColor()
{
    this->idx_fillColor++;
    this->idx_outlineColor++;
    this->updateColor();
}

//Text & Label
void Tree234Node::updateText()
{
    int sz = key.size();
    assert(sz > 0);
    for (int i = 0; i < sz; ++i)
        text[i].setString(std::to_string(key[i]));
    float cur_x = shape.getPosition().x;
    float cur_y = shape.getPosition().y;
    float cur_w = shape.getGlobalBounds().width;
    float cur_h = shape.getGlobalBounds().height;

    for (int i = 0; i < sz; ++i) {
        text[i].setPosition(cur_x + i * cur_w / sz + cur_w / (2 * sz) - text[i].getGlobalBounds().width / 2 - 3.f * cur_w / this->standard_width,
                            cur_y + cur_h / 2 - text[i].getGlobalBounds().height / 2 - 8.f * cur_h / this->standard_height);
    }
}

void Tree234Node::newLabel(std::string new_label)
{
    if (this->idx_label == (int)this->array_label.size() - 1) {
        this->array_label.push_back(new_label);
    }
}

void Tree234Node::updateLabel()
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

void Tree234Node::prevLabel()
{
    this->idx_label--;
    this->updateLabel();
}

void Tree234Node::nextLabel()
{
    this->idx_label++;
    this->updateLabel();
}

// Pos
void Tree234Node::updatePos()
{   
    this->x = array_pos[idx_pos].x;
    this->y = array_pos[idx_pos].y;
    this->x_center = this->x + this->radius;
    this->y_center = this->y + this->radius;

    this->shape.setPosition(this->x, this->y);
}

void Tree234Node::newPos(sf::Vector2f new_pos)
{
    if (this->idx_pos == (int)this->array_pos.size() - 1) {
        this->array_pos.push_back(new_pos);
    }
}

void Tree234Node::prevPos()
{
    this->idx_pos--;
    this->updatePos();
}

void Tree234Node::nextPos()
{
    this->idx_pos++;
    this->updatePos();
}

//Render
void Tree234Node::renderAnimation()
{
}

void Tree234Node::renderArrow(sf::RenderTarget *target)
{
    for (int i = 0; i < numChild234; ++i)
        if (this->showArrow[i])
            target->draw(this->arrow[i]);
}

void Tree234Node::renderNode(sf::RenderTarget *target)
{
    this->updateText();
    this->updateLabel();

    if (this->showLabel)
        target->draw(this->labelText);

    //show Node later to shade the arrow
    if (this->showNode) {
        target->draw(this->shape);
        for (int i = 0; i < (int)key.size(); ++i)
            target->draw(this->text[i]);
    }
}

void makeArrow234(sf::RectangleShape *node1, sf::RectangleShape *node2, sf::RectangleShape *targetArrow)
{
    /* Replace targetArrow such that it point from node1 -> node 2 */
    // float pi = atan(1) * 4;

    float pi = M_PI;
    float arrow_width, arrow_height, x1, y1, x2, y2;
    float alpha, s1, s2, distance;

    auto initVariables = [&]()
    {
        arrow_width = targetArrow->getLocalBounds().width;
        arrow_height = targetArrow->getLocalBounds().height;

        x1 = node1->getPosition().x + node1->getGlobalBounds().width / 2;
        y1 = node1->getPosition().y + node1->getGlobalBounds().height / 2;

        x2 = node2->getPosition().x + node2->getGlobalBounds().width / 2;
        y2 = node2->getPosition().y + node2->getGlobalBounds().height / 2;
    };  

    auto calNewVariables = [&]()
    {
        /* pay attention for zero denominator */
        if (x1 == x2)
            alpha = pi / 2;
        else
        {
            alpha = atan(fabs(y2 - y1) / fabs(x2 - x1));
        }

        s1 = (x2 - x1);
        s2 = (y2 - y1);

        distance = sqrt(s1 * s1 + s2 * s2);
    };
    initVariables();
    calNewVariables();

    if (x1 > x2)
    {
        if (y1 > y2)
        {
            alpha = pi + alpha;
        }
        else
        {
            alpha = pi - alpha;
        }
    }
    else if (y1 > y2)
    {
        alpha = 2 * pi - alpha;
    }

    targetArrow->setSize(sf::Vector2f(distance, arrow_height));
    targetArrow->setPosition(x1, y1);
    targetArrow->setRotation(alpha / pi * 180);
}

void RecalTreeAmountLeftRight(Tree234Node *root, int direction, bool isRoot)
{   
}

void RecalTreePosition(Tree234Node *root, float &start_x, float start_y, float distance_x, float distance_y, bool isRoot)
{
    if (root == nullptr) return;
    if (isRoot) root->depthTree234 = 0;

    if (root->next[0] == nullptr)  { //leaf
        root->newPos(sf::Vector2f(start_x, start_y + distance_y * root->depthTree234));
        root->nextPos();
        start_x += root->shape.getGlobalBounds().width + distance_x;
        return;
    }

    for (int i = 0; i < numChild234; ++i) {
        if (root->next[i] == nullptr) continue;
        root->next[i]->depthTree234 = root->depthTree234 + 1;
        RecalTreePosition(root->next[i], start_x, start_y, distance_x, distance_y, 0);
        root->layout_width += root->next[i]->layout_width + distance_x;
    }
    root->layout_width -= distance_x; //redundant last space
    root->newPos(sf::Vector2f(root->layout_width / 2 - root->shape.getGlobalBounds().width / 2, start_y + distance_y * root->depthTree234));
    root->nextPos();

    return;
}

void ResetTree(Tree234Node *root)
{   
    if (root == nullptr) return;
    ResetTree(root->next[0]);
    ResetTree(root->next[1]);

    // root->labelString = "";
    root->showNode = 1;

    for (int i = 0; i < numChild234; ++i) {
        root->showArrow[i] = 0;
        if (root->next[i])
        {
            // makeArrow234(&root->shape, &root->next[i]->shape, &root->arrow[i]);
            root->showArrow[i] = 1;
        }
    }

    // std::cout<<"\nkey,depth,L,R="<<root->key<<' '<<root->depthTree234<<' ';
    // if (root->next[0]) std::cout << root->next[0]->key<<' ';
    // if (root->next[1]) std::cout << root->next[1]->key<<' ';
    // std::cout<<'\n';

    root->reset();
}

sf::Vector2f getPositionNode(Tree234Node *root, Tree234Node *node, float start_x, float start_y, float distance_x, float distance_y)
{
    RecalTreeAmountLeftRight(root);
    int direction = 1;
    if (node->key < root->key)
        direction = -1;
    return sf::Vector2f(start_x + direction * distance_x * (node->amountLR[std::max(-direction, 0)] + 1 /* root */),
                        start_y + distance_y * node->depthTree234);
}

void updateBalanceFactor(Tree234Node *root)
{
    if (root == NULL) return;
    // root->balanceFactor = heightTree234(root->next[0]) - heightTree234(root->next[1]);
}



