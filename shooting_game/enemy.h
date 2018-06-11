#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include <QProgressBar>
#include <QLabel>

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
    void setGif(QMovie *movie);

private:
    QProgressBar *HPpercent;
    QWidget *w;
    QLabel *label;
    //int HP;
    //int height, width;
};

#endif // ENEMY_H
