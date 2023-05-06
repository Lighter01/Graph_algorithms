#include "linewrapper.h"
#include <algorithm>

LineWrapper::LineWrapper() : line(new QGraphicsLineItem()), node1(new Node()), node2(new Node())
{

}


LineWrapper::LineWrapper(QGraphicsLineItem *_line, Node *_node1, Node *_node2) : line(_line), node1(_node1), node2(_node2)
{

}

void LineWrapper::deleteLine(Node* cur_node)
{
    /// Key idea: if the deleting node is not a first point of line, then erase lines from all nodes, where this line starts
    /// and opposite, if the deleting nore is a first point, then erase it from all points, where the line ends
    if (cur_node == node2) {
        node1->lines.erase(std::find_if(node1->lines.begin(), node1->lines.end(), [this](const std::pair<LineWrapper*, bool> cur_line) {
            return (cur_line.first->line == this->line);
        }));
    }
    if (cur_node == node1) {
        node2->lines.erase(std::find_if(node2->lines.begin(), node2->lines.end(), [this](const std::pair<LineWrapper*, bool> cur_line) {
            return (cur_line.first->line == this->line);
        }));
    }
    delete line;
}

//LineWrapper::~LineWrapper()
//{
//    node1->lines.erase(std::find_if(node1->lines.begin(), node1->lines.end(), [this](const std::pair<LineWrapper*, bool> cur_line) {
//        return (cur_line.first->line == this->line);
//    }));
//    node2->lines.erase(std::find_if(node2->lines.begin(), node2->lines.end(), [this](const std::pair<LineWrapper*, bool> cur_line) {
//        return (cur_line.first->line == this->line);
//    }));
//    delete line;
//}

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
