#include "graphview.h"

graphView::graphView(QWidget *parent) :
    QGraphicsView(parent),
    my_graph(),
    my_scene(new QGraphicsScene),
    line_pen(QColor(98, 57, 72))
{
    /* Немного поднастроим отображение виджета и его содержимого */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    /* Также зададим минимальные размеры виджета
     * */
    this->setMinimumHeight(600);
    this->setMinimumWidth(800);

    my_scene->setSceneRect(0, 0, 800, 600);

    this->setScene(my_scene);          // Устанавливаем сцену в виджет
    this->setMouseTracking(true);

    this->setRenderHint(QPainter::Antialiasing);

    line_pen.setWidth(2);
}

graphView::~graphView()
{
    for (auto& it : my_graph) {
        delete it;
    }
//    for (auto& it : )
}

void graphView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsItem* item = my_scene->itemAt(mapToScene(event->pos()), QTransform());
    if (item == NULL) {
        QPointF pos = mapToScene(event->pos());
        pos.rx() -= 30/2; pos.ry() -= 30/2;
        Node* newNode = new Node(QRectF(0, 0, 30, 30), my_graph.size() + 1);
        newNode->setPos(pos);
        newNode->getNodeId()->setPos(pos);
        //adding new node
        my_graph.push_back(newNode);
        my_scene->addItem(newNode);
        my_scene->addItem(newNode->getNodeId());

        QGraphicsLineItem *line;
        for (int i = 0; i < this->my_graph.size() - 1; ++i) {
            line = my_scene->addLine(QLineF(0, 0, 1, 1));
            line->setZValue(-1);
            line->setPen(line_pen);
            my_graph.at(i)->addLine(line, false);
            my_graph.back()->addLine(line, true);
        }
    } else if (item->flags() & QGraphicsItem::ItemIsMovable) {
        QGraphicsView::mousePressEvent(event);
    }
}

void graphView::addNode()
{

}


