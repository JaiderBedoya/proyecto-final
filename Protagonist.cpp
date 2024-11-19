#include "Protagonist.h"
#include "Obstacle.h"

Protagonist::Protagonist() {

}
Protagonist::Protagonist(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites): Character(characterWidth, characterHeight, spritePath, numberOfHorizontalSprites){
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void Protagonist::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A){
        this->setDirectionSprite(-1);
        if(pos().x() > 0)
            setPos(x()-7,y());
        this->setMovementDirection(266.25);
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        //setSprite(266.25);
        qDebug() << "You pressed the A key";
    }
    else if(event->key() == Qt::Key_D){
        this->setDirectionSprite(1);
        if(pos().x() + this->getCharacterWidth() < 800)//70.33,88.75
            setPos(x()+7,y());
        this->setMovementDirection(0);
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        //setSprite(0);
        qDebug() << "You pressed the D key";
    }
    else if(event->key() == Qt::Key_W){
        if(pos().y() > 340)
            setPos(x(),y()-7);
        this->setMovementDirection(177.5);
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        //setSprite(177.5);
        qDebug() << "You pressed the W key";
    }
    else if(event->key() == Qt::Key_S){
        if(pos().y() + this->getCharacterHeight() < 600)
            setPos(x(),y()+7);
        this->setMovementDirection(88.75);
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        //setSprite(88.75);
        qDebug() << "You pressed the S key";
    }
    else if(event->key() == Qt::Key_Space){
        this->setMovementDirection(355);
        (this->getDirectionSprite() == 1) ? counterSprite = 0 : counterSprite = 3;

        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        //setSprite(355);
        //create obstacle
        Obstacle  *proyectile = new Obstacle(":/imagesEmancipation/BartBullet.png",10);

        if(this->getDirectionSprite() == 1){
            proyectile->setDirection(1);
            proyectile->setPos(x()+this->getCharacterWidth(),y()+(this->getCharacterHeight()/2));
        }
        else{
            proyectile->setDirection(-1);
            proyectile->setPos(x(),y()+(this->getCharacterHeight()/2));
        }

        scene()->addItem(proyectile);
        qDebug() << "Obstacle created";
        qDebug() << "You pressed the Space key";
    }
    qDebug() << "Character knows you pressed a key";
}
