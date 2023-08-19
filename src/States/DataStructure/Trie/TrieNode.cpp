#include "TrieNode.h"

TrieNode::TrieNode()
{
}

TrieNode::TrieNode(float x, float y, float scale_x, float scale_y, int _key, sf::Font *_font, std::map<std::string, sf::Color> *Colors)
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
        idx_next[i] = -1;
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
    shape.setOutlineThickness(2.5);


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
    text.setCharacterSize(textSize * scale_x * scale_y);
    text.setFillColor(Colors->at("characterColor"));
    
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

void TrieNode::reset()
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

bool TrieNode::isLeaf()
{   
    for (int i = 0; i < numChild; ++i)
        if (this->next[i] != nullptr) return false;
    return true;
}

// Next
void TrieNode::updateNext(int next_index)
{
    this->next[next_index] = array_next[next_index][idx_next[next_index]];  /* next_index is index of current childNode, idx_next is idx of array_next */
}

void TrieNode::newNext(TrieNode *new_next, int next_index)
{
    if (this->idx_next[next_index] == (int)this->array_next[next_index].size() - 1) {
        this->array_next[next_index].push_back(new_next);
    }
}

void TrieNode::prevNext(int next_index)
{
    this->idx_next[next_index]--;
    this->updateNext(next_index);
}

void TrieNode::nextNext(int next_index)
{
    this->idx_next[next_index]++;
    this->updateNext(next_index);
}

//key
void TrieNode::updateKey()
{
    this->key = array_key[idx_key];
}

void TrieNode::newKey(int new_key)
{
    if (this->idx_key == (int)this->array_key.size() - 1) {
        this->array_key.push_back(new_key);
    }
}

void TrieNode::prevKey()
{   
    this->idx_key--;
    this->updateKey();
}

void TrieNode::nextKey()
{
    this->idx_key++;
    this->updateKey();
}


//Color
void TrieNode::setNormalColor()
{
    this->shape.setOutlineColor(this->Colors->at("normalOutlineColor"));
    this->shape.setFillColor(this->Colors->at("normalFillColor"));
}

void TrieNode::newColor(std::string fillColor, std::string outlineColor)
{
    assert(this->idx_fillColor == this->idx_outlineColor);
    if (this->idx_fillColor == (int)this->array_fillColor.size() - 1) {
        this->array_fillColor.push_back(fillColor);
        this->array_outlineColor.push_back(outlineColor);
    }
}

void TrieNode::updateColor()
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
    this->text.setFillColor(Colors->at("characterColor"));
    this->labelText.setFillColor(labelColor);
}

void TrieNode::prevColor()
{
    this->idx_fillColor--;
    this->idx_outlineColor--;
    this->updateColor();
}

void TrieNode::nextColor()
{
    this->idx_fillColor++;
    this->idx_outlineColor++;
    this->updateColor();
}

//Text & Label
void TrieNode::updateText()
{
    if (key < numChild) {
        std::string tmpStr;
        tmpStr = key + 'A';
        this->text.setString(tmpStr);
    }
    else {
        this->text.setString("");
    }

    float cur_x = shape.getPosition().x;
    float cur_y = shape.getPosition().y;
    float cur_w = shape.getGlobalBounds().width;
    float cur_h = shape.getGlobalBounds().height;

    this->text.setPosition(cur_x + cur_w / 2 - this->text.getGlobalBounds().width / 2 - 3.f * cur_w / this->standard_width,
                           cur_y + cur_h / 2 - this->text.getGlobalBounds().height / 2 - 8.f * cur_h / this->standard_height);
}

void TrieNode::newLabel(std::string new_label)
{
    if (this->idx_label == (int)this->array_label.size() - 1) {
        this->array_label.push_back(new_label);
    }
}

void TrieNode::updateLabel()
{   
    float cur_x = shape.getPosition().x;
    float cur_y = shape.getPosition().y;
    float cur_w = shape.getGlobalBounds().width;
    float cur_h = shape.getGlobalBounds().height;

    this->labelString = array_label[idx_label];
    this->labelText.setString(this->labelString);

    // this->labelText.setPosition(cur_x + cur_w / 2 - labelText.getGlobalBounds().width / 2,
    //                             cur_y + cur_h + 5.f * cur_h / this->standard_height);
    this->labelText.setPosition(cur_x - labelText.getGlobalBounds().width / 2,
                                cur_y + cur_h - 2.f * cur_h / this->standard_height);
}

void TrieNode::prevLabel()
{
    this->idx_label--;
    this->updateLabel();
}

void TrieNode::nextLabel()
{
    this->idx_label++;
    this->updateLabel();
}

// Pos
void TrieNode::updatePos()
{   
    this->x = array_pos[idx_pos].x;
    this->y = array_pos[idx_pos].y;
    this->x_center = this->x + this->radius;
    this->y_center = this->y + this->radius;

    this->shape.setPosition(this->x, this->y);
}

void TrieNode::newPos(sf::Vector2f new_pos)
{
    if (this->idx_pos == (int)this->array_pos.size() - 1) {
        this->array_pos.push_back(new_pos);
    }
}

void TrieNode::prevPos()
{
    this->idx_pos--;
    this->updatePos();
}

void TrieNode::nextPos()
{
    this->idx_pos++;
    this->updatePos();
}

//Render
void TrieNode::renderAnimation()
{
}

void TrieNode::render(sf::RenderTarget *target)
{
    this->updateText();
    this->updateLabel();

    if (this->showNode) {
        target->draw(this->shape);
        target->draw(this->text);
    }

    for (int i = 0; i < numChild; ++i)
        if (this->showArrow[i])
            target->draw(this->arrow[i]);

    if (this->showLabel)
        target->draw(this->labelText);
}

void makeArrow(sf::CircleShape *node1, sf::CircleShape *node2, sf::RectangleShape *targetArrow)
{
    /* Replace targetArrow such that it point from node1 -> node 2 */

    float pi = atan(1) * 4;
    float arrow_width, arrow_height, r1, r2, x1, y1, x2, y2;
    float alpha, AOM, BOM, OA, AOB, Ax, Ay, aOB, ax, ay, x, y, s1, s2, distance;

    auto initVariables = [&]()
    {
        arrow_width = targetArrow->getLocalBounds().width;
        arrow_height = targetArrow->getLocalBounds().height;

        r1 = node1->getRadius();
        r2 = node2->getRadius();

        x1 = node1->getPosition().x;
        y1 = node1->getPosition().y;

        x2 = node2->getPosition().x;
        y2 = node2->getPosition().y;
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

        if (r1 == 0)
            AOM = pi / 2;
        else
            AOM = atan((arrow_height / 2) / r1);

        BOM = pi / 2 - alpha;
        OA = (arrow_height / 2) / sin(AOM);

        AOB = AOM + BOM;
        Ax = OA * sin(AOB);
        Ay = OA * cos(AOB);

        aOB = BOM - AOM;
        ax = OA * sin(aOB);
        ay = OA * cos(aOB);

        x = Ax + r1 + x1;
        y = Ay + r1 + y1;

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
            x = 2 * (x1 + r1) - x;
            y = 2 * (y1 + r1) - y;
        }
        else
        {
            alpha = pi - alpha;
            x = ax + r1 + x1;
            y = ay + r1 + y1;
            x = 2 * (x1 + r1) - x;
        }
    }
    else if (y1 > y2)
    {
        alpha = 2 * pi - alpha;
        x = ax + r1 + x1;
        y = ay + r1 + y1;
        y = 2 * (y1 + r1) - y;
    }

    targetArrow->setSize(sf::Vector2f(distance - r1 - r2, arrow_height));
    targetArrow->setPosition(x, y);
    targetArrow->setRotation(alpha / pi * 180);
}

void RecalTreeAmountLeftRight(TrieNode *root, bool isRoot)
{   
    if (root == nullptr) return;
    if (isRoot) {root->depthTrie = root->amountLR[0] = root->amountLR[1] = 0;}
    root->amountLR[1] = 0;

    bool notFirstChild = 0;
    for (int i = 0; i < numChild; ++i) {
        if (!root->next[i]) continue;
        root->next[i]->depthTrie = root->depthTrie + 1;
        root->next[i]->amountLR[0] = root->amountLR[0] + root->amountLR[1] + notFirstChild;
        RecalTreeAmountLeftRight(root->next[i], 0);
        root->amountLR[1] += root->next[i]->amountLR[1] + notFirstChild;
        notFirstChild = 1;
    }
    return;
}

void RecalTreePosition(TrieNode *root, float start_x, float start_y, float distance_x, float distance_y)
{
    for (int i = 0; i < numChild; ++i) {
        if (!root->next[i]) continue;
        RecalTreePosition(root->next[i], start_x, start_y, distance_x, distance_y);
    }

    root->newPos(sf::Vector2f(start_x + distance_x * root->amountLR[0], start_y + distance_y * root->depthTrie));

    root->nextPos();

    // std::cout<<"key,dir,nL,nR,X,Y="<<root->key<<' '<<direction << ' ' << root->amountLR[0]<<' '<<root->amountLR[1]<<' '<<root->x<<' '<<root->y<<' '<<root->x_center<<' '<<root->y_center<<'\n';
    return;
}

void ResetTree(TrieNode *root)
{   
    if (root == nullptr) return;

    for (int i = 0; i < numChild; ++i) {
        ResetTree(root->next[i]);
    }

    // root->labelString = "";
    root->showNode = 1;

    for (int i = 0; i < numChild; ++i) {
        root->showArrow[i] = 0;
        if (root->next[i])
        {
            makeArrow(&root->shape, &root->next[i]->shape, &root->arrow[i]);
            root->showArrow[i] = 1;
        }
    }

    root->reset();
}

sf::Vector2f getPositionNode(TrieNode *root, TrieNode *node, float start_x, float start_y, float distance_x, float distance_y)
{
    RecalTreeAmountLeftRight(root);
    int direction = 1;
    if (node->key < root->key)
        direction = -1;
    return sf::Vector2f(start_x + direction * distance_x * (node->amountLR[std::max(-direction, 0)] + 1 /* root */),
                        start_y + distance_y * node->depthTrie);
}
