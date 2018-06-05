#include "enemy.h"
#include <QMovie>
#include <QPixmap>

Enemy::Enemy()
{

    setImage(QPixmap(":/images/boss"), 150);
    //setMovie(QMovie(":/images/bossgif"));
    setPos(150, 50);

    HP = 100;
}




