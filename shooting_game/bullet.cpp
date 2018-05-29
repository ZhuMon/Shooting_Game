#include "bullet.h"

Bullet::Bullet(int who, int speed){
    PorE = who;
    s = speed;
}

Bullet::Bullet(QPixmap Qp, int who, int speed):PorE(who), s(speed){
    this -> MysetPixmap(Qp);
}

void Bullet::fly(int mX, int mY){
    if(PorE == 0)
        this -> setPos(x(), y() - s);
    else if(PorE == 1)
        if(mX != 0 || mY != 0)
            this -> setPos(x() + mX, y() + mY);
        else
            this -> setPos(x(), y() + s);
    if(y() < 20 || y() > 620 || x() < 40 || x() > 440) {
        this->scene()->removeItem(this);
        delete this;
    }
    emit bulletFly(this);
}

void Bullet::MysetPixmap(const QPixmap &pixmap){
    QPixmap Qp;
    Qp = pixmap;

    QMatrix Qm;
    Qm.rotate(180);
    if(PorE == 1){
        Qp = Qp.transformed(Qm);
    }

    this -> setPixmap(Qp);
}

int Bullet::whoShot(){
    return PorE;
}

int Bullet::getSpeed(){
    return s;
}
