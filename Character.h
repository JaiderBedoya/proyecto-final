#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QPixmap>
#include <QKeyEvent>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

class Character : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    QString name;
    qreal positionX;
    qreal positionY;
    QTimer *movementTimer;
    qreal movementDirection;
    unsigned short int health;
    short int directionSprite = 1;


public:
    QPixmap spriteSheet;
    QPixmap actualSprite;
    //Character();
    qreal characterWidth;
    qreal characterHeight;
    int spriteWidth, spriteHeight;
    Character(qreal characterWidth_,qreal characterHeight_);
    QString getName();
    unsigned short int getHealth();
    int counterSprite = 0;

    int coordinateSpriteX = 0, coordinateSpriteY = 0;

    void setName();
    void setHealth();

    void move(int movementX, int movementY);
    void setSprite();

    void keyPressEvent(QKeyEvent* event);
public slots:
};

#endif // CHARACTER_H

