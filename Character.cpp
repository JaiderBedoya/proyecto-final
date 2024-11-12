#include "Character.h"
#include <QDebug>
#include "Obstacle.h"

//Character::Character() {}

Character::Character(qreal characterWidth_,qreal characterHeight_): characterWidth(characterWidth_), characterHeight(characterHeight_){
    //setting the sprite
    positionX = 0;
    positionY = 0;
    setFlag(QGraphicsItem::ItemIsFocusable);
    spriteSheet.load(":/imagesEmancipation/bartConAtaque.png");
    actualSprite = spriteSheet.copy(coordinateSpriteX,coordinateSpriteY,characterWidth,characterHeight);
    setPixmap(actualSprite);
}


void Character::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A){
        if(pos().x() > 0)
            setPos(x()-10,y());
        setSprite(266.25);
        qDebug() << "You pressed the A key";
    }
    else if(event->key() == Qt::Key_D){
        if(pos().x() + characterWidth < 800)//70.33,88.75
            setPos(x()+10,y());
        setSprite(0);
        qDebug() << "You pressed the D key";
    }
    else if(event->key() == Qt::Key_W){
        if(pos().y() > 0)
            setPos(x(),y()-10);
        setSprite(177.5);
        qDebug() << "You pressed the W key";
    }
    else if(event->key() == Qt::Key_S){
        if(pos().y() + characterHeight < 600)
            setPos(x(),y()+10);
        setSprite(88.75);
        qDebug() << "You pressed the S key";
    }
    else if(event->key() == Qt::Key_Space){
        setSprite(355);
        //create obstacle
        Obstacle  *proyectile = new Obstacle();
        proyectile->setPos(x()+characterWidth,y()+(characterHeight/2));
        scene()->addItem(proyectile);
        qDebug() << "Obstacle created";
        qDebug() << "You pressed the Space key";
    }
    qDebug() << "Character knows you pressed a key";
}


void Character::setSprite(qreal direction){

    coordinateSpriteX = spriteWidth*counterSprite;
    coordinateSpriteY = direction;
    actualSprite = spriteSheet.copy(coordinateSpriteX,coordinateSpriteY,characterWidth,characterHeight);
    setPixmap(actualSprite);
    counterSprite++;
    if(counterSprite == 6){
        counterSprite = 0;
    }
}
