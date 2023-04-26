#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsPathItem>
#include <QDebug>
#include <QPen>
#include <QColor>
#include <QPainter>
#include <QBrush>


#include <vector>


class Node : public QGraphicsItemGroup
{
public:
    Node();
    Node(const QRectF& rectangle, const int& idx, QGraphicsItem *parent = 0);

//    void addCurve(QGraphicsPathItem *curve, bool isPoint1, const QPointF& start, const QPointF& end);
    void addLine(QGraphicsLineItem *line, bool isPoint1);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

//    void moveCurveToCenter(QPointF newPos, const QPointF& start, const QPointF& end);
    void moveLinesToCenter(QPointF newPos);

    QGraphicsTextItem* getNodeId();
    QGraphicsEllipseItem* getNode();

private:
    QGraphicsEllipseItem* node;
//    std::vector<std::pair<QGraphicsPathItem*, bool>> curves;
    std::vector<std::pair<QGraphicsLineItem*, bool>> lines;

private:
    QPen rect_pen;
    QBrush rect_brush;

    QPen node_pen;
    QBrush node_brush;
    QGraphicsTextItem* node_id;
};
