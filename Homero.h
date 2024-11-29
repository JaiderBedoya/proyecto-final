#ifndef HOMERO_H
#define HOMERO_H
#include "Character.h"

class Homero :  public Character
{
    Q_OBJECT
private:
    qreal gravity;
    qreal skateImpulse, verticalVelocity;
    unsigned short int scoreGame = 0;
    bool isFlying;
    QTimer *flyingTimer;
    QProgressBar* homerHealthBar;

public:
    Homero();
    Homero(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites);
    ~Homero();

    QProgressBar *getHomerHealthBar();
    unsigned short int getScoreGame();
    qreal getVerticalVelocity();
    qreal getGravity();
    qreal getSkateImpulse();
    bool getIsFlying();

    void setScoreGame(unsigned short int newScoreGame);
    void setHomerHealthBar(int newHealthBar);
    void setIsFlying(bool _isFlying);
    void setVerticalVelocity(qreal _verticalVelocity);
    void setGravity(qreal _gravity);
    void setSkateImpulse(qreal _skateImpulse);

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void increaseScore(unsigned short int newScore);

public slots:
    void updateMovement();

signals:
    void scoreChanged(unsigned short int newScore);

};

#endif
