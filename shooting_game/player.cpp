#include "player.h"

Player::Player()
{
    QPixmap Qp(":/images/player");
    this -> setPixmap(Qp);
    this -> setPos(200, 500);


    width = Qp.width();
    height = Qp.height();

    this -> setScale(50.0/width); //50*?

    height = height * (50.0/width);
    width = 50;

    HP = 5;
}

int Player::getH(){
    return height;
}

int Player::getW(){
    return width;
}

int Player::getHp(){
    return HP;
}
void Player::recover(int point){
    HP+=point;
}
void Player::damage(int point){
    HP-=point;
}
