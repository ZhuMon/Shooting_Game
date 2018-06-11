#ifndef CHARACTER_H
#define CHARACTER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>

class Character: public QGraphicsPixmapItem
{
public:
    Character();
    int getH();
    int getW();
    int getHp();
    virtual void recover(int point);
    virtual void damage(int point) = 0;
    void setImage(const QPixmap &Qp, float w);//set width to w
    virtual void myMove(int x, int y) = 0;
    virtual void initial();//initial position, hp


protected:
    int HP;
    int height, width;
    int X0, Y0; //initial position
    int initHP; //initial HP
};

#endif // CHARACTER_H
