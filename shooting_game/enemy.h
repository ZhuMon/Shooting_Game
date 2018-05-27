#ifndef ENEMY_H
#define ENEMY_H

#include <player.h>

class Enemy: public Player
{
public:
    Enemy();
    int getH();
    int getW();
    int getHp();
    void recover(int point);
    void damage(int point);

private:
    int HP;
    int height, width;
};

#endif // ENEMY_H
