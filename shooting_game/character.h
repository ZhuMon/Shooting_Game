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

protected:
    int HP;
    int height, width;
};

#endif // CHARACTER_H
