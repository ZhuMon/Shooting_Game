#include "bullet.h"

Bullet::Bullet(int who){
    PorE = who;
}

Bullet::Bullet(QPixmap Qp, int who):PorE(who){
    this -> MysetPixmap(Qp);
}

void Bullet::fly(int speed){
    this -> setPos(x(), y() - speed);
    if(y() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
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
