#include "Character.h"
#include <QDebug>
#include "Obstacle.h"

//Character::Character() {}

Character::Character(qreal characterWidth_,qreal characterHeight_): characterWidth(characterWidth_), characterHeight(characterHeight_){
    //setting the sprite
    movementTimer = new QTimer(this);
    positionX = 0;
    positionY = 0;
    setFlag(QGraphicsItem::ItemIsFocusable);
    spriteSheet.load(":/imagesEmancipation/bartConAtaque.png");
    actualSprite = spriteSheet.copy(coordinateSpriteX,coordinateSpriteY,characterWidth,characterHeight);
    setPixmap(actualSprite);

    connect(movementTimer, &QTimer::timeout, this, &Character::setSprite);
}

void Character::setSprite(){

    coordinateSpriteX = characterWidth*counterSprite;
    coordinateSpriteY = movementDirection;
    actualSprite = spriteSheet.copy(coordinateSpriteX,coordinateSpriteY,characterWidth,characterHeight);
    setPixmap(actualSprite);
    counterSprite++;
    if(movementDirection == 355 && directionSprite == 1){
        if(counterSprite == 3){
            movementTimer->stop();
            counterSprite = 0;
        }
    }
    else if(movementDirection == 495.66 && directionSprite == -1){
        if(counterSprite == 6){
            movementTimer->stop();
            counterSprite = 0;
        }
    }
    if(counterSprite == 6){
        movementTimer->stop();
        counterSprite = 0;
    }
}


void Character::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A){
        directionSprite = -1;
        if(pos().x() > 0)
            setPos(x()-7,y());
        movementDirection = 266.25;
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        //setSprite(266.25);
        qDebug() << "You pressed the A key";
    }
    else if(event->key() == Qt::Key_D){
        directionSprite = 1;
        if(pos().x() + characterWidth < 800)//70.33,88.75
            setPos(x()+7,y());
        movementDirection = 0;
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        //setSprite(0);
        qDebug() << "You pressed the D key";
    }
    else if(event->key() == Qt::Key_W){
        if(pos().y() > 330)
            setPos(x(),y()-7);
        movementDirection = 177.5;
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        //setSprite(177.5);
        qDebug() << "You pressed the W key";
    }
    else if(event->key() == Qt::Key_S){
        if(pos().y() + characterHeight < 600)
            setPos(x(),y()+7);
        movementDirection = 88.75;
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        //setSprite(88.75);
        qDebug() << "You pressed the S key";
    }
    else if(event->key() == Qt::Key_Space){
        movementDirection = 355;
        (directionSprite == 1) ? counterSprite = 0 : counterSprite = 3;

        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        //setSprite(355);
        //create obstacle
        Obstacle  *proyectile = new Obstacle();
        if(directionSprite == 1){
            proyectile->setDirection(1);
            proyectile->setPos(x()+characterWidth,y()+(characterHeight/2));
        }
        else{
            proyectile->setDirection(-1);
            proyectile->setPos(x(),y()+(characterHeight/2));
        }

        scene()->addItem(proyectile);
        qDebug() << "Obstacle created";
        qDebug() << "You pressed the Space key";
    }
    qDebug() << "Character knows you pressed a key";
}

