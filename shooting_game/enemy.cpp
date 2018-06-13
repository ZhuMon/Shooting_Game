#include "enemy.h"
#include <QMovie>
#include <QPixmap>
#include <QProgressBar>
#include <QLabel>


Enemy::Enemy(QWidget *parent)
{
    this -> parent = parent;
    setImage(QPixmap(":/images/boss"), 150);
    //setMovie(QMovie(":/images/bossgif"));
    setPos(150, 50);
    X0 = 150;
    Y0 = 50;

    HPpercent = new QProgressBar(parent);
    HPpercent -> setGeometry(150,70, 150, 10);
    //HPpercent -> setVisible(true);
    HPpercent -> setValue(100);

    QPalette pal;
    pal.setColor(QPalette::Highlight,Qt::red);
    HPpercent -> setPalette(pal);

    initHP = HP = 100;

    label = new QLabel(parent);

}

void Enemy::myMove(int x, int y){
    if(this->y() + y > 20 && this->y() + y < 620){
        setY(this->y() + y);
        HPpercent ->setGeometry(HPpercent->x(), HPpercent->y()+y, HPpercent->width(), HPpercent->height());
        label -> setGeometry(this -> x(), this -> y() + 35 + y, width, height);
    }
    if(this->x() + x > 40 && this->x() + x < 440) {
        setX(this->x() + x);
        HPpercent ->setGeometry(HPpercent->x()+x, HPpercent->y(), HPpercent->width(), HPpercent->height());
        label -> setGeometry(this -> x() + x, this -> y() + 35, width, height);
    }

}

void Enemy::damage(int point){
    HP -= point;
    HPpercent -> setValue(HP);
}

void Enemy::recover(int point){
    HP += point;
    HPpercent -> setValue(HP);
}

void Enemy::setHPvisible(bool visible){
    this -> HPpercent -> setVisible(visible);
    //w-> setVisible(false);
}

void Enemy::initial(){
    setPos(X0, Y0);
    this ->HP = initHP;
    HPpercent -> setGeometry(X0,Y0+20, width, 10);
    HPpercent -> setValue(initHP);
    HPpercent -> setMaximum(initHP);

    label ->setGeometry(X0, Y0+35, width, height);
}
void Enemy::initial(int x, int y, int w, int HP, const QPixmap& qp){
    X0 = x;
    Y0 = y;

    initHP = HP;
    setImage(qp, w);

    initial();
}

void Enemy::setGif(QMovie *movie, int w, int h){



    //QMovie *movie1 = new QMovie(":/images/bat");
    movie -> setParent(label);
    movie -> setScaledSize(QSize(w,h));
    movie -> start();
    label -> setMovie(movie);

    label ->setGeometry(X0, Y0+35, w, h);
    width = w;
    height = h;
}

void Enemy::setGifvisible(bool visible){
    label -> setVisible(visible);
}

