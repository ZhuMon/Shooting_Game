#include "enemy.h"
#include <QMovie>
#include <QPixmap>
#include <QProgressBar>
#include <QLabel>


Enemy::Enemy(QWidget *parent)
{
    w = parent;
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

    label = new QLabel(w);

}

void Enemy::myMove(int x, int y){
    if(this->y() + y > 20 && this->y() + y < 620){
        setY(this->y() + y);
        HPpercent ->setGeometry(HPpercent->x(), HPpercent->y()+y, HPpercent->width(), HPpercent->height());
    }
    if(this->x() + x > 40 && this->x() + x < 440) {
        setX(this->x() + x);
        HPpercent ->setGeometry(HPpercent->x()+x, HPpercent->y(), HPpercent->width(), HPpercent->height());
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
    HP = initHP;
    HPpercent -> setGeometry(150,70, 150, 10);
    HPpercent -> setValue(100);
}

void Enemy::setGif(QMovie *movie){



    //QMovie *movie1 = new QMovie(":/images/bat");
    movie -> setParent(label);
    movie -> setScaledSize(QSize(width,height));
    movie -> start();
    label -> setMovie(movie);

    label ->setGeometry(X0, Y0, width, height);
}
