#include "bullet.h"
#include <QtMath>
#include <QDebug>

Bullet::Bullet(int who, int dx, int dy){
    PorE = who;
    pX = dx;
    pY = dy;
    flyORresize = true;
    resizeORstay = true;
    flower = false;
    notM = false;
    star = false;
    count = 0;
    move = 0;
    path = 0;
}

Bullet::Bullet(QPixmap Qp, int who, int dx, int dy):
    PorE(who),
    pX(dx), pY(dy){
    this -> MysetPixmap(Qp);
    flyORresize = true;
    resizeORstay = true;
    flower = false;
    notM = false;
    star = false;
    count = 0;
    move = 0;
    path = 0;
}

void Bullet::fly(int mX, int mY, bool overplus){



    double mmX = mX;// = (double)mX/10;
    double mmY = mY;// = (double)mY/10;
    if(flower){
        mmX += pX;
        mmY += pY;
        mmX = qCos(qDegreesToRadians(mmX))*10;
        mmY = qSin(qDegreesToRadians(mmY))*10;
        //qDebug() << QString::number(mmX) << QString::number(mmY);
        move += 1;
        if(move < 30){
            mmX *= (30-move)/30;
            mmY *= (30-move)/30;
            //qDebug() << QString::number(mmX) << QString::number(mmY);

        } else {
            move = 0;
            flyORresize = false;
            resizeORstay = false;
            //qDebug() << QString::number(x())<<QString::number(y());
            emit bulletFly(this);
            return;
        }
    }
    if(flyORresize){ //fly
        if(PorE == 0){ //player shoot
            this -> setPos(x(), y() - 3);
        } else if(PorE == 1) {//enemy shoot
            if(notM){
                this -> setPos(x() + pX, y() + pY);
            } else if(overplus){
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
        if(count > 10 && flower == false){
            resizeORstay = true;
            flyORresize = true;
        }
        if(count > 5 && star == true){
            flyORresize = true;
            count = 0;
            //initX = x();
            //initY = y();
        }
        return;
    }
    /*if(star){
        //path += pow(pow((x()-initX),2)+pow((y()-initY),2), 0.5);
        //initX = x();
        //initY = y();
        if(y() <= 20 || y() + pixmap().height() >= 620 || x() <= 40 || x()+ pixmap().width() >= 440){
            flyORresize = false;
            resizeORstay = false;
            //path = 0;
        }
    }*/
    //path += pow(pow((x()-initX),2)+pow((y()-initY),2), 0.5);
    //qDebug() << QString::number(path);

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

    initX = x();
    initY = y();

    //qDebug() << "init"<<QString::number(initX) << " "<<QString::number(initY);
}

int Bullet::whoShot(){
    return PorE;
}

int Bullet::getSpeed(){
    return s;
}

void Bullet::MysetPos(qreal x, qreal y){
    setPos(x,y);
    initX = this->x();
    initY = this->y();
}
