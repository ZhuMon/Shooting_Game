#include "bullet.h"

Bullet::Bullet(int who, int dx, int dy){
    PorE = who;
    pX = dx;
    pY = dy;
    flyORresize = true;
}

Bullet::Bullet(QPixmap Qp, int who, int dx, int dy):
    PorE(who),
    pX(dx), pY(dy){
    this -> MysetPixmap(Qp);
    flyORresize = true;
}

void Bullet::fly(int mX, int mY, bool overplus){
    if(flyORresize){ //fly
        if(PorE == 0){ //player shoot
            this -> setPos(x(), y() - 3);
        } else if(PorE == 1) {//enemy shoot
            if(overplus){
                setPos(x() + mX + pX, y() + mY + pY);
            }else if(mX != 0 || mY != 0){
                this -> setPos(x() + mX, y() + mY);
            }else{
                this -> setPos(x() + pX, y() + pY);
            }
        }

        emit bulletFly(this);
    } else { //resize   //mX = width, mY = height
        mX += 5;
        mY += 5;
        setPos(x()-mX/2, y()-mY/2);
        //this->pixmap().scaled(pixmap().width()+mX, pixmap().height()+mY);
        //setScale(((qreal)pixmap().width()+mX)/pixmap().width());
        this -> MysetPixmap(QPixmap(":/images/bullet4").scaled(pixmap().width()+mX, pixmap().height()+mY));

        if(pixmap().width() > 75){
            flyORresize = true;
        }
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

void Bullet::MysetPos(Character *p, int posOfClock){
    int halfW = this -> pixmap().width()/2;
    int halfH = this -> pixmap().height()/2;
    switch(posOfClock){
    case 1:
        setPos(p -> x() + p -> getW()*3/4 - halfW, p -> y() - halfH*2);
        break;
    case 2:
        setPos(p -> x() + p -> getW(), p -> y() + p -> getH() / 4 - halfH);
        break;
    case 3:
        setPos(p -> x() + p -> getW(), p -> y() + p -> getH() / 2 - halfH);
        break;
    case 4:
        setPos(p -> x() + p -> getW(), p -> y() + p -> getH()*3/4 - halfH);
        break;
    case 5:
        setPos(p -> x() + p -> getW()*3/4 - halfW, p -> y() + p -> getH());
        break;
    case 6:
        setPos(p -> x() + p -> getW() / 2 - halfW, p -> y() + p -> getH());
        break;
    case 7:
        setPos(p -> x() + p -> getW()*1/4 - halfW, p -> y() + p -> getH());
        break;
    case 8:
        setPos(p -> x() - halfW*2, p -> y() + p -> getH()*3/4 - halfH);
        break;
    case 9:
        setPos(p -> x() - halfW*2, p -> y() + p -> getH()*2/4 - halfH);
        break;
    case 10:
        setPos(p -> x() - halfW*2, p -> y() + p -> getH() / 4 - halfH);
        break;
    case 11:
        setPos(p -> x() + p -> getW() / 4 - halfW, p -> y() - halfH*2);
        break;
    case 12:
        setPos(p -> x() + p -> getW() / 2 - halfW, p -> y() - halfH*2);
        break;
    }
}

int Bullet::whoShot(){
    return PorE;
}

int Bullet::getSpeed(){
    return s;
}
