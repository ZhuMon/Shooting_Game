#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMovie>
//#include <QSignalMapper>
#include <QtMath>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(40,20, 400, 600)),
    timer(new QTimer),timerRF(new QTimer),timerES(new QTimer),

    enemy_move_cycle(0),
    bullet_move_cycle(0),
    doubleShotState(0),
    level(1),
    passlevel(5),
    stopState(true),
    smoothTimes(0)

    //levelmode(new QVBoxLayout(parent))
{
    ui -> setupUi(this);
    ui -> graphicsView -> setScene(scene);

    player = new Player();
    enemy = new Enemy(this); // so the HP can flow on scene
    static_cast<Enemy *>(enemy) -> setHPvisible(false);

    player -> skill = new QGraphicsPixmapItem();


    timer -> start(10);
    timerRF -> start(100);
    timerES -> start(1000);

    ui -> hp1 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    ui -> hp2 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    ui -> hp3 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    ui -> hp4 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    ui -> hp5 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));


    QToolBar *toolbar = new QToolBar(this);


    levelAction = new QAction(tr("&Level..."), this);
    playAction = new QAction(tr("&Play..."), this);

    levelAction -> setStatusTip(tr("level"));
    playAction -> setStatusTip(tr("play"));

    connect(levelAction, SIGNAL(triggered(bool)), this, SLOT(tolevelMode()));
    connect(playAction, SIGNAL(triggered(bool)), this, SLOT(toplayMode()));

    toolbar -> addAction(levelAction);
    toolbar -> addAction(playAction);
    //ui -> mainToolBar -> addAction(levelAction);
    //ui -> mainToolBar -> addAction(playAction);
    //ui -> mainToolBar = toolbar;
    this->addToolBar(toolbar);

    ui -> doubleshot -> setStatusTip("Shot two bullets each time ");
    ui -> heal -> setStatusTip("HP + 1");
    ui -> rapidfire -> setStatusTip("Shot continuously");

    statusBar() ;

    ui -> pause -> setVisible(false);

    QIcon icon, icon1, icon2, icon3;
    icon.addPixmap(QPixmap(":/images/doublebullet"));
    ui -> doubleshot -> setIcon(icon);
    ui -> doubleshot -> setIconSize(QSize(50, 50));

    icon1.addPixmap(QPixmap(":/images/heal"));
    ui -> heal -> setIcon(icon1);
    ui -> heal -> setIconSize(QSize(50,50));

    icon2.addPixmap(QPixmap(":/images/rapidfire"));
    ui -> rapidfire -> setIcon(icon2);
    ui -> rapidfire -> setIconSize(QSize(50,50));

    icon3.addPixmap(QPixmap(":/images/smoothAll"));
    ui -> smoothAll -> setIcon(icon3);
    ui -> smoothAll -> setIconSize(QSize(50,50));

    QPalette pal;
    pal.setColor(QPalette::Highlight,Qt::gray);
    ui -> doubleshot_cd -> setPalette(pal);
    ui -> heal_cd -> setPalette(pal);
    ui -> rapidfire_cd -> setPalette(pal);

    ui -> doubleshot_cd -> setValue(0);
    ui -> doubleshot -> setEnabled(false);

    ui -> heal_cd -> setValue(0);
    ui -> heal -> setEnabled(false);

    ui -> rapidfire_cd -> setValue(0);
    ui -> rapidfire -> setEnabled(false);

    ui -> gameover -> setAlignment(Qt::AlignHCenter);

    ui -> level -> setText("Level " + QString::number(level));


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
            //b -> setPos(player->x() + player->getW() / 2 + b->pixmap().width(), player->y() - b->pixmap().height());
            if(doubleShotState > 0)
                b -> MysetPos(player, 11);
            else
                b -> MysetPos(player, 12);
            b -> connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
            connect(b, SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(b));


            if(doubleShotState > 0){
                Bullet *c = new Bullet;
                c -> MysetPixmap(QPixmap(":/images/bullet1").scaled(5,20));
                //c -> setPos(player->x() + player->getW() / 2 - 2*c->pixmap().width(), player->y() - c->pixmap().height());
                c -> MysetPos(player, 1);
                c -> connect(timer, SIGNAL(timeout()), c, SLOT(fly()));
                connect(c, SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
                scene->addItem(static_cast<QGraphicsPixmapItem*>(c));
            }
        }
    } else {
        e -> ignore();
    }
}

void MainWindow::checkHP(){


    /*ui -> hp1 -> setVisible(0);
    ui -> hp2 -> setVisible(0);
    ui -> hp3 -> setVisible(0);
    ui -> hp4 -> setVisible(0);
    ui -> hp5 -> setVisible(0);
*/
    ui -> hp1 -> setPixmap(QPixmap(":/images/empty").scaled(30,30));
    ui -> hp2 -> setPixmap(QPixmap(":/images/empty").scaled(30,30));
    ui -> hp3 -> setPixmap(QPixmap(":/images/empty").scaled(30,30));
    ui -> hp4 -> setPixmap(QPixmap(":/images/empty").scaled(30,30));
    ui -> hp5 -> setPixmap(QPixmap(":/images/empty").scaled(30,30));

    switch(player->getHp()){
    case 5:ui -> hp5 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    case 4:ui -> hp4 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    case 3:ui -> hp3 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    case 2:ui -> hp2 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
    case 1:ui -> hp1 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
        break;
    default:if(player->getHp() > 5){
            ui -> hp5 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
            ui -> hp4 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
            ui -> hp3 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
            ui -> hp2 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));
            ui -> hp1 -> setPixmap(QPixmap(":/images/playerHP").scaled(30,30));

        }
    }

    if(player -> getHp() <= 0){
        ui -> gameover -> setText("GameOver");
        on_stop_clicked();
    }
    if(enemy -> getHp() <= 0){
        ui -> gameover -> setText("You Win");

        if(level > passlevel){
            passlevel++;
        }
        on_stop_clicked();
        /*QPushButton *nextlevel = new QPushButton("next level", this);
        nextlevel -> setFixedWidth(100);
        ui -> levelMode -> addWidget(nextlevel);
        connect(nextlevel, &QPushButton::pressed, this, &MainWindow::tolevelMode);
*/
    }
    for(int i = 0; i < small_enemy.size(); ++i){
        if(small_enemy[i]->getHp() <= 0 && small_enemy[i]->getHp() > -10){
            scene->removeItem(small_enemy[i]);
            small_enemy[i]->damage(20); //force hp to <-10 then it will not do "hit" & "remove"
            static_cast<Enemy*>(small_enemy[i]) ->setHPvisible(false);
            static_cast<Enemy*>(small_enemy[i]) ->setGifvisible(false);
        }
    }

}

void MainWindow::hit(Bullet *b){
    if(b->whoShot() == 0){ //player shot the bullet
        if(b->x() >= enemy->x() && b->x() + b->pixmap().width() <= enemy->x() + enemy->getW() &&
            b->y() <= enemy->y() + enemy->getH() && b->y() >= enemy->y()){
            enemy -> damage(1);

            if(level == 5){
                Bullet *c;
                c = new Bullet(QPixmap(":/images/bullet1").scaled(5, 20), 1);
                c -> setPos(b -> x(), b -> y());
                c -> connect(this, SIGNAL(bullet_track(int, int)), c, SLOT(fly(int,int)));
                connect(c, SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
                scene->addItem(static_cast<QGraphicsPixmapItem*>(c));

            }
            scene -> removeItem(b);
            delete b;
            return;
        }
        for(int i = 0; i < small_enemy.size(); ++i){
            if(b -> x() >= small_enemy[i]->x() &&
                    b->x() + b->pixmap().width() <= small_enemy[i]->x() + small_enemy[i]->getW() &&
                    b->y() <= small_enemy[i]->y() + small_enemy[i]->getH() &&
                    b->y() >= small_enemy[i]->y() &&
                    small_enemy[i]->getHp()>0){
                small_enemy[i] -> damage(1);
                scene -> removeItem(b);
                delete b;
                return;
            }
        }

    } else if(b -> whoShot() == 1){ //enemy shot
        int b_head_x = b -> x() + b->pixmap().width()/2;
        int b_head_y = b -> y() + b->pixmap().height();

        if(b_head_x >= player -> x() && b_head_x <= player -> x() + player -> getW() &&
                b_head_y >= player -> y() && b_head_y <= player -> y() + player -> getH()){
            player -> damage(1);
            scene -> removeItem(b);
            delete b;
        } else if(b_head_x >= player -> skill -> x() &&
                  b_head_x <= player -> skill -> x() + player -> skill -> pixmap().width() &&
                  b_head_y >= player -> skill -> y() &&
                  b_head_y <= player -> skill -> y() + player -> skill -> pixmap().height()){
            scene -> removeItem(b);
            delete b;
        }
    }
}

void MainWindow::on_start_clicked()
{
    scene -> addItem(player);
    scene -> addItem(enemy);
    //scene -> addItem(player -> skill);

    static_cast<Enemy *>(enemy) -> setHPvisible(true);

    enemy -> initial();
    player -> initial();

    ui -> gameover -> setText("");


    connect(timerES, SIGNAL(timeout()), this, SLOT(enemy_shoot()));
    connect(timerRF, SIGNAL(timeout()), this, SLOT(enemy_move()));
    connect(timerRF, SIGNAL(timeout()), this, SLOT(bullet_track_control()));
    connect(timerES, SIGNAL(timeout()), this, SLOT(check_skill_cd()));
    connect(timerRF, SIGNAL(timeout()), this, SLOT(checkHP()));

    stopState = false;

    ui -> start -> setVisible(false); //avoid double click
    ui -> pause -> setVisible(true);  //avoid pause stop resume
    ui -> pause -> setText("pause");

    enemy_move_cycle = 0;

    ui -> doubleshot_cd -> setValue(0);
    ui -> doubleshot -> setEnabled(false);

    ui -> heal_cd -> setValue(0);
    ui -> heal -> setEnabled(false);

    ui -> rapidfire_cd -> setValue(0);
    ui -> rapidfire -> setEnabled(false);

    if(level == 5){
        static_cast<Enemy*>(enemy) -> setGifvisible(true);
    } else if(level == 6){
        for(int i = 0; i < small_enemy.size(); i++){
            scene -> addItem(small_enemy[i]);
            static_cast<Enemy*>(small_enemy[i]) -> setHPvisible(true);
            static_cast<Enemy*>(small_enemy[i]) -> setGifvisible(true);
        }
    }


    scene->addItem(player -> skill);

    smoothTimes = 5;

    ui -> smooth_cd1 -> setPixmap(QPixmap(":/images/bullet2").scaled(10,10));
    ui -> smooth_cd2 -> setPixmap(QPixmap(":/images/bullet2").scaled(10,10));
    ui -> smooth_cd3 -> setPixmap(QPixmap(":/images/bullet2").scaled(10,10));
    ui -> smooth_cd4 -> setPixmap(QPixmap(":/images/bullet2").scaled(10,10));
    ui -> smooth_cd5 -> setPixmap(QPixmap(":/images/bullet2").scaled(10,10));


}

void MainWindow::on_pause_clicked()
{
    if(ui -> pause -> text() == "pause"){
        disconnect(timerES, SIGNAL(timeout()), this, SLOT(enemy_shoot()));
        if(rapidFireState > 0)
            disconnect(timerRF, SIGNAL(timeout()), this, SLOT(player_shoot()));
        disconnect(timerRF, SIGNAL(timeout()), this, SLOT(enemy_move()));
        disconnect(timerRF, SIGNAL(timeout()), this, SLOT(bullet_track_control()));
        disconnect(timerES, SIGNAL(timeout()), this, SLOT(check_skill_cd()));
        disconnect(timerRF, SIGNAL(timeout()), this, SLOT(checkHP()));

        ui -> pause -> setText("resume");
        stopState = true;
    } else if(ui -> pause -> text() == "resume"){
        connect(timerES, SIGNAL(timeout()), this, SLOT(enemy_shoot()));
        if(rapidFireState > 0)
            connect(timerRF, SIGNAL(timeout()), this, SLOT(player_shoot()));
        connect(timerRF, SIGNAL(timeout()), this, SLOT(enemy_move()));
        connect(timerRF, SIGNAL(timeout()), this, SLOT(bullet_track_control()));
        connect(timerES, SIGNAL(timeout()), this, SLOT(check_skill_cd()));
        connect(timerRF, SIGNAL(timeout()), this, SLOT(checkHP()));

        ui -> pause -> setText("pause");
        stopState = false;
    }
}

void MainWindow::enemy_shoot(){
    Bullet *b[12];
    int x[12] = {3, 4, 5, 4, 3, 0, -3, -4, -5, -4, -3, 0};
    int y[12] = {-4, -3, 0, 3, 4, 5, 4, 3, 0, -3, -4, -5};
    if(level == 1){
        b[0] = new Bullet(QPixmap(":/images/bullet2").scaled(25, 25), 1);
        b[0] -> MysetPos(enemy, 6);
        b[0] -> connect(this, SIGNAL(bullet_track(int, int)), b[0], SLOT(fly(int,int)));
        connect(b[0], SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b[0]));

    } else if(level == 2){
        for(int i = 0; i < 2; i++){
            b[i] = new Bullet(QPixmap(":/images/bullet2").scaled(25, 25), 1);
            b[i] -> MysetPos(enemy, 3+6*i);
            b[i] -> connect(this, SIGNAL(bullet_track(int, int)), b[i], SLOT(fly(int,int)));
            connect(b[i], SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(b[i]));
        }

    } else if(level == 3){
        for(int i = 0; i < 12; i++){
            b[i] = new Bullet(QPixmap(":/images/bullet2").scaled(25, 25), 1);
            b[i] -> MysetPos(enemy, 6);
            //b[i] -> setPos(enemy -> x() + enemy -> getW()/2, enemy -> y() + enemy -> getH()/2);
            b[i] -> pX = x[i];
            b[i] -> pY = y[i];
            //b[i] -> connect(timerRF, SIGNAL(timeout()), b[i], SLOT(fly()));
            b[i] -> connect(this, SIGNAL(bullet_track(int, int)), b[i], SLOT(fly(int,int)));
            connect(b[i], SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(b[i]));
        }
    } else if(level == 4){
        for(int i = 0; i < 2; i++){
            b[i] = new Bullet(QPixmap(":/images/bullet2").scaled(25, 25), 1);
            b[i] -> MysetPos(enemy, 5+2*i);
            //b[i] -> pX = x[i];
            //b[i] -> pY = y[i];
            b[i] -> connect(this, SIGNAL(bullet_track(int, int, bool)), b[i], SLOT(fly(int,int, bool)));
            connect(b[i], SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(b[i]));
        }

    } else if(level == 5){
        b[0] = new Bullet(QPixmap(":/images/bullet2").scaled(25, 25), 1);
        b[0] -> MysetPos(enemy, 6);
        b[0] -> connect(this, SIGNAL(bullet_track(int, int)), b[0], SLOT(fly(int,int)));
        connect(b[0], SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b[0]));
    } else if(level == 6){

    } else if(level == 7){

    } else if(level == 8){

    } else if(level == 9){

    }
}

void MainWindow::on_stop_clicked()
{
    disconnect(timerES, SIGNAL(timeout()), this, SLOT(enemy_shoot()));
    if(rapidFireState > 0)
        disconnect(timerRF, SIGNAL(timeout()), this, SLOT(player_shoot()));
    disconnect(timerRF, SIGNAL(timeout()), this, SLOT(enemy_move()));
    disconnect(timerRF, SIGNAL(timeout()), this, SLOT(bullet_track_control()));
    disconnect(timerES, SIGNAL(timeout()), this, SLOT(check_skill_cd()));
    disconnect(timerRF, SIGNAL(timeout()), this, SLOT(checkHP()));
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
    static_cast<Enemy*>(enemy) -> setGifvisible(false);

    ui -> start -> setVisible(true);
    ui -> pause -> setVisible(false); //avoid pause stop resume

    for(int i = 0; i < small_enemy.size(); i++){
        scene -> addItem(small_enemy[i]);
        static_cast<Enemy*>(small_enemy[i]) -> setHPvisible(false);
        static_cast<Enemy*>(small_enemy[i]) -> setGifvisible(false);
    }
}

void MainWindow::enemy_move(){
    enemy_move_cycle++;
    //if(level != 4){
        if(enemy_move_cycle == 100 ){ //10s or stop
            enemy_move_cycle = 0;
            return;
        } else if(enemy_move_cycle < 25) { //2.5s
            enemy->myMove(5,0);
        } else if(enemy_move_cycle < 75) {
            enemy->myMove(-5,0);
        } else if(enemy_move_cycle < 100) {
            enemy->myMove(5,0);
        }

    //}
}

void MainWindow::bullet_track_control(){
    bullet_move_cycle++;
    //int back;
    //back = bullet_move_cycle-100;
    if(bullet_move_cycle == 360){
        bullet_move_cycle = 0;
    }
    if(level == 4){
        double x;
        x = qDegreesToRadians((double)bullet_move_cycle);
        emit bullet_track(qCos(x)*10,qSin(x)*5, true);
        //emit bullet_track(0,0);
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
    } else {
        emit bullet_track(0,0);
    }
}

void MainWindow::tolevelMode(){
    //int i = 0;
    /*while(i < ui -> levelMode -> columnCount()*ui -> levelMode -> rowCount()){
        QWidget* widget = ui -> levelMode -> itemAt(i++) -> widget();
        widget->deleteLater();
    }*/

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

    ui -> gameover -> setText("");

    int i = 0;
    while(i < ui -> levelMode -> columnCount()*ui -> levelMode -> rowCount()){
        QWidget* widget = ui -> levelMode -> itemAt(i++) -> widget();
        widget->deleteLater();
    }

}

void MainWindow::setLevelMode(){
    LevelButton *level[9];
    QFont f;
    f.setPointSize(50);

    for(int i = 0; i < 9; i++){
        level[i] = new LevelButton(i+1, this);
        //level[i] -> setGeometry(100+20*(i%3), 40 + 20*(i/3), 10, 10);
        //QLayoutItem *li = new QLayoutItem();
        level[i] -> setFont(f);
        ui -> levelMode -> addWidget(level[i], i/3, i%3);
                //addWidget(level[i]);
        connect(level[i], SIGNAL(pressed()), level[i], SLOT(MyClicked()));
        connect(level[i], SIGNAL(MyClick(int)), this, SLOT(level_choose(int)));
        if(i > passlevel){
            level[i] -> setEnabled(false);
        }
    }

}

void MainWindow::level_choose(int level){
    this -> level = level;
    QMovie *movie = new QMovie(":/images/bat");

    switch(level){
    case 1:
        enemy->setImage(QPixmap(":/images/boss"), 150);
        break;
    case 2:
        enemy->setImage(QPixmap(":/images/boss2"), 150);
        break;
    case 3:
        enemy->setImage(QPixmap(":/images/boss3"), 150);
        break;
    case 4:
        enemy->setImage(QPixmap(":/images/boss"), 150);
        break;
    case 5:
        //enemy->setImage(QPixmap(":/images/boss3"), 150);
        static_cast<Enemy*>(enemy) -> setGif(movie,150,195/2.5);
        enemy->setImage(QPixmap(),150);
        static_cast<Enemy*>(enemy) -> setGifvisible(false);
        break;
    case 6:

        enemy->setImage(QPixmap(":/images/boss"), 150);
        if(small_enemy.size() < 1)
            small_enemy.append(new Enemy(this));
        static_cast<Enemy*>(small_enemy[0]) -> setGif(movie,75,195/5);
        static_cast<Enemy*>(small_enemy[0]) -> initial(300,300,75,30,QPixmap());

        break;
    }
    toplayMode();
    ui -> level -> setText("Level " + QString::number(level));
}

void MainWindow::check_skill_cd(){
    //skill_cd_cycle++;

    QPalette pal;
    if(doubleShotState == 5){
        doubleShotState = 0;
    } else if(doubleShotState > 0){
        doubleShotState += 1;
    } else if(ui -> doubleshot_cd -> value() < 20){ //cd = 20s
        ui -> doubleshot_cd -> setValue(ui -> doubleshot_cd -> value() + 1);
        pal.setColor(QPalette::Highlight,Qt::gray);
        ui -> doubleshot_cd -> setPalette(pal);
    } else {
        ui -> doubleshot -> setEnabled(true);
        pal.setColor(QPalette::Highlight,Qt::blue);
        ui -> doubleshot_cd -> setPalette(pal);
    }

    if(ui -> heal_cd -> value() < 40){
        ui -> heal_cd-> setValue(ui -> heal_cd -> value() + 1);
        pal.setColor(QPalette::Highlight,Qt::gray);
        ui -> heal_cd -> setPalette(pal);
    } else {
        ui -> heal -> setEnabled(true);
        pal.setColor(QPalette::Highlight,Qt::green);
        ui -> heal_cd -> setPalette(pal);
    }

    if(rapidFireState == 3){
        rapidFireState = 0;
        disconnect(timerRF, SIGNAL(timeout()), this, SLOT(player_shoot()));
    } else if(rapidFireState > 0){
        rapidFireState += 1;
    } else if(ui -> rapidfire_cd -> value() < 30){
        ui -> rapidfire_cd-> setValue(ui -> rapidfire_cd -> value() + 1);
        pal.setColor(QPalette::Highlight,Qt::gray);
        ui -> rapidfire_cd -> setPalette(pal);
    } else {
        ui -> rapidfire -> setEnabled(true);
        pal.setColor(QPalette::Highlight,Qt::red);
        ui -> rapidfire_cd -> setPalette(pal);
    }

    switch(smoothTimes){
    case 0:ui -> smooth_cd1 -> setPixmap(QPixmap(":/images/bullet3").scaled(10,10));
            ui -> smoothAll -> setEnabled(false);
    case 1:ui -> smooth_cd2 -> setPixmap(QPixmap(":/images/bullet3").scaled(10,10));
    case 2:ui -> smooth_cd3 -> setPixmap(QPixmap(":/images/bullet3").scaled(10,10));
    case 3:ui -> smooth_cd4 -> setPixmap(QPixmap(":/images/bullet3").scaled(10,10));
    case 4:ui -> smooth_cd5 -> setPixmap(QPixmap(":/images/bullet3").scaled(10,10));
          break;
    case 5:ui -> smooth_cd5 -> setPixmap(QPixmap(":/images/bullet2").scaled(10,10));
        ui -> smooth_cd4 -> setPixmap(QPixmap(":/images/bullet2").scaled(10,10));
        ui -> smooth_cd3 -> setPixmap(QPixmap(":/images/bullet2").scaled(10,10));
        ui -> smooth_cd2 -> setPixmap(QPixmap(":/images/bullet2").scaled(10,10));
        ui -> smooth_cd1 -> setPixmap(QPixmap(":/images/bullet2").scaled(10,10));
        ui -> smoothAll -> setEnabled(true);
    }
}

void MainWindow::on_doubleshot_clicked()
{
    doubleShotState = 1;
    ui -> doubleshot_cd -> setValue(0);
    ui -> doubleshot -> setEnabled(false);

}

void MainWindow::on_heal_clicked()
{
    player -> recover(1);
    ui -> heal -> setEnabled(false);
    ui -> heal_cd -> setValue(0);

}

void MainWindow::player_shoot()
{

    if(rapidFireState > 0){
        Bullet *b = new Bullet;
        b -> MysetPixmap(QPixmap(":/images/bullet1").scaled(5,20));
        //b -> setPos(player->x() + player->getW() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
        b -> MysetPos(player, 12);
        b -> connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
        connect(b, SIGNAL(bulletFly(Bullet*)), this, SLOT(hit(Bullet*)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
    }
}

void MainWindow::on_rapidfire_clicked()
{

    rapidFireState = 1;
    ui -> rapidfire -> setEnabled(false);
    connect(timerRF, SIGNAL(timeout()), this, SLOT(player_shoot()));
    ui -> rapidfire_cd -> setValue(0);
}

void MainWindow::on_smoothAll_clicked()
{
    //if times > 0
    player -> skill -> setPixmap(QPixmap(":/images/smoothAll").scaled(player->getH(),player -> getH()));

    player -> skill -> setPos(player -> x(), player -> y());
    smoothTimes--;


    connect(timerRF, SIGNAL(timeout()), this, SLOT(circle_wave_emit()));
}

void MainWindow::circle_wave_emit(){
    if(player -> skill -> y() > 20){
        //player -> skill -> setScale((player -> skill -> pixmap().width()+20)/(double)player->skill -> pixmap().width());
        //player -> skill -> pixmap().scaled(player -> skill -> pixmap().width()+20, player -> skill -> pixmap().height()+20);
        player -> skill -> setPixmap(QPixmap(":/images/smoothAll").scaled(player -> skill -> pixmap().width()+20, player -> skill -> pixmap().height()+20));
        player -> skill -> setPos(player -> skill -> x() - 10, player -> skill -> y() -10);
        player -> skill -> setVisible(true);
    } else {
        player -> skill -> setPixmap(QPixmap());
        // has bug
        //scene->removeItem(player -> skill);
        player -> skill -> setVisible(false);
        disconnect(timerRF, SIGNAL(timeout()), this, SLOT(circle_wave_emit()));

    }
}

void MainWindow::on_supertime_clicked()
{
    ui -> doubleshot_cd -> setValue(ui -> doubleshot_cd ->maximum());
    ui -> heal_cd -> setValue(ui -> heal_cd ->maximum());
    ui -> rapidfire_cd -> setValue(ui -> rapidfire_cd ->maximum());

}
