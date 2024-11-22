#ifndef HOMERO_H
#define HOMERO_H
#include "Character.h"

class Homero : public Character
{
private:
    qreal verticalVelocity,gravity,jetPackImpulse;
    bool isFlying;
    QTimer *flyingTimer;

public:
    Homero();
    Homero(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void setIsFlying(bool _isFlying);
public slots:
    void updateMovement();
};

#endif
