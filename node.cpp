#include "node.h"


Node::Node (const QRectF& rectangle, const int& idx, QGraphicsItem *parent) :
    QGraphicsItemGroup(parent),
    node(new QGraphicsEllipseItem(rectangle)),
    rect_pen(QColor(98, 57, 72)),
    rect_brush(QColor(55, 216, 153)),
    node_pen(QColor(19, 136, 67)),
    node_brush(QColor(38, 189, 146)),
    node_id(new QGraphicsTextItem(QString::number(idx)))

{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    node->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsScenePositionChanges);
    node_id->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsScenePositionChanges);

    node_pen.setWidth(2);
    node->setPen(node_pen);
    node->setBrush(node_brush);

    node_id->setDefaultTextColor(QColor(255, 198, 42));
    node_id->setFont(QFont("Franklin Gothic Medium", 13));
    node_id->setZValue(2);

    addToGroup(node);
    addToGroup(node_id);



}

//void Node::addCurve(QGraphicsPathItem *curve, bool isPoint1, const QPointF& start, const QPointF& end)
//{
//    this->curves.emplace_back(curve, isPoint1);
//    moveCurveToCenter(QPointF(this->pos().x(), this->pos().y()), start, end);
//}


void Node::addLine(QGraphicsLineItem *line, bool isPoint1) {
    this->lines.emplace_back(line, isPoint1);
    moveLinesToCenter(QPointF(this->pos().x(), this->pos().y()));
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
//        qDebug() << value;
        QPointF newPos = value.toPointF();
        moveLinesToCenter(newPos);
    }
    return QGraphicsItem::itemChange(change, value);
}

//void Node::moveCurveToCenter(QPointF newPos, const QPointF& start, const QPointF& end)
//{
//    int xOffset = boundingRect().x() + boundingRect().width()/2;
//    int yOffset = boundingRect().y() + boundingRect().height()/2;

//    QPointF newCenterPos = QPointF(newPos.x() + xOffset, newPos.y() + yOffset);

//    for (auto& it : this->curves) {
//        QPointF p1 = it.second ? newCenterPos : start;
//        QPointF p2 = it.second ? end : newCenterPos;

//        QPointF controlPoint = (p1 + p2) / 2 + QPointF(50, 0);
//        QPainterPath path(p1);
//        path.cubicTo(controlPoint, controlPoint, p2);
//        it.first = new QGraphicsPathItem(path);
//    }
//}

void Node::moveLinesToCenter(QPointF newPos) {
    // Converts the elipse position (top-left)
    // to its center position
    int xOffset = boundingRect().x() + boundingRect().width()/2;
    int yOffset = boundingRect().y() + boundingRect().height()/2;

    QPointF newCenterPos = QPointF(newPos.x() + xOffset, newPos.y() + yOffset);

    for (auto& it : this->lines) {
        // Move the required point of the line to the center of the elipse
        QPointF p1 = it.second ? newCenterPos : it.first->line().p1();
        QPointF p2 = it.second ? it.first->line().p2() : newCenterPos;

        it.first->setLine(QLineF(p1, p2));
    }
}

QGraphicsTextItem *Node::getNodeId()
{
    return this->node_id;
}

QGraphicsEllipseItem* Node::getNode()
{
    return this->node;
}


