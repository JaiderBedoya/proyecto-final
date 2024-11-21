#ifndef PROTAGONIST_H
#define PROTAGONIST_H
#include <Character.h>

class Protagonist: public Character
{
private:
    QSet<int> activeKeys;
    QTimer* movementUpdateTimer;
    bool canShoot;
    QTimer* shootCooldownTimer;
    QProgressBar* bartHealthBar;

public:
    Protagonist();
    Protagonist(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void resetShootCooldown();
    QProgressBar *getBartHealthBar();

    void setBartHealthBar(int newHealthBar);

private slots:
    void updateMovement();

};

#endif // PROTAGONIST_H
