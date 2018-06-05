#include "character.h"

Character::Character()
{

}
int Character::getH(){
    return height;
}

int Character::getW(){
    return width;
}

int Character::getHp(){
    return HP;
}
void Character::recover(int point){
    HP+=point;
}
void Character::damage(int point){
    HP-=point;
}

void Character::setImage(const QPixmap &Qp, float w){

    width = Qp.width();
    height = Qp.height();

    setScale(w/width); //50*?
    setPixmap(Qp);
    setPos(200, 500);


    height = height * (w/width);
    width = w;
}
