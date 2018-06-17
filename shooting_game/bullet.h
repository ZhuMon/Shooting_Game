#ifndef BULLET_H
#define BULLET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "character.h"



class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Bullet(int who = 0, int dx = 0, int dy = 10);
    Bullet(QPixmap Qp, int who = 0, int dx = 0, int dy = 10);
    void MysetPixmap(const QPixmap &pixmap);
    void MysetPos(Character *p, int posOfClock = 6);
    int whoShot();
    int getSpeed();
    double pX, pY; //when begin where bullet go
    bool flyORresize;
    bool resizeORstay;
    bool flower;
    bool notM;
    bool star;
    void MysetPos(qreal x, qreal y);

public slots:
    /*virtual*/void fly(int mX = 0, int mY = 0, bool overplus = false); //move (x,y)

signals:
    void bulletFly(Bullet *b);


private:
    int PorE; //0:player 1:enemy
    int s; //speed of bullet
    int count; //count time
    double move; //how long bullet trace


    int initX; //the bullet begin pos
    int initY;
    double path;
};

#endif // BULLET_H
