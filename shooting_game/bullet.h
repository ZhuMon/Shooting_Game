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

public slots:
    virtual void fly();

private:
    int PorE; //0:player 1:enemy
};

#endif // BULLET_H
