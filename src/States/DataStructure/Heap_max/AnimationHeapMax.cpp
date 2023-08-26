#include "AnimationHeapMax.h"

AnimationHeapMax::AnimationHeapMax(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight)
    : Animation(Colors, animationTime, codeHighlight)
{
    this->startStep.resize(5, 1);
    this->Colors = Colors;
    this->animationTime = animationTime;
    this->codeHighlight = codeHighlight;
}

AnimationHeapMax::~AnimationHeapMax()
{
}

// Initialize

// AnimationHeapMax

void AnimationHeapMax::addCodeLines(std::vector<int> codeLines)
{
    if (!this->startStep[stepChildIndex])
        return;
    this->startStep[stepChildIndex] = 0;
    if (this->reverse) codeHighlight->prev_currentLines();
    else codeHighlight->next_currentLines(codeLines);
}

// void AnimationHeapMax::changeRoot(int &idx_root, std::vector<HeapMaxNode *> array_root, HeapMaxNode* new_root, HeapMaxNode* root, std::vector<int> codeLines)
// {
//     if (!this->startStep[stepChildIndex]) return;
//     this->startStep[stepChildIndex] = 0;

//     if (this->reverse) {
//         prevRoot();
//         codeHighlight->prev_currentLines();
//         return;
//     }
//     new(targetLabel);
//     targetNode->nextLabel();
//     codeHighlight->next_currentLines(codeLines);
// }

void AnimationHeapMax::showNode(HeapMaxNode *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines) 
{   
    /* For newNode only */

    targetNode->showNode = 1;

    if (this->reverse && this->doneStep) {
        // --numberNode;
        targetNode->showTextArray = 0;
        targetNode->prevColor();
        codeHighlight->prev_currentLines();
    }
    if (!this->reverse && this->startStep[stepChildIndex]) {
        // ++numberNode;
        targetNode->showTextArray = 1;
        targetNode->newColor("newColor", "newColor");
        targetNode->nextColor();
        codeHighlight->next_currentLines(codeLines);
    }
    if (this->startStep[stepChildIndex]) startStep[stepChildIndex] = 0;

    float scale = 1.f / this->animationTime * this->dt;
    targetNode->shape.setScale(sf::Vector2f(scale, scale));
    targetNode->text.setScale(sf::Vector2f(scale, scale));
    targetNode->labelText.setScale(sf::Vector2f(scale, scale));

    /* To appear from center */
    targetNode->shape.setPosition(targetNode->x_center - targetNode->radius * scale,
                                  targetNode->y_center - targetNode->radius * scale);
    targetNode->updateText();
}

void AnimationHeapMax::hideNode(HeapMaxNode *targetNode, HeapMaxNode *parentNode, int next_index, int &numberNode, std::vector<int> codeLines)
{   
    /* hide Node => hide Arrow also */
    /* For deleted Node only */
    if (this->reverse && this->doneStep) {
        // ++numberNode;
        targetNode->showTextArray = 1;
        parentNode->showArrow[next_index] = 1;
        codeHighlight->prev_currentLines();
    }
    if (!this->reverse && this->startStep[stepChildIndex]) {
        // --numberNode;
        targetNode->showTextArray = 0;
        parentNode->showArrow[next_index] = 0;
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

void AnimationHeapMax::changeNodeLabel(HeapMaxNode *targetNode, std::string targetLabel, std::vector<int> codeLines)
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

void AnimationHeapMax::changeNodeValue(HeapMaxNode *targetNode, int newValue, std::vector<int> codeLines)
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

void AnimationHeapMax::connectNodes(HeapMaxNode *targetNode, HeapMaxNode *nextNode, int next_index, std::vector<int> codeLines)
{   
    /* Don't waste time to make arrow */
    // this->dt = this->animationTime;

    //In HeapMax, all arrow are set beforehand, only adjust showArrow
    if (this->reverse && this->doneStep)
    {   
        targetNode->showArrow[next_index] = 0;
        codeHighlight->prev_currentLines();
    }

    if (!this->reverse && this->startStep[stepChildIndex]) {
        targetNode->showArrow[next_index] = 1;
        codeHighlight->next_currentLines(codeLines);
    }
    if (this->startStep[stepChildIndex]) this->startStep[stepChildIndex] = 0;

    makeArrowHeapMax(&targetNode->shape, &targetNode->next[next_index]->shape, &targetNode->arrow[next_index]);
    float scale = 1.f / this->animationTime * this->dt;
    targetNode->arrow[next_index].setScale(sf::Vector2f(scale, 1));
}

void AnimationHeapMax::highlightCurrentNode(HeapMaxNode *targetNode, std::string targetColor, std::vector<int> codeLines)
{   
    if (!this->startStep[stepChildIndex]) return;
    this->startStep[stepChildIndex] = 0;

    if (this->reverse) {
        targetNode->prevColor();
        codeHighlight->prev_currentLines();
        return;
    }
    codeHighlight->next_currentLines(codeLines);

    targetNode->newColor(targetColor, targetColor);

    targetNode->nextColor();
}

void AnimationHeapMax::moveNode(HeapMaxNode *targetNode, float x1, float y1)
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
    // std::cout<<"x0,y0,x1,y1,sx,sy="<<x0<<' '<<y0<<' '<<x1<<' '<<y1<<' '<<sx<<' '<<sy<<'\n';

    float x = x0 + sx / this->animationTime * this->dt;
    float y = y0 + sy / this->animationTime * this->dt;

    targetNode->shape.setPosition(x, y);
}


void AnimationHeapMax::Relayout(bool emptyList, HeapMaxNode *root, float start_x, float start_y, float distance_x, float distance_y, std::vector<int> codeLines)
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
        RecalTreeAmountLeftRight(root);
    }

    std::queue<std::pair<HeapMaxNode* , int>> Queue; // second is 1 or -1 represent right/left to the root
    Queue.push({root, 0});

    while (!Queue.empty()) {
        auto Pair = Queue.front();
        auto curNode = Pair.first;
        auto direction = Pair.second;
        Queue.pop();

        if (curNode == nullptr) continue;

        if (direction == 0) {
            Queue.push({curNode->next[0], -1});
            Queue.push({curNode->next[1], 1});
            moveNode(curNode, start_x, start_y);
            
            continue;
        }

        Queue.push({curNode->next[0], direction});
        Queue.push({curNode->next[1], direction});
        //1->0   -1->1
        moveNode(curNode, start_x + direction * distance_x * (curNode->amountLR[std::max(-direction, 0)] + 1 /* root */), start_y + distance_y * curNode->depthHeapMax);
    }

    /* Update position of arrows */
    std::queue<HeapMaxNode*> q; // node only
    q.push(root);

    while (!q.empty()) {
        auto curNode = q.front();
        q.pop();

        if (curNode == nullptr) continue;

        for (int i = 0; i < numChildHeapMax; ++i) {
            curNode->showArrow[i] = 0;
            if (curNode->next[i])
            {
                makeArrowHeapMax(&curNode->shape, &curNode->next[i]->shape, &curNode->arrow[i]);
                curNode->showArrow[i] = 1;
            }
        }

        q.push(curNode->next[0]);
        q.push(curNode->next[1]);
    }
}

//Reset
void AnimationHeapMax::updateNodePosition(HeapMaxNode *root, std::vector<HeapMaxNode*> arrNode, int numberNode, float start_x, float start_y, float distance_x, float distance_y)
{
    if (root == nullptr)
        return;

    // RecalTreeAmountLeftRight(root);
    // RecalTreePosition(root, start_x, start_y, distance_x, distance_y);
    for (int i = 1; i <= numberNode; ++i) {
        if (2 * i <= numberNode) arrNode[i]->showArrow[0] = 1;
        if (2 * i + 1 <= numberNode) arrNode[i]->showArrow[1] = 1;
        arrNode[i]->showNode = 1;
        arrNode[i]->showTextArray = 1;
        arrNode[i]->reset();
    }

    return;
}

void AnimationHeapMax::newInstruction(HeapMaxNode *root, std::vector<HeapMaxNode*> arrNode, int numberNode, float start_x, float start_y, float distance_x, float distance_y)
{   
    /* Already completed all animations */
    this->updateNodePosition(root, arrNode, numberNode, start_x, start_y, distance_x, distance_y);

    this->resetStartStep();
    this->curIndex = 0;

    for (auto &ins : instructions) ins.clear();
    this->instructions.clear();

    this->animationClock.restart();
    this->codeHighlight->reset();
}
