#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>


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

#endif // MAINWINDOW_H
