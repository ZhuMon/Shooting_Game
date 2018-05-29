#ifndef BULLET_H
#define BULLET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Bullet(int who = 0, int s = 3);
    Bullet(QPixmap Qp, int who = 0, int s = 3);
    void MysetPixmap(const QPixmap &pixmap);
    int whoShot();
    int getSpeed();

public slots:
    /*virtual*/void fly(int mX = 0, int mY = 0); //move (x,y)

signals:
    void bulletFly(Bullet *b);


private:
    int PorE; //0:player 1:enemy
    int s; //speed of bullet
};

#endif // BULLET_H
