#include "AnimationAVL.h"

AnimationAVL::AnimationAVL(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight)
    : Animation(Colors, animationTime, codeHighlight)
{
    this->startStep.resize(5, 1);
    this->Colors = Colors;
    this->animationTime = animationTime;
    this->codeHighlight = codeHighlight;
}

AnimationAVL::~AnimationAVL()
{
}

// Initialize

// AnimationAVL

void AnimationAVL::addCodeLines(std::vector<int> codeLines)
{
    if (!this->startStep[stepChildIndex])
        return;
    this->startStep[stepChildIndex] = 0;
    if (this->reverse) codeHighlight->prev_currentLines();
    else codeHighlight->next_currentLines(codeLines);
}



void AnimationAVL::showNode(AVLNode *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines) 
{   
    /* For newNode only */

    targetNode->showNode = 1;

    if (this->reverse && this->doneStep) {
        --numberNode;
        targetNode->prevColor();
        targetNode->prevLabel();
        codeHighlight->prev_currentLines();
    }
    if (!this->reverse && this->startStep[stepChildIndex]) {
        ++numberNode;
        targetNode->newColor("newColor", "newColor");
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

void AnimationAVL::hideNode(AVLNode *targetNode, int &numberNode, std::vector<int> codeLines)
{   
    /* hide Node => hide Arrow also */
    /* For deleted Node only */

    // if (this->reverse && this->doneStep) {
    //     ++numberNode;
    //     if (targetNode->next != nullptr) targetNode->showArrow[next_index] = 1;
    //     codeHighlight->prev_currentLines();
    // }
    // if (!this->reverse && this->startStep[stepChildIndex]) {
    //     --numberNode;
    //     targetNode->showArrow[next_index] = 0;
    //     codeHighlight->next_currentLines(codeLines);
    // }
    // if (this->startStep[stepChildIndex]) startStep[stepChildIndex] = 0;
    // targetNode->showNode = 1;

    // float scale = 1.f - 1.f / this->animationTime * this->dt;
    // targetNode->shape.setScale(sf::Vector2f(scale, scale));
    // targetNode->text.setScale(sf::Vector2f(scale, scale));
    // targetNode->labelText.setScale(sf::Vector2f(scale, scale));

    // targetNode->shape.setPosition(targetNode->x_center - targetNode->radius * scale,
    //                               targetNode->y_center - targetNode->radius * scale);
    // targetNode->updateText();
}

void AnimationAVL::changeNodeLabel(AVLNode *targetNode, std::string targetLabel, std::vector<int> codeLines)
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

void AnimationAVL::changeNodeValue(AVLNode *targetNode, int newValue, std::vector<int> codeLines)
{   
    if (!this->startStep[stepChildIndex]) return;
    this->startStep[stepChildIndex] = 0;

    if (this->reverse) {
        targetNode->prevKey();
        codeHighlight->prev_currentLines();
        return;
    }
    targetNode->newKey(newValue);
    targetNode->nextKey();
    codeHighlight->next_currentLines(codeLines);
}

void AnimationAVL::connectNodes(AVLNode *targetNode, AVLNode *nextNode, int next_index, std::vector<int> codeLines)
{   
    if (this->reverse && this->doneStep)
    {   
        targetNode->prevNext(next_index);
        codeHighlight->prev_currentLines();

        if (targetNode->next[next_index] != nullptr) {
            targetNode->showArrow[next_index] = 1;
            this->makeArrow(&targetNode->shape, &targetNode->next[next_index]->shape, &targetNode->arrow[next_index]);
        }
        else {
            targetNode->showArrow[next_index] = 0;
        }

        targetNode->arrow[next_index].setScale(sf::Vector2f(1, 1));
        return;
    }

    if (!this->reverse && this->startStep[stepChildIndex]) {
        targetNode->newNext(nextNode, next_index);
        targetNode->nextNext(next_index);
        codeHighlight->next_currentLines(codeLines);
    }
    if (this->startStep[stepChildIndex]) this->startStep[stepChildIndex] = 0;

    if (targetNode->next[next_index] != nullptr) {
        targetNode->showArrow[next_index] = 1;
        this->makeArrow(&targetNode->shape, &targetNode->next[next_index]->shape, &targetNode->arrow[next_index]);
    }
    else {
        targetNode->showArrow[next_index] = 0;
    }

    float scale = 1.f / this->animationTime * this->dt;
    targetNode->arrow[next_index].setScale(sf::Vector2f(scale, 1));
}

void AnimationAVL::highlightCurrentNode(AVLNode *targetNode, std::string targetLabel, std::string targetColor, std::vector<int> codeLines)
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

void AnimationAVL::moveNode(AVLNode *targetNode, float x1, float y1)
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

void AnimationAVL::makeArrow(sf::CircleShape *node1, sf::CircleShape *node2, sf::RectangleShape *targetArrow)
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

void AnimationAVL::Relayout(bool emptyList, AVLNode *root, float start_x, float start_y, float distance, std::vector<int> codeLines)
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

    /* Change node label */
    
    /* Move node to new position */
    // for (AVLNode *cur = head; cur != tail->next; cur = cur->next)
    // {
    //     float x1 = start_x + cur->index * distance;
    //     float y1 = start_y;

    //     this->moveNode(cur, x1, y1);
    //     if (cur != tail)
    //     {
    //         cur->next->index = cur->index + 1;
    //     }
    // }

    /* Show Arrow by makeArrow*/
}

//Reset
void AnimationAVL::updateNodePosition(AVLNode *root, float start_x, float start_y, float distance)
{   
    if (root == nullptr)
        return;
    

    /* Set new position */
        // cur->labelString = "";
        // cur->isNewNode = 0;
        // cur->showNode = 1;

        // cur->x = start_x + cur->index * distance;
        // cur->y = start_y;
        // cur->shape.setPosition(cur->x, cur->y);
            

    /* Show Arrow by makeArrow*/

    /* cur->reset() */
}

void AnimationAVL::newInstruction(AVLNode *root, float start_x, float start_y, float distance)
{   
    /* Already completed all animations */
    this->updateNodePosition(root, start_x, start_y, distance);

    this->resetStartStep();
    this->curIndex = 0;

    for (auto &ins : instructions) ins.clear();
    this->instructions.clear();

    this->animationClock.restart();
    this->codeHighlight->reset();
}
