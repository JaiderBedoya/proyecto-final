#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QPixmap>
#include <QKeyEvent>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QRandomGenerator>

class Character : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal movementDirection;
    unsigned short int numberOfHorizontalSprites;
    unsigned short int health;
    short int directionSprite = 1;
    qreal characterWidth;
    qreal characterHeight;
    int spriteWidth, spriteHeight;

public:
    QTimer *movementTimer;
    QPixmap spriteSheet;
    QPixmap actualSprite;
    Character();
    Character(qreal characterWidth_,qreal characterHeight_, QString spritePath, unsigned short int numberOfHorizontalSprites);
    int counterSprite = 0;

    int coordinateSpriteX = 0, coordinateSpriteY = 0;
    qreal getMovementDirection();
    unsigned short int getHealth();
    short int getDirectionSprite();
    qreal getCharacterWidth();
    qreal getCharacterHeight();
    int getSpriteWidth();
    int getSpriteHeight();


    void setHealth();
    void setSprite();
    void setDirectionSprite(short int _directionSprite);
    void setMovementDirection(qreal _movementDirection);

    void setCounterSprite(int _counterSprite);

    int getCounterSprite() ;

public slots:
};

#endif // CHARACTER_H

