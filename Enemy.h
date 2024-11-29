#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"

class Enemy: public Character
{
private:
    bool attacking;
    QProgressBar* homerHealthBar;
    qreal moveValor = 10;
    unsigned short int rollCounter = 0;
public:

    Enemy();
    Enemy(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites);
    ~Enemy();

    QTimer *autonomousTimer;
    QTimer *kamehamehaTimer;
    QTimer *cannonBallTimer;
    QTimer *rollTimer;
    QTimer *aleatoryAttackTimer;

    void setAttacking(bool _attacking);
    void setHomerHealthBar(int newHealthBar);
    void setRollCounter(unsigned short _rollCounter);
    void setMoveValor(qreal newMoveValor);

    bool getAttacking();
    unsigned short getRollCounter();
    qreal getMoveValor();
    QProgressBar *getHomerHealthBar();

    void autonomousMovement();
    void aleatoryAttack();
    void kamehamehaAttack();
    void throwBullet();
    void roll();
    void createKamehameha();
    void checkProtagonistCollision();
    void playDamageSound();

};

#endif // ENEMY_H
