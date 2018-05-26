#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Player: public QGraphicsPixmapItem
{
public:
    Player();
    int getH();
    int getW();
    int getHp();
    void recover(int point);
    void damage(int point);

private:
    int HP;
    int height, width;
};

#endif // PLAYER_H
