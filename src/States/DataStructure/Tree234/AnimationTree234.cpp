#include "AnimationTree234.h"

AnimationTree234::AnimationTree234(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight)
    : Animation(Colors, animationTime, codeHighlight)
{
    this->startStep.resize(5, 1);
    this->Colors = Colors;
    this->animationTime = animationTime;
    this->codeHighlight = codeHighlight;
}

AnimationTree234::~AnimationTree234()
{
}

// Initialize

// AnimationTree234

void AnimationTree234::addCodeLines(std::vector<int> codeLines)
{
    if (!this->startStep[stepChildIndex])
        return;
    this->startStep[stepChildIndex] = 0;
    if (this->reverse) codeHighlight->prev_currentLines();
    else codeHighlight->next_currentLines(codeLines);
}

void AnimationTree234::showNode(Tree234Node *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines) 
{   
    /* For newNode only */

    // targetNode->showNode = 1;

    if (this->reverse && this->doneStep) {
        // --numberNode;
        // targetNode->showTextArray = 0;
        // targetNode->prevColor();
        targetNode->showNode = 0;
        codeHighlight->prev_currentLines();
    }
    if (!this->reverse && this->startStep[stepChildIndex]) {
        // ++numberNode;
        // targetNode->showTextArray = 1;
        // targetNode->newColor("newColor", "newColor");
        // targetNode->nextColor();
        targetNode->showNode = 1;
        codeHighlight->next_currentLines(codeLines);
    }
    if (this->startStep[stepChildIndex]) startStep[stepChildIndex] = 0;
    return;

    // float scale = 1.f / this->animationTime * this->dt;
    // targetNode->shape.setScale(sf::Vector2f(scale, scale));
    // for (int i = 0; i < (int)targetNode->key.size(); ++i) targetNode->text[i].setScale(sf::Vector2f(scale, scale));
    // targetNode->labelText.setScale(sf::Vector2f(scale, scale));

    // /* To appear from center */
    // targetNode->shape.setPosition(targetNode->x_center - targetNode->radius * scale,
    //                               targetNode->y_center - targetNode->radius * scale);
    // targetNode->updateText();
}

void AnimationTree234::hideNode(Tree234Node *targetNode, Tree234Node *parentNode, int next_index, int &numberNode, std::vector<int> codeLines)
{   
    /* hide Node => hide Arrow also */
    /* For deleted Node only */
    if (this->reverse && this->doneStep) {
        // ++numberNode;
        // targetNode->showTextArray = 1;
        parentNode->showArrow[next_index] = 1;
        codeHighlight->prev_currentLines();
    }
    if (!this->reverse && this->startStep[stepChildIndex]) {
        // --numberNode;
        // targetNode->showTextArray = 0;
        parentNode->showArrow[next_index] = 0;
        codeHighlight->next_currentLines(codeLines);
    }
    if (this->startStep[stepChildIndex]) startStep[stepChildIndex] = 0;
    targetNode->showNode = 1;

    float scale = 1.f - 1.f / this->animationTime * this->dt;
    targetNode->shape.setScale(sf::Vector2f(scale, scale));
    // targetNode->text.setScale(sf::Vector2f(scale, scale));
    targetNode->labelText.setScale(sf::Vector2f(scale, scale));

    targetNode->shape.setPosition(targetNode->x_center - targetNode->radius * scale,
                                  targetNode->y_center - targetNode->radius * scale);
    targetNode->updateText();
}

void AnimationTree234::changeNodeLabel(Tree234Node *targetNode, std::string targetLabel, std::vector<int> codeLines)
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

void AnimationTree234::changeNodeValue(Tree234Node *targetNode, std::vector<int> newValue, std::vector<int> codeLines)
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

void AnimationTree234::connectNodes(Tree234Node *targetNode, Tree234Node *nextNode, int next_index, std::vector<int> codeLines)
{   
    /* Don't waste time to make arrow */
    // this->dt = this->animationTime;

    if (this->reverse && this->doneStep)
    {   
        targetNode->prevNext(next_index);
        codeHighlight->prev_currentLines();

        if (targetNode->next[next_index] != nullptr) {
            targetNode->showArrow[next_index] = 1;
            makeArrow234(&targetNode->shape, &targetNode->next[next_index]->shape, &targetNode->arrow[next_index]);
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
        makeArrow234(&targetNode->shape, &targetNode->next[next_index]->shape, &targetNode->arrow[next_index]);
    }
    else {
        targetNode->showArrow[next_index] = 0;
        // return;
    }

    // /* If new node is last node, dont animate arrow */
    // int curIdx = targetNode->idx_next[next_index]; 
    // if (targetNode->array_next[next_index][curIdx] == targetNode->array_next[next_index][curIdx - 1]) {
    //     return;
    // }

    // float scale = 1.f / this->animationTime * this->dt;
    // targetNode->arrow[next_index].setScale(sf::Vector2f(scale, 1));
}

void AnimationTree234::highlightCurrentNode(Tree234Node *targetNode, std::string fillColor, std::string outlineColor, std::vector<int> codeLines)
{   
    if (!this->startStep[stepChildIndex]) return;
    this->startStep[stepChildIndex] = 0;

    if (this->reverse) {
        targetNode->prevColor();
        codeHighlight->prev_currentLines();
        return;
    }
    codeHighlight->next_currentLines(codeLines);

    targetNode->newColor(fillColor, outlineColor);

    targetNode->nextColor();
}

void AnimationTree234::moveNode(Tree234Node *targetNode, float x1, float y1)
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

void AnimationTree234::Relayout(bool emptyList, Tree234Node *root, float start_x, float start_y, float distance_x, float distance_y, std::vector<int> codeLines)
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
    }

    std::function<float(Tree234Node *, float, float, float, float, bool)> 
    recalTreePosition = [&](Tree234Node *root, float start_x, float start_y, float distance_x, float distance_y, bool isRoot)
    {
        if (root == nullptr) return start_x;
        if (isRoot) root->depthTree234 = 0;

        if (root->next[0] == nullptr) { //leaf
            moveNode(root, start_x, start_y + distance_y * root->depthTree234);
            start_x += root->shape.getGlobalBounds().width + distance_x;
            root->layout_width = root->shape.getGlobalBounds().width;
            return start_x;
        }

        root->layout_width = 0;
        int initial_start_x = start_x;
        for (int i = 0; i < numChild234; ++i) {
            if (root->next[i] == nullptr) continue;
            root->next[i]->depthTree234 = root->depthTree234 + 1;
            start_x = recalTreePosition(root->next[i], start_x, start_y, distance_x, distance_y, 0);
            root->layout_width += root->next[i]->width + distance_x;
        }
        root->layout_width -= distance_x; //redundant last space

        moveNode(root, initial_start_x + root->layout_width / 2 - root->shape.getGlobalBounds().width / 2, start_y + distance_y * root->depthTree234);
        
        return start_x;
    };
    float tmp_start_x = start_x;
    recalTreePosition(root, tmp_start_x, start_y, distance_x, distance_y, 1);

    /* Update position of arrows */
    std::queue<Tree234Node*> q; // node only
    q.push(root);

    while (!q.empty()) {
        auto curNode = q.front();
        q.pop();

        if (curNode == nullptr) continue;

        for (int i = 0; i < numChild234; ++i) {
            curNode->showArrow[i] = 0;
            if (curNode->next[i])
            {
                makeArrow234(&curNode->shape, &curNode->next[i]->shape, &curNode->arrow[i]);
                curNode->showArrow[i] = 1;
                q.push(curNode->next[i]);
            }
        }
    }
}

//Reset
void AnimationTree234::updateNodePosition(Tree234Node *root, int numberNode, float start_x, float start_y, float distance_x, float distance_y)
{
    if (root == nullptr)
        return;

    std::queue<Tree234Node*> q;
    q.push(root);

    while (!q.empty()) {
        Tree234Node *u = q.front();
        q.pop();
        for (int i = 0; i < numChild234; ++i) {
            if (u->next[i] == nullptr) continue;
            u->showArrow[i] = 1;
            q.push(u->next[i]);
        }
        u->showNode = 1;
        u->reset();
    }
    return;
}

void AnimationTree234::newInstruction(Tree234Node *root, int numberNode, float start_x, float start_y, float distance_x, float distance_y)
{   
    /* Already completed all animations */
    // this->updateNodePosition(root, numberNode, start_x, start_y, distance_x, distance_y);

    this->resetStartStep();
    this->curIndex = 0;

    for (auto &ins : instructions) ins.clear();
    this->instructions.clear();

    this->animationClock.restart();
    this->codeHighlight->reset();
}
