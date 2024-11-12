#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QPixmap>
#include <QKeyEvent>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Character : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    QString name;
    qreal positionX;
    qreal positionY;

    unsigned short int health;


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
    void setSprite(qreal direction);

    void keyPressEvent(QKeyEvent* event);
public slots:
};

#endif // CHARACTER_H

