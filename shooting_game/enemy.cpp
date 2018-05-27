#include "enemy.h"
#include <QMovie>
#include <QPixmap>

Enemy::Enemy()
{

    setImage(QPixmap(":/images/boss"), 150);
    setPos(150, 50);


}
