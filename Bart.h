#ifndef BART_H
#define BART_H
#include <Character.h>

class Bart: public Character
{
private:
    QSet<int> activeKeys;
    QTimer* movementUpdateTimer;
    QTimer* shootCooldownTimer;
    QTimer* ayCarambaTimer;
    bool canShoot;
    bool ayCaramba;
    QProgressBar* bartHealthBar;

public:
    Bart();
    Bart(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites);
    ~Bart();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    QProgressBar *getBartHealthBar();
    bool getAyCaramba();
    bool getCanShoot();

    void setBartHealthBar(int _healthBar);
    void setCanShoot(bool _canShoot);
    void setAyCaramba(bool _ayCaramba);


private slots:
    void updateMovement();
    void ayCarambaCooldown();
    void resetShootCooldown();

};

#endif // BART_H
