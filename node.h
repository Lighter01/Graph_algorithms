#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
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

    void addLine(QGraphicsLineItem *line, bool isPoint1);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void moveLinesToCenter(QPointF newPos);

    QGraphicsTextItem* getNodeId();

private:
    QGraphicsEllipseItem* node;
    std::vector<std::pair<QGraphicsLineItem*, bool>> lines;

private:
    QPen node_pen;
    QBrush node_brush;
    QGraphicsTextItem* node_id;
};
