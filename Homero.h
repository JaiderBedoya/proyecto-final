#ifndef HOMERO_H
#define HOMERO_H
#include "Character.h"

class Homero :  public Character
{
    Q_OBJECT
private:
    qreal verticalVelocity,gravity,jetPackImpulse;
    int scoreGame = 0;
    bool isFlying;
    QTimer *flyingTimer;
    QProgressBar* homerHealthBar;

public:
    Homero();
    Homero(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    void setScoreGame(int newScoreGame);
    void increaseScore(int newScore);

    QProgressBar *getHomerHealthBar();
    int getScoreGame();

    void setHomerHealthBar(int newHealthBar);
    void setIsFlying(bool _isFlying);

public slots:
    void updateMovement();

signals:
    void scoreChanged(int newScore);

};

#endif
