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
    void recover(int point);
    void damage(int point);
    void setImage(const QPixmap &Qp, float w);//set width to w

protected:
    int HP;
    int height, width;
};

#endif // CHARACTER_H
