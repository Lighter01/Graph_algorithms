#ifndef LINEWRAPPER_H
#define LINEWRAPPER_H

#include <QGraphicsLineItem>

#include "node.h"

class LineWrapper
{
public:
    LineWrapper();
    LineWrapper(QGraphicsLineItem* _line, Node* _node1, Node* _node2);
    ~LineWrapper();
    void deleteLine(Node* cur_node);
    QGraphicsLineItem*& getLine();
    Node*& setNode1();
    Node*& setNode2();
private:
    QGraphicsLineItem* line;
    Node* node1; // origin node (from)
    Node* node2; // connected node (to)
};

#endif // LINEWRAPPER_H
