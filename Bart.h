#ifndef BART_H
#define BART_H
#include <Character.h>

class Bart: public Character
{
private:
    QSet<int> activeKeys;
    QTimer* movementUpdateTimer;
    bool canShoot;
    QTimer* shootCooldownTimer;
    QTimer* ayCarambaTimer;
    QProgressBar* bartHealthBar;
    bool ayCaramba;

public:
    Bart();
    Bart(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    QProgressBar *getBartHealthBar();
    void setBartHealthBar(int _healthBar);
    void setCanShoot(bool _canShoot);
    void setAyCaramba(bool _ayCaramba);

    bool getAyCaramba();
    bool getCanShoot();

private slots:
    void updateMovement();
    void ayCarambaCooldown();
    void resetShootCooldown();

};

#endif // BART_H
