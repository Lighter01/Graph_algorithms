#include "graphview.h"
#include "popup.h"

#include "./ui_mainwindow.h"

#include <QHeaderView>

#include <cmath>
#include <iterator>
#include <algorithm>


graphView::graphView(Ui::MainWindow *_ui, QWidget *parent) :
    QGraphicsView(parent),
    ui(_ui),
    form_graph(),
    my_scene(new QGraphicsScene),
    line_pen(QColor(98, 57, 72)),
    selected_node_0(std::make_pair(-1, QPointF(-1, -1))),
    selected_node_1(std::make_pair(-1, QPointF(-1, -1))),
    gen_flag(0), // choose entering edge weight mode
    cellChanged_connected(false)

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
    for (auto& it : form_graph) {
        delete it;
    }
    //    for (auto& it : )
}

void graphView::on_matrixWidget_cellChanged(int row, int column)
{
    origin_graph.change_matrix().at(row).at(column) = ui->matrixWidget->item(row, column)->text().toInt();
}

std::pair<int, QPointF> graphView::findNode(const QPointF& pos)
{
    qreal x, y;
    for (int i = 0; i < form_graph.size(); ++i) {
        x = form_graph.at(i)->pos().rx();
        y = form_graph.at(i)->pos().ry();
        qDebug() << x << x + 30 << y << y + 30;
        if (pos.x() >= x && pos.x() <= x+30 && pos.y() >= y && pos.y() <= y + 30) {
            return std::make_pair(i, form_graph.at(i)->pos());
        }
    }
    return std::make_pair(-1, QPointF(-1, -1));
}

double graphView::countDistance(const QPointF& p1, const QPointF& p2)
{
    return std::sqrt(std::pow(p1.x() - p2.x(), 2) + qPow(p1.y() - p2.y(), 2));
}

void graphView::updateTableView()
{
    /// Add data into tableview
    int matrix_size = this->form_graph.size();
    ui->matrixWidget->setColumnCount(matrix_size);
    ui->matrixWidget->setRowCount(matrix_size);
    if (matrix_size > 1) {
        for (int row = 0; row < matrix_size; ++row) {
            for (int column = 0; column < matrix_size; ++column) {
                QTableWidgetItem* item = new QTableWidgetItem(tr("%1").arg(origin_graph.change_matrix().at(row).at(column)));
                ui->matrixWidget->setItem(row, column, item);
            }
        }
    }
}

void graphView::mousePressEvent(QMouseEvent *event)
{
    if (!cellChanged_connected) {
        connect(ui->matrixWidget, &QTableWidget::cellChanged, this, &graphView::on_matrixWidget_cellChanged);
    }
    if (gen_flag == 0) {
        if (event->button() == Qt::LeftButton) {
            QGraphicsItem* item = my_scene->itemAt(mapToScene(event->pos()), QTransform());
            if (item == NULL) {
                QPointF pos = mapToScene(event->pos());
                pos.rx() -= 30/2; pos.ry() -= 30/2;
                Node* newNode = new Node(QRectF(0, 0, 30, 30), form_graph.size() + 1);
                newNode->setPos(pos);
                if (form_graph.size() + 1 <= 9) {
                    newNode->getNodeId()->setPos(5,1);
                } else {
                    newNode->getNodeId()->setPos(1,1);
                }
                //adding new node
                form_graph.push_back(newNode);
                my_scene->addItem(newNode);
                for (int i = 0; i < this->form_graph.size() - 1; ++i) {
                    LineWrapper *line = new LineWrapper();
                    line->getLine() = my_scene->addLine(QLineF(0, 0, 1, 1));
                    line->getLine()->setZValue(-1);
                    line->getLine()->setPen(line_pen);
                    line->getLine() = my_scene->addLine(QLineF(0, 0, 1, 1));
                    line->getLine()->setZValue(-1);
                    line->getLine()->setPen(line_pen);
                    line->setNode1() = form_graph.back();
                    line->setNode2() = form_graph.at(i);
                    form_graph.at(i)->addLine(line, false);
                    form_graph.back()->addLine(line, true);
                    // Debug zone
//                    for (int j = 0; j < form_graph.size(); ++j) {
//                        for (int k = 0; k < form_graph.at(j)->getLines().size(); ++k) {
//                            qDebug() << j << k << form_graph.at(j)->getLines().at(k).first << form_graph.at(j)->getLines().at(k).first->setNode1() << form_graph.at(j)->getLines().at(k).first->setNode2();
//                        }
//                    }

                    /// Assign initial values for matrix of edges weights
                    if (this->form_graph.size() > origin_graph.get_matrix().size()) {
                        origin_graph.change_matrix().resize(this->form_graph.size());
                        for (auto& it :  origin_graph.change_matrix()) {
                            it.resize(this->form_graph.size());
                        }
                    }
                    origin_graph.change_matrix().at(this->form_graph.size() - 1).at(i) = countDistance(form_graph.back()->pos(), form_graph.at(i)->pos());
                    origin_graph.change_matrix().at(i).at(this->form_graph.size() - 1) = countDistance(form_graph.back()->pos(), form_graph.at(i)->pos());

                    for (int i = 0; i < origin_graph.get_matrix().size(); ++i) {
                        QDebug debug = qDebug();
                        for (int j = 0; j < origin_graph.change_matrix().at(i).size(); ++j) {
                            debug << origin_graph.change_matrix().at(i).at(j);
                        }
                    }
                    qDebug();
                    //                curve
                    //                endPoint = form_graph.at(i)->pos() + QPointF(0, form_graph.at(i)->boundingRect().height()/2);
                    //                QPointF controlPoint = (pos + endPoint) / 2 + QPointF(50, 0);
                    //                QPainterPath path(pos);
                    //                path.cubicTo(controlPoint, controlPoint, endPoint);
                    //                QGraphicsPathItem *pathItem = new QGraphicsPathItem(path);
                    //                pathItem->setPen(QPen(Qt::black));
                    //                form_graph.at(i)->addCurve(pathItem, false, pos, endPoint);
                    //                form_graph.back()->addCurve(pathItem, true, pos, endPoint);
                    //                my_scene->addItem(pathItem);
                }
                ui->matrixWidget->blockSignals(true);
                this->updateTableView();
                ui->matrixWidget->blockSignals(false);

            } else if (item->flags() & QGraphicsItem::ItemIsMovable) {
                QGraphicsView::mousePressEvent(event);
            }
        } else if (event->button() == Qt::RightButton) {
            qDebug("right button pressed");
            QGraphicsItem* item = my_scene->itemAt(mapToScene(event->pos()), QTransform());
            qDebug() << mapToScene(event->pos());
            if (item != NULL) {
                std::pair<int, QPointF> cur_selected_node = findNode(mapToScene(event->pos()));
                qDebug() << cur_selected_node.first;
                delete form_graph.at(cur_selected_node.first);

                // Shrink ui form graph's matrix
                form_graph.erase(form_graph.begin() + cur_selected_node.first);

                // Shrink original graph's matrix
                for (int i = 0; i < origin_graph.get_matrix().size(); ++i) {
                    origin_graph.change_matrix().at(i).erase(origin_graph.change_matrix().at(i).begin() + cur_selected_node.first);
                }
                origin_graph.change_matrix().erase(origin_graph.change_matrix().begin() + cur_selected_node.first);

                // Redraw indexes on nodes
                for (int i = cur_selected_node.first; i < form_graph.size(); ++i) {
                    form_graph.at(i)->setNodeId(i+1);
                }
                qDebug() << origin_graph.get_matrix().size();

                ui->matrixWidget->blockSignals(true);
                this->updateTableView();
                ui->matrixWidget->blockSignals(false);
            }
        }
    } else if (gen_flag == 1) {
        if (event->modifiers() == Qt::ControlModifier) {
            QGraphicsItem* item = my_scene->itemAt(mapToScene(event->pos()), QTransform());

            if (item != NULL) {
                if (selected_node_0.second.rx() == -1 && selected_node_0.second.ry() == -1) {
                    qDebug("Выбрали первый узел");
                    selected_node_0 = findNode(mapToScene(event->pos()));
                    form_graph.at(selected_node_0.first)->getNode()->setBrush(QColor(199,98,122));
                } else {
                    QPointF start = selected_node_0.second;
                    QPointF end = mapToScene(event->pos());
                    selected_node_1 = findNode(end);
                    if (selected_node_0.first == selected_node_1.first) {
                        qDebug("Выбран тот же самый узел");
                        form_graph.at(selected_node_0.first)->getNode()->setBrush(QColor(38, 189, 146));
                        selected_node_0 = std::make_pair(-1, QPointF(-1, -1));
                        selected_node_1 = selected_node_0;
                    } else {
                        qDebug("Выбрали второй узел");
                        form_graph.at(selected_node_1.first)->getNode()->setBrush(QColor(199,98,122));

                        MyDialog dialog(this);
                        int result = dialog.exec();
                        if (result == QDialog::Accepted) {
                            QString value = dialog.getValue();
                            LineWrapper *line = new LineWrapper();
                            line->getLine() = my_scene->addLine(start.rx(), start.ry(), end.rx(), end.ry());
                            line->getLine()->setZValue(-1);
                            line->getLine()->setPen(line_pen);
                            line->setNode1() = form_graph.at(selected_node_0.first);
                            line->setNode2() = form_graph.at(selected_node_1.first);
                            form_graph.at(selected_node_0.first)->addLine(line, true);
                            form_graph.at(selected_node_1.first)->addLine(line, false);
                            qDebug("Вес рабра был введен");
                        } else {
                            qDebug("Вес рабра не был введен");
                        }

                        form_graph.at(selected_node_0.first)->getNode()->setBrush(QColor(38, 189, 146));
                        form_graph.at(selected_node_1.first)->getNode()->setBrush(QColor(38, 189, 146));
                        selected_node_0 = std::make_pair(-1, QPointF(-1, -1));
                        selected_node_1 = selected_node_0;
                    }
                }
            }
        } else {
            QGraphicsItem* item = my_scene->itemAt(mapToScene(event->pos()), QTransform());
            if (item == NULL) {
                QPointF pos = mapToScene(event->pos());
                pos.rx() -= 30/2; pos.ry() -= 30/2;
                Node* newNode = new Node(QRectF(0, 0, 30, 30), form_graph.size() + 1);
                newNode->setPos(pos);
                if (form_graph.size() + 1 <= 9) {
                    newNode->getNodeId()->setPos(5,1);
                } else {
                    newNode->getNodeId()->setPos(1,1);
                }
                //adding new node
                form_graph.push_back(newNode);
                my_scene->addItem(newNode);
            } else if (item->flags() & QGraphicsItem::ItemIsMovable) {
                QGraphicsView::mousePressEvent(event);
            }
        }
    }
}
