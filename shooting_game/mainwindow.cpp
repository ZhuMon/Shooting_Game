#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(40,20, 400, 600)),
    timer(new QTimer),
    timerRF(new QTimer),
    player(new Player)
{
    ui -> setupUi(this);
    ui -> graphicsView -> setScene(scene);

    //QPixmap Qp(":/images/player");
    //player = new QGraphicsPixmapItem(Qp);
    scene -> addItem(player);
    //player -> setPos(200, 500);

    //width and height of player
    //player_w = Qp.width();
    //player_h = Qp.height();

    //player -> setScale(50.0/player_w); //50*?

    //new width and height
    //player_h = player_h * (50.0/player_w);
    //player_w = 50;

    timer -> start(10);
    timerRF -> start(100);

    connect(timerRF, SIGNAL(timeout()), this, SLOT(on_rapid_fire_clicked()));

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
        if(player -> y() < 620 - player->getH() - 10)
            player -> setPos(player -> x(), player -> y() + 10);
        else if(player -> y() >= 620 - player->getH() - 10)
            player -> setPos(player -> x(), 620 - player->getH());
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
        if(player -> x() < 440 - player->getW() - 10)
            player -> setPos(player -> x() + 10, player -> y());
        else if(player -> x() >= 440 - player->getW() - 10)
            player -> setPos(440 - player->getW(), player -> y());
        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{


    if(e -> type() == QEvent::MouseButtonPress){
        Bullet *b = new Bullet;
        b -> MysetPixmap(QPixmap(":/images/bullet1").scaled(5,20));
        b -> setPos(player->x() + player->getW() / 2 + b->pixmap().width(), player->y() - b->pixmap().height());
        b -> connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));



        Bullet *c = new Bullet;
        c -> MysetPixmap(QPixmap(":/images/bullet1").scaled(5,20));
        c -> setPos(player->x() + player->getW() / 2 - 2*c->pixmap().width(), player->y() - c->pixmap().height());
        c -> connect(timer, SIGNAL(timeout()), c, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(c));
    }
}




void MainWindow::on_rapid_fire_clicked()
{
    if(ui -> rapid_fire -> isChecked()){
            Bullet *b = new Bullet;
            b -> MysetPixmap(QPixmap(":/images/bullet1").scaled(5,20));
            b -> setPos(player->x() + player->getW() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
            b -> connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
    }
}
