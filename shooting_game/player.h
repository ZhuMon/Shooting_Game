#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Player: public Character
{
public:
    Player();
    virtual void myMove(int x, int y);
    virtual void damage(int point);
};

#endif // PLAYER_H
