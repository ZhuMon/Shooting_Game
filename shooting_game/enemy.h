#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include <QProgressBar>

class Enemy: public Character//, public QLabel
{
public:
    Enemy(QWidget *parent);
    virtual void myMove(int x, int y);
    //int getH();
    //int getW();
    //int getHp();
    //void recover(int point);
    virtual void damage(int point);
    virtual void recover(int point);
    void setHPvisible(bool visible);
    virtual void initial();

private:
    QProgressBar *HPpercent;
    QWidget *w;
    //int HP;
    //int height, width;
};

#endif // ENEMY_H
