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


void Character::setImage(const QPixmap &Qp, float w){

    if(Qp.isNull() == false){
        width = Qp.width();
        height = Qp.height();

        setScale(w/width); //w*?
        height = height * (w/width);
        width = w;
        setPixmap(Qp);
    } else { //is gif
        //QPixmap qq = Qp;
        //qq.scaled(width, height);
        setPixmap(Qp);
    }



}

void Character::initial(){
    setPos(X0, Y0);
    HP = initHP;
}

