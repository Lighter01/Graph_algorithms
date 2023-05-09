#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemDelegate>


#include "graph.h"
#include "graphview.h"

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    graph g;
    graphView *MyGraphView;
    QStandardItemModel* graph_matrix;

signals:
    void graphChanged();
};



// Help class for disabling cells with (n, n) indices
// Help class for disabling cells with (n, n) indices
class ReadOnlyDelegate : public QItemDelegate
{
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        if (index.column() == index.row()) {
            return nullptr;
        } else {
            return QItemDelegate::createEditor(parent, option, index);
        }
    }
};

#endif // MAINWINDOW_H
