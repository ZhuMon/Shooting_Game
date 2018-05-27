#include "bullet.h"

Bullet::Bullet(int who, int speed){
    PorE = who;
    s = speed;
}

Bullet::Bullet(QPixmap Qp, int who, int speed):PorE(who), s(speed){
    this -> MysetPixmap(Qp);
}

void Bullet::fly(){
    if(PorE == 0)
        this -> setPos(x(), y() - s);
    else if(PorE == 1)
        this -> setPos(x(), y() + s);
    if(y() < 0) {
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
