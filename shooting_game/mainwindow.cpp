#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMovie>
#include <QSignalMapper>
#include <QtMath>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(40,20, 400, 600)),
    timer(new QTimer),timerRF(new QTimer),timerES(new QTimer),

    player(new Player),
    //enemy(new Enemy(this)),
    enemy_move_cycle(0),
    bullet_move_cycle(0)
    //levelmode(new QVBoxLayout(parent))
{
    ui -> setupUi(this);
    ui -> graphicsView -> setScene(scene);

    enemy = new Enemy(this); // so the HP can flow on scene
    static_cast<Enemy *>(enemy) -> setHPvisible(false);

    timer -> start(10);
    timerRF -> start(100);
    timerES -> start(1000);

    ui -> hp1 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    ui -> hp2 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    ui -> hp3 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    ui -> hp4 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    ui -> hp5 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));

    connect(timerRF, SIGNAL(timeout()), this, SLOT(checkHP()));
    //QLabel label;
    QMovie *movie = new QMovie(":/images/bat");
    //label.setMovie(movie);
    movie ->setScaledSize(QSize(200,160));
    ui -> boss -> setMovie(movie);

    movie -> start();
    ui -> boss ->setGeometry(150,200, 200, 80);

    levelAction = new QAction(tr("&Level..."), this);
    playAction = new QAction(tr("&Play..."), this);

    levelAction -> setStatusTip(tr("level"));
    playAction -> setStatusTip(tr("play"));

    connect(levelAction, &QAction::triggered, this, &MainWindow::tolevelMode);
    connect(playAction, &QAction::triggered, this, &MainWindow::toplayMode);

    ui -> mainToolBar -> addAction(levelAction);
    ui -> mainToolBar -> addAction(playAction);
    statusBar() ;

    ui -> pause -> setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    //border:x:40-440 y:20-620
    if(stopState == false){
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
    } else {
        e -> ignore();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(stopState == false){
        if(e -> type() == QEvent::MouseButtonPress){
            Bullet *b = new Bullet;
            b -> MysetPixmap(QPixmap(":/images/bullet1").scaled(5,20));
            b -> setPos(player->x() + player->getW() / 2 + b->pixmap().width(), player->y() - b->pixmap().height());
            b -> connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
            connect(b, SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(b));



            Bullet *c = new Bullet;
            c -> MysetPixmap(QPixmap(":/images/bullet1").scaled(5,20));
            c -> setPos(player->x() + player->getW() / 2 - 2*c->pixmap().width(), player->y() - c->pixmap().height());
            c -> connect(timer, SIGNAL(timeout()), c, SLOT(fly()));
            connect(c, SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(c));
        }
    } else {
        e -> ignore();
    }
}




void MainWindow::on_rapid_fire_clicked()
{
    if(ui -> rapid_fire -> isChecked()){
        Bullet *b = new Bullet;
        b -> MysetPixmap(QPixmap(":/images/bullet1").scaled(5,20));
        b -> setPos(player->x() + player->getW() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
        b -> connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
        connect(b, SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
    }
}

void MainWindow::checkHP(){


    ui -> hp1 -> setVisible(0);
    ui -> hp2 -> setVisible(0);
    ui -> hp3 -> setVisible(0);
    ui -> hp4 -> setVisible(0);
    ui -> hp5 -> setVisible(0);

    switch(player->getHp()){
    case 5:ui -> hp5 -> setVisible(1);
    case 4:ui -> hp4 -> setVisible(1);
    case 3:ui -> hp3 -> setVisible(1);
    case 2:ui -> hp2 -> setVisible(1);
    case 1:ui -> hp1 -> setVisible(1);
        break;
    }

    if(player -> getHp() <= 0){
        ui -> gameover -> setText("GameOver");
        on_stop_clicked();
    }
    if(enemy -> getHp() <= 0){
        ui -> gameover -> setText(" You Win");
        on_stop_clicked();
    }

}

void MainWindow::hit(Bullet *b){
    if(b->whoShot() == 0){ //player shot the bullet
        if(b->x() >= enemy->x() && b->x() + b->pixmap().width() <= enemy->x() + enemy->getW() &&
            b->y() <= enemy->y() + enemy->getH() && b->y() >= enemy->y()){
            enemy -> damage(1);
            scene -> removeItem(b);
            delete b;
        }

    } else if(b -> whoShot() == 1){
        int b_head_x = b -> x() + b->pixmap().width()/2;
        int b_head_y = b -> y() + b->pixmap().height();
        if(b_head_x >= player -> x() && b_head_x <= player -> x() + player -> getW() &&
                b_head_y >= player -> y() && b_head_y <= player -> y() + player -> getH()){
            player -> damage(1);
            scene -> removeItem(b);
            delete b;
        }
    }
}

void MainWindow::on_start_clicked()
{
    scene -> addItem(player);
    scene -> addItem(enemy);

    static_cast<Enemy *>(enemy) -> setHPvisible(true);

    enemy -> initial();
    player -> initial();

    ui -> gameover -> setText("");


    connect(timerES, SIGNAL(timeout()), this, SLOT(enemy_shoot()));
    connect(timerRF, SIGNAL(timeout()), this, SLOT(on_rapid_fire_clicked()));
    connect(timerRF, SIGNAL(timeout()), this, SLOT(enemy_move()));
    connect(timerRF, SIGNAL(timeout()), this, SLOT(bullet_track_control()));
    stopState = false;

    ui -> start -> setVisible(false); //avoid double click
    ui -> pause -> setVisible(true);  //avoid pause stop resume
    ui -> pause -> setText("pause");

    enemy_move_cycle = 0;
}

void MainWindow::on_pause_clicked()
{
    if(ui -> pause -> text() == "pause"){
        disconnect(timerES, SIGNAL(timeout()), this, SLOT(enemy_shoot()));
        disconnect(timerRF, SIGNAL(timeout()), this, SLOT(on_rapid_fire_clicked()));
        disconnect(timerRF, SIGNAL(timeout()), this, SLOT(enemy_move()));
        disconnect(timerRF, SIGNAL(timeout()), this, SLOT(bullet_track_control()));
        ui -> pause -> setText("resume");
        stopState = true;
    } else if(ui -> pause -> text() == "resume"){
        connect(timerES, SIGNAL(timeout()), this, SLOT(enemy_shoot()));
        connect(timerRF, SIGNAL(timeout()), this, SLOT(on_rapid_fire_clicked()));
        connect(timerRF, SIGNAL(timeout()), this, SLOT(enemy_move()));
        connect(timerRF, SIGNAL(timeout()), this, SLOT(bullet_track_control()));
        ui -> pause -> setText("pause");
        stopState = false;
    }
}

void MainWindow::enemy_shoot(){
    Bullet *b[12];
    int x[12] = {3, 4, 5, 4, 3, 0, -3, -4, -5, -4, -3, 0};
    int y[12] = {-4, -3, 0, 3, 4, 5, 4, 3, 0, -3, -4, -5};
    for(int i = 0; i < 12; i++){
        b[i] = new Bullet(QPixmap(":/images/bullet2").scaled(25, 25), 1, 1);
        //b[i] -> MysetPos(enemy, 6);
        b[i] -> setPos(enemy -> x() + enemy -> getW()/2, enemy -> y() + enemy -> getH()/2);
        b[i] -> pX = x[i];
        b[i] -> pY = y[i];
        //b[i] -> connect(timerRF, SIGNAL(timeout()), b[i], SLOT(fly()));
        b[i] -> connect(this, SIGNAL(bullet_track(int, int)), b[i], SLOT(fly(int,int)));
        connect(b[i], SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b[i]));
    }

}

void MainWindow::on_stop_clicked()
{
    disconnect(timerES, SIGNAL(timeout()), this, SLOT(enemy_shoot()));
    disconnect(timerRF, SIGNAL(timeout()), this, SLOT(on_rapid_fire_clicked()));
    disconnect(timerRF, SIGNAL(timeout()), this, SLOT(enemy_move()));
    disconnect(timerRF, SIGNAL(timeout()), this, SLOT(bullet_track_control()));
    stopState = true;
    //QList list(scene -> items());
    //list = scene -> items();

    int i;
    while(scene->items().size() != 0){
        for(i = 0; i < scene ->items().size(); i++){
            //QGraphicsItem const *gpi = scene -> items().at(i);

            scene -> items().at(i) -> setPos(0,0);
            scene -> removeItem(scene -> items().at(i));
        }
    }

    static_cast<Enemy *>(enemy) -> setHPvisible(false);

    ui -> start -> setVisible(true);
    ui -> pause -> setVisible(false); //avoid pause stop resume
}

void MainWindow::enemy_move(){
    enemy_move_cycle++;
    if(enemy_move_cycle == 100 ){ //10s or stop
        enemy_move_cycle = 0;
        return;
    } else if(enemy_move_cycle < 25) { //2.5s
        enemy->myMove(5,0);
        //enemy->setPos(enemy->x() + 5, enemy-> y());
        ui -> boss ->setGeometry(ui -> boss -> x() + 10, ui -> boss -> y(), ui -> boss ->width(), ui -> boss -> height());
    } else if(enemy_move_cycle < 75) {
        enemy->myMove(-5,0);
        //enemy->setPos(enemy->x() - 5, enemy->y());
        ui -> boss ->setGeometry(ui -> boss -> x() - 10, ui -> boss -> y(), ui -> boss ->width(), ui -> boss -> height());
    } else if(enemy_move_cycle < 100) {
        enemy->myMove(5,0);
        //enemy->setPos(enemy->x() + 5, enemy->y());
        ui -> boss ->setGeometry(ui -> boss -> x() + 10, ui -> boss -> y(), ui -> boss ->width(), ui -> boss -> height());
    }


}

void MainWindow::bullet_track_control(){
    bullet_move_cycle++;
    //int back;
    //back = bullet_move_cycle-100;
    emit bullet_track(0,0);
    /*if(bullet_move_cycle < 50){
        //back = 360 - bullet_move_cycle;
        //double x;//, y;
        //x = qDegreesToRadians((double)bullet_move_cycle);
        //y = qDegreesToRadians((double)bullet_move_cycle);
        emit bullet_track(0,5);
    } else if(bullet_move_cycle < 70){
        //double x;//, y;
        //x = qDegreesToRadians((double)back);
        //y = qDegreesToRadians((double)bullet_move_cycle);
        //emit bullet_track(qCos(x)*10,qSin(x)*10);
        emit bullet_track(0, 0);
    } else if(bullet_move_cycle < 100){
        emit bullet_track(0,5);
    } else if(bullet_move_cycle < 120){
        emit bullet_track(0,0);
    } else if(bullet_move_cycle < 200){
        emit bullet_track(0,5);
    } else if(bullet_move_cycle < 220){
        emit bullet_track(0,0);
    } else if(bullet_move_cycle < 360){
        emit bullet_track(0,5);
    } else if(bullet_move_cycle == 360){
        bullet_move_cycle = 0;
    }*/
}

void MainWindow::tolevelMode(){
    //levelmode -> setVisible(true);
    //ui ->player_status -> setVisible(false);
    ui ->boss->setVisible(false);
    ui ->gameover->setVisible(false);
    ui ->graphicsView->setVisible(false);
    ui ->gridLayoutWidget->setVisible(false);  //player_status
    ui ->gridLayoutWidget_2->setVisible(true); //level
    //ui ->player_status->setEnabled(false);
    //static_cast<Enemy *>(enemy) -> setHPvisible(false);

    setLevelMode();
    on_stop_clicked();
}

void MainWindow::toplayMode(){

    ui ->boss->setVisible(true);
    ui ->gameover->setVisible(true);
    ui ->graphicsView->setVisible(true);
    ui ->gridLayoutWidget->setVisible(true);
    ui ->gridLayoutWidget_2->setVisible(false);


    int i = 0;
    while(i < ui -> levelMode -> columnCount()*ui -> levelMode -> rowCount()){
        QWidget* widget = ui -> levelMode -> itemAt(i++) -> widget();
        widget->deleteLater();
    }
}

void MainWindow::setLevelMode(){
    QPushButton *level[9];

    for(int i = 0; i < 9; i++){
        level[i] = new QPushButton(QString::number(i+1), this);
        //level[i] -> setGeometry(100+20*(i%3), 40 + 20*(i/3), 10, 10);
        level[i] -> setFixedHeight(100);
        level[i] -> setFixedWidth(100);
        //QLayoutItem *li = new QLayoutItem();

        ui -> levelMode -> addWidget(level[i], i/3, i%3);
                //addWidget(level[i]);
    }

    QRect rect;
    rect.setHeight(100);
    rect.setWidth(100);
    rect.setX(0);
    rect.setY(0);
    //levelmode->setGeometry(rect);


}


