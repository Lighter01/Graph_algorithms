#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    MyGraphView(new graphView(ui)),
    graph_matrix(new QStandardItemModel)
{
    ui->setupUi(this);
    ui->graphLayout->addWidget(MyGraphView);
    ui->matrixWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->matrixWidget->setItemDelegate(new ReadOnlyDelegate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

