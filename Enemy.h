#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"

class Enemy: public Character
{
private:
    bool attacking;
public:

    QTimer *autonomousTimer;
    QTimer *kamehamehaTimer;
    QTimer *cannonBallTimer;
    QTimer *rollTimer;
    QTimer *aleatoryAttackTimer;

    Enemy();
    Enemy(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites);
    void setAttacking(bool _attacking);
    bool getAttacking();

    void increaseMovementDirection();
    void autonomousMovement();
    void aleatoryAttack();

    qreal moveValor = 10;

    void kamehamehaAttack();
    void throwBullet();
    void roll();

public slots:

};

#endif // ENEMY_H
