#ifndef BULLET_H
#define BULLET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Bullet(int who = 0);
    Bullet(QPixmap Qp, int who = 0);
    void MysetPixmap(const QPixmap &pixmap);
    int whoShot();

public slots:
    virtual void fly(int speed = 3);

signals:
    void bulletFly(Bullet *b);


private:
    int PorE; //0:player 1:enemy
};

#endif // BULLET_H
