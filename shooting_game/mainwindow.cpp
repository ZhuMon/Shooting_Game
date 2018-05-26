#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(40,20, 400, 600))
{
    ui -> setupUi(this);
    ui -> graphicsView -> setScene(scene);

    QPixmap Qp(":/images/player");
    player = new QGraphicsPixmapItem(Qp);
    scene -> addItem(player);
    player -> setPos(40, 20);

    //width and height of player
    player_w = Qp.width();
    player_h = Qp.height();

    player -> setScale(50.0/player_w); //50*?
    player_h = player_h * (50.0/player_w);
    player_w = 50;
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
        if(player -> y() >= 20 + 10) //border + a move
            player -> setPos(player -> x(), player -> y() - 10);
        else if(player -> y() < 20 + 10) //a move will beyond border
            player -> setPos(player -> x(), 20);  //make player on border
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        if(player -> y() < 620 - player_h - 10)
            player -> setPos(player -> x(), player -> y() + 10);
        else if(player -> y() >= 620 - player_h - 10)
            player -> setPos(player -> x(), 620 - player_h);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        if(player -> x() >= 40 + 10)
            player -> setPos(player -> x() - 10, player -> y());
        else if(player -> x() < 40 + 10)
            player -> setPos(40, player -> y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        if(player -> x() < 440 - player_w - 10)
            player -> setPos(player -> x() + 10, player -> y());
        else if(player -> x() >= 440 - player_w - 10)
            player -> setPos(440 - player_w, player -> y());
        break;
    }
}
