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

void RecalTreeAmountLeftRight(AVLNode *root, int direction, bool isRoot)
{   
    if (root == nullptr) return;
    if (isRoot) root->depthAVL = 0;

    if (root->next[0]) root->next[0]->depthAVL = root->depthAVL + 1;
    if (root->next[1]) root->next[1]->depthAVL = root->depthAVL + 1;
    
    if (isRoot) {
        if (root->next[0])
            root->next[0]->amountLR[0] = root->next[0]->amountLR[1] = 0;
        if (root->next[1])
            root->next[1]->amountLR[0] = root->next[1]->amountLR[1] = 0;
        RecalTreeAmountLeftRight(root->next[0], 1, 0);
        RecalTreeAmountLeftRight(root->next[1], 0, 0);
        return;
    }
    
    if (root->next[direction]) root->next[direction]->amountLR[direction] = root->amountLR[direction];
    RecalTreeAmountLeftRight(root->next[direction], direction, 0);
    if (root->next[direction]) root->amountLR[direction] += root->next[direction]->subTreeSize;
    if (root->next[direction ^ 1]) root->next[direction ^ 1]->amountLR[direction] = root->amountLR[direction] + 1 /* itself */;
    RecalTreeAmountLeftRight(root->next[direction ^ 1], direction, 0);

    root->subTreeSize = 1;
    if (root->next[0]) root->subTreeSize += root->next[0]->subTreeSize;
    if (root->next[1]) root->subTreeSize += root->next[1]->subTreeSize;

    // std::cout<<"\nkey,size,amLR="<<root->key<<' '<<root->subTreeSize<<' '<<root->amountLR[0]<<' '<<root->amountLR[1]<<'\n';
    return;
}

void RecalTreePosition(AVLNode *root, float start_x, float start_y, float distance_x, float distance_y, int direction)
{
    if (root == nullptr) return;

    if (root->depthAVL == 0) {
        RecalTreePosition(root->next[0], start_x, start_y, distance_x, distance_y, -1);
        RecalTreePosition(root->next[1], start_x, start_y, distance_x, distance_y, 1);
        root->newPos(sf::Vector2f(start_x, start_y));
        return;
    }

    RecalTreePosition(root->next[0], start_x, start_y, distance_x, distance_y, direction);
    RecalTreePosition(root->next[1], start_x, start_y, distance_x, distance_y, direction);

    root->newPos(sf::Vector2f(start_x + direction * distance_x * (root->amountLR[std::max(-direction, 0)] + 1 /* root */),
                              start_y + distance_y * root->depthAVL));

    root->nextPos();

    // std::cout<<"key,dir,nL,nR,X,Y="<<root->key<<' '<<direction << ' ' << root->amountLR[0]<<' '<<root->amountLR[1]<<' '<<root->x<<' '<<root->y<<' '<<root->x_center<<' '<<root->y_center<<'\n';
    return;
}

void ResetTree(AVLNode *root)
{   
    if (root == nullptr) return;
    ResetTree(root->next[0]);
    ResetTree(root->next[1]);

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

    // std::cout<<"\nkey,depth,L,R="<<root->key<<' '<<root->depthAVL<<' ';
    // if (root->next[0]) std::cout << root->next[0]->key<<' ';
    // if (root->next[1]) std::cout << root->next[1]->key<<' ';
    // std::cout<<'\n';

    root->reset();
}

sf::Vector2f getPositionNode(AVLNode *root, AVLNode *node, float start_x, float start_y, float distance_x, float distance_y)
{
    RecalTreeAmountLeftRight(root);
    int direction = 1;
    if (node->key < root->key)
        direction = -1;
    return sf::Vector2f(start_x + direction * distance_x * (node->amountLR[std::max(-direction, 0)] + 1 /* root */),
                        start_y + distance_y * node->depthAVL);
}

void updateBalanceFactor(AVLNode *root)
{
    if (root == NULL) return;
    // root->balanceFactor = heightAVL(root->next[0]) - heightAVL(root->next[1]);
}

// //Root
// void updateRoot(int idx_root, AVLNode* &root, std::vector<AVLNode*>& array_root) {
//     root = array_root[idx_root];
// }
// void newRoot(AVLNode* root, std::vector<AVLNode*>& array_root) {
//     if (idx_root == (int)array_root.size() - 1) {
//         array_root.push_back(root);
//     }
// }
// void prevRoot(int &idx_root, AVLNode* &root, std::vector<AVLNode*>& array_root) {
//     this->idx_pos--;
//     this->updateRoot(idx_root, root, array_root);
// }
// void nextRoot(int &idx_root, AVLNode* &root, std::vector<AVLNode*>& array_root) {
//     this->idx_pos++;
//     this->updateRoot(idx_root, root, array_root);
// }


