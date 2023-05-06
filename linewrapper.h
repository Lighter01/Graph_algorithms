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
    QGraphicsLineItem*& getLine();
    Node*& setNode1();
    Node*& setNode2();
private:
    QGraphicsLineItem* line;
    Node* node1; // origin node
    Node* node2; // connected node
};

#endif // LINEWRAPPER_H
