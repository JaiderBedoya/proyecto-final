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
#include <QProgressBar>
#include <QGraphicsProxyWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>
#include <QFile>
#include <QDate>

class Character : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal movementDirection;
    unsigned short int numberOfHorizontalSprites;
    short int health = 100;
    short int directionSprite = 1;
    qreal characterWidth;
    qreal characterHeight;
    int spriteWidth, spriteHeight;
    QPixmap spriteSheet;
    QPixmap actualSprite;
    int counterSprite = 0, coordinateSpriteX = 0, coordinateSpriteY = 0;

public:

    QTimer *movementTimer;

    Character();
    Character(qreal characterWidth_,qreal characterHeight_, QString spritePath, unsigned short int numberOfHorizontalSprites);
    virtual ~Character();


    qreal getMovementDirection();
    short int getHealth();
    short int getDirectionSprite();
    qreal getCharacterWidth();
    qreal getCharacterHeight();
    int getSpriteWidth();
    int getSpriteHeight();
    int getCounterSprite() ;
    int getCoordinateSpriteX();
    int getCoordinateSpriteY();

    void setHealth(short int _health);
    void setSprite();
    void setDirectionSprite(short int _directionSprite);
    void setMovementDirection(qreal _movementDirection);
    void setCounterSprite(int _counterSprite);
    void setCoordinateSpriteX(int _CoordinateSpriteX);
    void setCoordinateSpriteY(int _CoordinateSpriteY);


    void emitWinOrLost(bool win, unsigned short int sceneNumber);
    void achievement(const QString &text);

signals:
    void winOrLost(bool win, unsigned short int sceneNumber);
};

#endif // CHARACTER_H

