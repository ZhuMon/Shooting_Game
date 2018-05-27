#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>

class Player: public QGraphicsPixmapItem
{
public:
    Player();
    int getH();
    int getW();
    int getHp();
    void recover(int point);
    void damage(int point);
    void setImage(const QPixmap &Qp, float w);//set width to w

protected:
    int HP;
    int height, width;
};

#endif // PLAYER_H
