#include "bullet.h"
#include <QtMath>

Bullet::Bullet(int who, int dx, int dy){
    PorE = who;
    pX = dx;
    pY = dy;
    flyORresize = true;
    resizeORstay = true;
    flower = false;
    count = 0;
    move = 0;
}

Bullet::Bullet(QPixmap Qp, int who, int dx, int dy):
    PorE(who),
    pX(dx), pY(dy){
    this -> MysetPixmap(Qp);
    flyORresize = true;
    resizeORstay = true;
    flower = false;
    count = 0;
    move = 0;
}

void Bullet::fly(int mX, int mY, bool overplus){
    /*int initX, initY;
    initX = x();
    initY = y();*/

    double mmX = (double)mX/10;
    double mmY = (double)mY/10;
    if(flower){
        move += 1;
        if(move < 50){
            mmX *= (50-move)/50;
            mmY *= (0-move)/50;
        } else {
            move = 0;
        }
    }
    if(flyORresize){ //fly
        if(PorE == 0){ //player shoot
            this -> setPos(x(), y() - 3);
        } else if(PorE == 1) {//enemy shoot
            if(overplus){
                setPos(x() + mmX + pX, y() + mmY + pY);
            }else if(mmX != 0 || mmY != 0){
                this -> setPos(x() + mmX, y() + mmY);
            }else{
                this -> setPos(x() + pX, y() + pY);
            }
        }

        emit bulletFly(this);
    } else if(resizeORstay){ //resize   //mX = width, mY = height
        mX += 5;
        mY += 5;
        setPos(x()-mX/2, y()-mY/2);
        //this->pixmap().scaled(pixmap().width()+mX, pixmap().height()+mY);
        //setScale(((qreal)pixmap().width()+mX)/pixmap().width());
        this -> MysetPixmap(QPixmap(":/images/bullet4").scaled(pixmap().width()+mX, pixmap().height()+mY));
        count++;
        if(count > 10){
            flyORresize = true;
        }
    } else {
        count++;
        if(count > 10){
            resizeORstay = true;
            flyORresize = true;
        }
    }

    //move += pow(pow((x()-initX),2)+pow((y()-initY),2), 0.5);

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
