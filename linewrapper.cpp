#include "linewrapper.h"
#include <algorithm>

LineWrapper::LineWrapper() : line(new QGraphicsLineItem()), node1(new Node()), node2(new Node())
{

}


LineWrapper::LineWrapper(QGraphicsLineItem *_line, Node *_node1, Node *_node2) : line(_line), node1(_node1), node2(_node2)
{

}

LineWrapper::~LineWrapper()
{

    node2->lines.erase(std::find_if(node2->lines.begin(), node2->lines.end(), [this](const std::pair<LineWrapper*, bool> cur_line) {
        return (cur_line.first->line == this->line) && (cur_line.second == false);
    }));
    delete line;
}

QGraphicsLineItem*& LineWrapper::getLine()
{
    return this->line;
}

Node*& LineWrapper::setNode1()
{
    return this->node1;
}

Node*& LineWrapper::setNode2()
{
    return this->node2;
}
