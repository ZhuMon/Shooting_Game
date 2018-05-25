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
    player -> setScale(0.1); //70*70
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    //border:x:40-440 y:20-620
    switch(e -> key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        if(player -> y() >= 20+10) //border + a move
            player -> setPos(player -> x(), player -> y() - 10);
        else if(player -> y() < 20 + 10) //a move will beyond border
            player -> setPos(player -> x(), 20);  //make player on border
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        if(player -> y() < 620 - 70 - 10)
            player -> setPos(player -> x(), player -> y() + 10);
        else if(player -> y() >= 620 - 70 - 10)
            player -> setPos(player -> x(), 620 - 70);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        player -> setPos(player -> x() - 10, player -> y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        player -> setPos(player -> x() + 10, player -> y());
        break;
    }
}
