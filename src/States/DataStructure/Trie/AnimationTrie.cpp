#include "AnimationTrie.h"

AnimationTrie::AnimationTrie(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight)
    : Animation(Colors, animationTime, codeHighlight)
{
    this->startStep.resize(5, 1);
    this->Colors = Colors;
    this->animationTime = animationTime;
    this->codeHighlight = codeHighlight;
}

AnimationTrie::~AnimationTrie()
{
}

// Initialize

// AnimationTrie

void AnimationTrie::addCodeLines(std::vector<int> codeLines)
{
    if (!this->startStep[stepChildIndex])
        return;
    this->startStep[stepChildIndex] = 0;
    if (this->reverse) codeHighlight->prev_currentLines();
    else codeHighlight->next_currentLines(codeLines);
}

void AnimationTrie::showNode(TrieNode *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines) 
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

    /* To appear from center */
    targetNode->shape.setPosition(targetNode->x_center - targetNode->radius * scale,
                                  targetNode->y_center - targetNode->radius * scale);
    targetNode->updateText();
}

void AnimationTrie::hideNode(TrieNode *targetNode, int &numberNode, std::vector<int> codeLines)
{   
    /* hide Node => hide Arrow also */
    /* For deleted Node only */
    if (this->reverse && this->doneStep) {
        ++numberNode;
        for (int i = 0; i < numChildTrie; ++i)
            if (targetNode->next[i] != nullptr)
                targetNode->showArrow[i] = 1;
        codeHighlight->prev_currentLines();
    }
    if (!this->reverse && this->startStep[stepChildIndex]) {
        --numberNode;
        for (int i = 0; i < numChildTrie; ++i)
            targetNode->showArrow[i] = 0;
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

void AnimationTrie::changeNodeLabel(TrieNode *targetNode, std::string targetLabel, std::vector<int> codeLines)
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

void AnimationTrie::changeNodeValue(TrieNode *targetNode, int newValue, std::vector<int> codeLines)
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

void AnimationTrie::connectNodes(TrieNode *targetNode, TrieNode *nextNode, int next_index, std::vector<int> codeLines)
{   
    /* Don't waste time to make arrow */
    // this->dt = this->animationTime;

    if (this->reverse && this->doneStep)
    {   
        targetNode->prevNext(next_index);
        codeHighlight->prev_currentLines();

        if (targetNode->next[next_index] != nullptr) {
            targetNode->showArrow[next_index] = 1;
            makeArrowTrie(&targetNode->shape, &targetNode->next[next_index]->shape, &targetNode->arrow[next_index]);
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
        makeArrowTrie(&targetNode->shape, &targetNode->next[next_index]->shape, &targetNode->arrow[next_index]);
    }
    else {
        targetNode->showArrow[next_index] = 0;
        // return;
    }

    /* If new node is last node, dont animate arrow */
    int curIdx = targetNode->idx_next[next_index]; 
    if (targetNode->array_next[next_index][curIdx] == targetNode->array_next[next_index][curIdx - 1]) {
        return;
    }

    float scale = 1.f / this->animationTime * this->dt;
    targetNode->arrow[next_index].setScale(sf::Vector2f(scale, 1));
}

void AnimationTrie::highlightCurrentNode(TrieNode *targetNode, std::string targetColor, std::vector<int> codeLines)
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

void AnimationTrie::moveNode(TrieNode *targetNode, float x1, float y1)
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


void AnimationTrie::Relayout(bool emptyList, TrieNode *root, float start_x, float start_y, float distance_x, float distance_y, std::vector<int> codeLines)
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

    std::queue<TrieNode*> Queue; 
    Queue.push(root);

    while (!Queue.empty()) {
        auto curNode = Queue.front();
        Queue.pop();

        if (curNode == nullptr) continue;

        moveNode(curNode, start_x + distance_x * curNode->amountLR[0], start_y + distance_y * curNode->depthTrie);

        for (int i = 0; i < numChildTrie; ++i) {
            Queue.push(curNode->next[i]);
        }
        
    }

    /* Update position of arrows, (should be after moveNode to align correctly) */
    std::queue<TrieNode*> q; // node only
    q.push(root);

    while (!q.empty()) {
        auto curNode = q.front();
        q.pop();

        if (curNode == nullptr) continue;

        for (int i = 0; i < numChildTrie; ++i) {
            q.push(curNode->next[i]);
            curNode->showArrow[i] = 0;
            if (curNode->next[i])
            {
                makeArrowTrie(&curNode->shape, &curNode->next[i]->shape, &curNode->arrow[i]);
                curNode->showArrow[i] = 1;
            }
        }
    }
}

//Reset
void AnimationTrie::updateNodePosition(TrieNode *root, float start_x, float start_y, float distance_x, float distance_y)
{
    if (root == nullptr)
        return;

    RecalTreeAmountLeftRight(root);
    RecalTreePosition(root, start_x, start_y, distance_x, distance_y);
    ResetTree(root);
}

void AnimationTrie::newInstruction(TrieNode *root, float start_x, float start_y, float distance_x, float distance_y)
{   
    /* Already completed all animations */
    this->updateNodePosition(root, start_x, start_y, distance_x, distance_y);

    this->resetStartStep();
    this->curIndex = 0;

    for (auto &ins : instructions) ins.clear();
    this->instructions.clear();

    this->animationClock.restart();
    this->codeHighlight->reset();
}
