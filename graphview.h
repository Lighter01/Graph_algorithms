#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QAbstractItemModel>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QMouseEvent>
#include <QItemSelection>


#include <vector>

#include "node.h"
#include "graph.h"


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
    std::pair<int, QPointF> selected_node_0, selected_node_1;
    std::vector<Node*> form_graph;
    graph origin_graph;

private:
    QPen line_pen;
    int gen_flag;

public:
    std::pair<int, QPointF> findNode(const QPointF& pos);
    double countDistance(const QPointF& p1, const QPointF& p2);
};

#endif // GRAPHVIEW_H
