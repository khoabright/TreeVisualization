#include "AnimationHash.h"

AnimationHash::AnimationHash(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight)
    : Animation(Colors, animationTime, codeHighlight)
{
    this->startStep.resize(5, 1);
    this->Colors = Colors;
    this->animationTime = animationTime;
    this->codeHighlight = codeHighlight;
}

AnimationHash::~AnimationHash()
{
}

// Initialize

// AnimationHash

void AnimationHash::addCodeLines(std::vector<int> codeLines)
{
    if (!this->startStep[stepChildIndex])
        return;
    this->startStep[stepChildIndex] = 0;
    if (this->reverse) codeHighlight->prev_currentLines();
    else codeHighlight->next_currentLines(codeLines);
}

void AnimationHash::changeHead(HashNode *&head, HashNode *old_head, HashNode *targetNode, std::vector<int> codeLines)
{   
    if (!this->startStep[stepChildIndex])
        return;
    this->startStep[stepChildIndex] = 0;

    if (this->reverse)
    {
        head = old_head;
        head->prevLabel();
        targetNode->prevLabel();
        codeHighlight->prev_currentLines();
        return;
    }

    head = targetNode;
    head->newLabel("head");

    if (old_head->labelString == "head/tail")
        old_head->newLabel("tail");
    else
        old_head->newLabel("");

    head->nextLabel();
    old_head->nextLabel();
    codeHighlight->next_currentLines(codeLines);

    return;
}

void AnimationHash::changeTail(HashNode *&tail, HashNode *old_tail, HashNode *targetNode, std::vector<int> codeLines)
{   
    if (!this->startStep[stepChildIndex])
        return;
    this->startStep[stepChildIndex] = 0;

    if (this->reverse)
    {
        tail = old_tail;
        tail->prevLabel();
        targetNode->prevLabel();
        codeHighlight->prev_currentLines();
        return;
    }

    tail = targetNode;
    tail->newLabel("tail");

    if (old_tail->labelString == "head/tail")
        old_tail->newLabel("head");
    else
        old_tail->newLabel("");
        
    tail->nextLabel();
    old_tail->nextLabel();
    codeHighlight->next_currentLines(codeLines);

    return;
}

void AnimationHash::showNode(HashNode *targetNode, std::string targetLabel, std::vector<int> codeLines) 
{   
    /* For newNode only */

    targetNode->showNode = 1;

    if (this->reverse && this->doneStep) {
        targetNode->prevColor();
        targetNode->prevLabel();
        codeHighlight->prev_currentLines();
    }
    if (!this->reverse && this->startStep[stepChildIndex]) {
        targetNode->newColor("normal", "normal");
        targetNode->newLabel(targetLabel);
        targetNode->nextColor();
        targetNode->nextLabel();
        codeHighlight->next_currentLines(codeLines);
    }
    if (this->startStep[stepChildIndex]) startStep[stepChildIndex] = 0;

    float scale = 1.f / this->animationTime * this->dt;
    targetNode->shape.setScale(sf::Vector2f(scale, scale));
    targetNode->text.setScale(sf::Vector2f(scale, scale));
    targetNode->labelText.setScale(sf::Vector2f(scale, scale));

    targetNode->shape.setPosition(targetNode->x_center - targetNode->radius * scale,
                                  targetNode->y_center - targetNode->radius * scale);
    targetNode->updateText();
}

void AnimationHash::hideNode(HashNode *targetNode, std::vector<int> codeLines)
{   
    /* hide Node => hide Arrow also */
    /* For deleted Node only */

    if (this->reverse && this->doneStep) {
        if (targetNode->next != nullptr) targetNode->showArrow = 1;
        codeHighlight->prev_currentLines();
    }
    if (!this->reverse && this->startStep[stepChildIndex]) {
        targetNode->showArrow = 0;
        codeHighlight->next_currentLines(codeLines);
    }
    if (this->startStep[stepChildIndex]) startStep[stepChildIndex] = 0;
    targetNode->showNode = 1;

    float scale = 1.f - 1.f / this->animationTime * this->dt;
    targetNode->shape.setScale(sf::Vector2f(scale, scale));
    targetNode->text.setScale(sf::Vector2f(scale, scale));
    targetNode->labelText.setScale(sf::Vector2f(scale, scale));

    targetNode->shape.setPosition(targetNode->x_center - targetNode->radius * scale,
                                  targetNode->y_center - targetNode->radius * scale);
    targetNode->updateText();
}

void AnimationHash::changeNodeLabel(HashNode *targetNode, std::string targetLabel, std::vector<int> codeLines)
{   
    if (!this->startStep[stepChildIndex]) return;
    this->startStep[stepChildIndex] = 0;

    if (this->reverse) {
        targetNode->prevLabel();
        codeHighlight->prev_currentLines();
        return;
    }
    targetNode->newLabel(targetLabel);
    targetNode->nextLabel();
    codeHighlight->next_currentLines(codeLines);
}

void AnimationHash::changeNodeValue(HashNode *targetNode, int newValue, std::vector<int> codeLines)
{   
    if (!this->startStep[stepChildIndex]) return;
    this->startStep[stepChildIndex] = 0;

    if (this->reverse) {
        targetNode->prevkey();
        codeHighlight->prev_currentLines();
        return;
    }
    targetNode->newkey(newValue);
    targetNode->nextkey();
    codeHighlight->next_currentLines(codeLines);
}

void AnimationHash::connectNodes(HashNode *targetNode, HashNode *nextNode, std::vector<int> codeLines)
{   
    if (this->reverse && this->doneStep)
    {   
        targetNode->prevNext();
        codeHighlight->prev_currentLines();

        if (targetNode->next != nullptr) {
            targetNode->showArrow = 1;
            this->makeArrowHash(&targetNode->shape, &targetNode->next->shape, &targetNode->arrow);
        }
        else {
            targetNode->showArrow = 0;
        }

        targetNode->arrow.setScale(sf::Vector2f(1, 1));
        return;
    }

    if (!this->reverse && this->startStep[stepChildIndex]) {
        targetNode->newNext(nextNode);
        targetNode->nextNext();
        codeHighlight->next_currentLines(codeLines);
    }
    if (this->startStep[stepChildIndex]) this->startStep[stepChildIndex] = 0;

    if (targetNode->next != nullptr) {
        targetNode->showArrow = 1;
        this->makeArrowHash(&targetNode->shape, &targetNode->next->shape, &targetNode->arrow);
    }
    else {
        targetNode->showArrow = 0;
    }

    float scale = 1.f / this->animationTime * this->dt;
    targetNode->arrow.setScale(sf::Vector2f(scale, 1));
}

void AnimationHash::highlightCurrentNode(HashNode *targetNode, std::string targetLabel, std::string targetColor, std::vector<int> codeLines)
{   
    if (!this->startStep[stepChildIndex]) return;
    this->startStep[stepChildIndex] = 0;

    if (this->reverse) {
        targetNode->prevColor();
        targetNode->prevLabel();
        codeHighlight->prev_currentLines();
        return;
    }
    codeHighlight->next_currentLines(codeLines);

    targetNode->newColor(targetColor, targetColor);
    targetNode->newLabel(targetLabel);

    targetNode->nextColor();
    targetNode->nextLabel();
}

void AnimationHash::highlightPassedNode(HashNode *targetNode, std::string passedLabel, std::string currentLabel, std::string passedColor, std::string currentColor, std::vector<int> codeLines)
{      
    if (!this->startStep[stepChildIndex]) return;
    this->startStep[stepChildIndex] = 0;

    if (this->reverse) {
        targetNode->prevColor();
        targetNode->prevLabel();
        codeHighlight->prev_currentLines();

        if (targetNode->next == nullptr) return;

        targetNode->next->prevColor();
        targetNode->next->prevLabel();
        return;
    }
    codeHighlight->next_currentLines(codeLines);

    targetNode->newColor("normalFillColor", passedColor);
    targetNode->newLabel(passedLabel);

    targetNode->nextColor();
    targetNode->nextLabel();

    if (targetNode->next == nullptr) return;;

    targetNode->next->newColor(currentColor, currentColor);
    targetNode->next->newLabel(currentLabel);

    targetNode->next->nextColor();
    targetNode->next->nextLabel();
}


void AnimationHash::moveNode(HashNode *targetNode, float x1, float y1)
{
    if (this->reverse && this->doneStep)
    {   
        targetNode->prevPos();
        return;
    }

    if (!this->reverse && this->doneStep) {
        targetNode->newPos(sf::Vector2f(x1, y1));
        targetNode->nextPos();
        return;
    }

    if (this->startStep[stepChildIndex]) this->startStep[stepChildIndex] = 0;

    float x0 = targetNode->x;
    float y0 = targetNode->y;
    
    if (reverse) {
        x0 = targetNode->array_pos[targetNode->idx_pos - 1].x;
        y0 = targetNode->array_pos[targetNode->idx_pos - 1].y;
    }
    float sx = x1 - x0;
    float sy = y1 - y0;

    float x = x0 + sx / this->animationTime * this->dt;
    float y = y0 + sy / this->animationTime * this->dt;

    targetNode->shape.setPosition(x, y);
}

void AnimationHash::makeArrowHash(sf::CircleShape *node1, sf::CircleShape *node2, sf::RectangleShape *targetArrow)
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

void AnimationHash::Relayout(bool emptyList, HashNode *head, float start_x, float start_y, float distance_x, float distance_y, std::vector<int> codeLines)
{       
    if (emptyList) {
        if (!this->startStep[stepChildIndex]) return;
        this->startStep[stepChildIndex] = 0;

        if (this->reverse)
            codeHighlight->prev_currentLines();
        else
            codeHighlight->next_currentLines(codeLines);
        return;
    }

    if (this->startStep[stepChildIndex]) {
        this->startStep[stepChildIndex] = 0;
        for (HashNode *cur = head; cur != nullptr; cur = cur->next) {
            if (this->reverse) {
                if (cur != head) {
                    cur->prevColor();
                }
                codeHighlight->prev_currentLines();
            }
            else {
                if (cur != head) {
                    cur->newColor("normal", "normal");
                    cur->nextColor();
                }
                codeHighlight->next_currentLines(codeLines);
            }
        }
    }

    int index = 0;

    for (HashNode *cur = head; cur != nullptr; cur = cur->next, ++index)
    {   
        float x1 = start_x;
        float y1 = start_y + index * distance_y;

        this->moveNode(cur, x1, y1);
    }

    /* Show Arrow */
    for (HashNode *cur = head; cur->next != nullptr; cur = cur->next)
    {
        this->makeArrowHash(&cur->shape, &cur->next->shape, &cur->arrow);
    }
}

//Reset
void AnimationHash::updateNodePosition(HashNode *head, HashNode *tail, float start_x, float start_y, float distance)
{   
    if (head == nullptr)
        return;

    head->index = 0;
    

    for (HashNode *cur = head; cur != tail->next; cur = cur->next)
    {
        cur->labelString = "";
        cur->isNewNode = 0;
        cur->showNode = 1;

        cur->x = start_x + cur->index * distance;
        cur->y = start_y;
        cur->shape.setPosition(cur->x, cur->y);

        if (cur != tail)
            cur->next->index = cur->index + 1;
    }

    head->labelString = "head";
    tail->labelString = "tail";
    if (head == tail) head->labelString = "head/tail";

    /* Show Arrow */
    for (HashNode *cur = head; cur != tail; cur = cur->next)
    {   
        cur->showArrow = 1;
        if (cur != tail)
        {
            this->makeArrowHash(&cur->shape, &cur->next->shape, &cur->arrow);
        }
    }

    for (HashNode *cur = head; cur != tail->next; cur = cur->next)
    {
        cur->reset();
    }
}

void AnimationHash::newInstruction(std::vector<std::vector<HashNode *>> &Nodes, float start_x, float start_y, float distance_x, float distance_y)
{   
    /* Already completed all animations */
    // this->updateNodePosition(head, tail, start_x, start_y, distance);
    for (auto list : Nodes) {
        for (HashNode *cur = list[0]->next; cur != nullptr; cur = cur->next) {
            cur->newColor("normal", "normal");
            cur->nextColor();
        }
    }
    this->resetStartStep();
    this->curIndex = 0;

    for (auto &ins : instructions) ins.clear();
    this->instructions.clear();

    this->animationClock.restart();
    this->codeHighlight->reset();
}
