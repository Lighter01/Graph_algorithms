#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QAbstractItemModel>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QMouseEvent>

#include <vector>

#include "node.h"


class graphView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit graphView(QWidget *parent = 0);
    ~graphView();

public:
    QGraphicsScene *my_scene;

private slots:
//    void slotAlarmTimer();

private:
    void mousePressEvent(QMouseEvent* event);

private:
    std::vector<Node*> my_graph;
    void addNode();

private:
    QPen line_pen;
};

#endif // GRAPHVIEW_H
