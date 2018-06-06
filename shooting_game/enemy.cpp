#include "enemy.h"
#include <QMovie>
#include <QPixmap>
#include <QProgressBar>


Enemy::Enemy(QWidget *parent)
{

    setImage(QPixmap(":/images/boss"), 150);
    //setMovie(QMovie(":/images/bossgif"));
    setPos(150, 50);


    HPpercent = new QProgressBar(parent);
    HPpercent -> setGeometry(150,70, 150, 10);
    //HPpercent -> setVisible(true);
    HPpercent -> setValue(100);
    QPalette pal;
    pal.setColor(QPalette::Highlight,Qt::red);
    HPpercent -> setPalette(pal);
    HP = 100;


}

void Enemy::myMove(int x, int y){
    setPos(this -> x() + x, this -> y() + y);
    HPpercent ->setGeometry(HPpercent->x()+x, HPpercent->y()+y, HPpercent->width(), HPpercent->height());
}

void Enemy::damage(int point){
    HP -= point;
    HPpercent -> setValue(HP);
}

void Enemy::recover(int point){
    HP += point;
    HPpercent -> setValue(HP);
}

