#include "AnimationGraph.h"

AnimationGraph::AnimationGraph(std::map<std::string, sf::Color> *Colors, float animationTime, CodeHighlight *codeHighlight)
    : Animation(Colors, animationTime, codeHighlight)
{
    this->startStep.resize(5, 1);
    this->Colors = Colors;
    this->animationTime = animationTime;
    this->codeHighlight = codeHighlight;
}

AnimationGraph::~AnimationGraph()
{
}

// Initialize

// AnimationGraph

void AnimationGraph::addCodeLines(std::vector<int> codeLines)
{
    if (!this->startStep[stepChildIndex])
        return;
    this->startStep[stepChildIndex] = 0;
    if (this->reverse) codeHighlight->prev_currentLines();
    else codeHighlight->next_currentLines(codeLines);
}

// void AnimationGraph::changeRoot(int &idx_root, std::vector<GraphNode *> array_root, GraphNode* new_root, GraphNode* root, std::vector<int> codeLines)
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

void AnimationGraph::showNode(GraphNode *targetNode, std::string targetLabel, int &numberNode, std::vector<int> codeLines) 
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

void AnimationGraph::hideNode(GraphNode *targetNode, GraphNode *parentNode, int next_index, int &numberNode, std::vector<int> codeLines)
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

void AnimationGraph::changeNodeLabel(GraphNode *targetNode, std::string targetLabel, std::vector<int> codeLines)
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

void AnimationGraph::changeNodeValue(GraphNode *targetNode, int newValue, std::vector<int> codeLines)
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

void AnimationGraph::connectNodes(GraphNode *targetNode, GraphNode *nextNode, GraphEdge *edge, std::vector<int> codeLines)
{   
    /* Don't waste time to make arrow */
    // this->dt = this->animationTime;

    //In Graph, all arrow are set beforehand, only adjust showArrow
    if (this->reverse && this->doneStep)
    {   
        edge->showSecond = 0;
        codeHighlight->prev_currentLines();
    }

    if (!this->reverse && this->startStep[stepChildIndex]) {
        edge->showSecond = 1;
        codeHighlight->next_currentLines(codeLines);
    }
    if (this->startStep[stepChildIndex]) this->startStep[stepChildIndex] = 0;

    makeArrow(&targetNode->shape, &nextNode->shape, &edge->edgeSecond);
    float scale = 1.f / this->animationTime * this->dt;
    edge->edgeSecond.setScale(sf::Vector2f(scale, 1));
}

void AnimationGraph::highlightCurrentNode(GraphNode *targetNode, std::string fillColor, std::string outlineColor, std::vector<int> codeLines)
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

void AnimationGraph::moveNode(GraphNode *targetNode, float x1, float y1)
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

void AnimationGraph::newInstruction(std::vector<GraphNode *> Nodes, std::vector<GraphEdge *> Edges)
{   
    /* Already completed all animations */
    for (GraphNode *node : Nodes) {
        if (node != nullptr) node->reset();
    }
    for (GraphEdge *edge : Edges) {
        edge->reset();
    }

    this->resetStartStep();
    this->curIndex = 0;

    for (auto &ins : instructions) ins.clear();
    this->instructions.clear();

    this->animationClock.restart();
    this->codeHighlight->reset();
    return;
}
