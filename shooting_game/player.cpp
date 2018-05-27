#include "player.h"

Player::Player()
{

    setImage(QPixmap(":/images/player"), 50.0);



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

void Player::setImage(const QPixmap &Qp, float w){

    width = Qp.width();
    height = Qp.height();

    setScale(w/width); //50*?
    setPixmap(Qp);
    setPos(200, 500);


    height = height * (w/width);
    width = w;
}
