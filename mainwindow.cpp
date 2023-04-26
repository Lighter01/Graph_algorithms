#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    MyGraphView(new graphView())

{
    ui->setupUi(this);
    ui->graphLayout->addWidget(MyGraphView);
}

MainWindow::~MainWindow()
{
    delete ui;
}


