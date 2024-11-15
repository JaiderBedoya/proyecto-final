#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"

class Enemy: public Character
{
private:
    bool attacking;

public:
    Enemy();
    Enemy(qreal characterWidth, qreal characterHeight, const QString &spritePath);
    void setAttacking(bool _attacking);
    bool getAttacking();
};

#endif // ENEMY_H
