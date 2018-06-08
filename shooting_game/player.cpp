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

}

void Player::damage(int point){
    HP -= point;
}
