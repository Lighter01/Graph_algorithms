#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    graph_matrix(new QStandardItemModel)
{
    ui->setupUi(this);
    ui->matrixWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->matrixWidget->setItemDelegate(new ReadOnlyDelegate());

    MyGraphView = new graphView(ui);
    ui->graphLayout->addWidget(MyGraphView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

