#include "player.h"

Player::Player()
{

    setImage(QPixmap(":/images/player"), 50.0);

    setPos(200, 500);
    X0 = 200;
    Y0 = 500;
    initHP = HP = 5;


}

void Player::myMove(int x, int y){
    if(this->y() + y > 20 && this->y() + y < 620){
        setY(this->y() + y);
    }
    if(this->x() + x > 40 && this->x() + x < 440) {
        setX(this->x() + x);
    }
}

void Player::damage(int point){
    HP -= point;
}
