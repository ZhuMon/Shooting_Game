#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(40,20, 400, 600))
{
    ui -> setupUi(this);
    ui -> graphicsView -> setScene(scene);
    player = new QGraphicsPixmapItem(QPixmap(":/images/player"));
    scene -> addItem(player);
    player -> setPos(40, 20);
    player -> setScale(0.1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
