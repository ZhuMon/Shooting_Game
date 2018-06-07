#include "bullet.h"

Bullet::Bullet(int who, int speed, int dx, int dy){
    PorE = who;
    s = speed;
    pX = dx;
    pY = dy;
}

Bullet::Bullet(QPixmap Qp, int who, int speed, int dx, int dy):
    PorE(who),
    s(speed),
    pX(dx), pY(dy){
    this -> MysetPixmap(Qp);
}

void Bullet::fly(int mX, int mY){
    if(PorE == 0)
        this -> setPos(x(), y() - s);
    else if(PorE == 1)
        if(mX != 0 || mY != 0)
            this -> setPos(x() + mX, y() + mY);
        else
            this -> setPos(x() + pX, y() + s + pY);
    if(y() < 20 || y() > 620 || x() < 40 || x() > 440) {

        //scene() -> addItem(this);
        scene() -> removeItem(this);

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

void Bullet::MysetPos(Player *p, int posOfClock){
    switch(posOfClock){
    case 1:
        setPos(p -> x() + p -> getW()*3/4 , p -> y());
        break;
    case 2:
        setPos(p -> x() + p -> getW(), p -> y() + p -> getH() / 4);
        break;
    case 3:
        setPos(p -> x() + p -> getW(), p -> y() + p -> getH() / 2);
        break;
    case 4:
        setPos(p -> x() + p -> getW(), p -> y() + p -> getH()*3/4);
        break;
    case 5:
        setPos(p -> x() + p -> getW()*3/4, p -> y() + p -> getH());
        break;
    case 6:
        setPos(p -> x() + p -> getW() / 2, p -> y() + p -> getH());
        break;
    case 7:
        setPos(p -> x() + p -> getW()*1/4, p -> y() + p -> getH());
        break;
    case 8:
        setPos(p -> x(), p -> y() + p -> getH()*3/4);
        break;
    case 9:
        setPos(p -> x(), p -> y() + p -> getH()*2/4);
        break;
    case 10:
        setPos(p -> x(), p -> y() + p -> getH() / 4);
        break;
    case 11:
        setPos(p -> x() + p -> getW() / 4, p -> y());
        break;
    case 12:
        setPos(p -> x() + p -> getW() / 2, p -> y());
        break;
    }
}
int Bullet::whoShot(){
    return PorE;
}

int Bullet::getSpeed(){
    return s;
}
