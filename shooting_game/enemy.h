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
    void initial(int x, int y, int w, int HP, const QPixmap& qp);
    void setGif(QMovie *movie, int w , int h);
    void setGifvisible(bool visible);


private:
    QProgressBar *HPpercent;
    QWidget *parent;
    QLabel *label;
    //int HP;
    //int height, width;
};

#endif // ENEMY_H
