#include "Character.h"
#include <QDebug>

//CONSTRUCTORS

Character::Character()
{

}

Character::Character(qreal characterWidth_,qreal characterHeight_, QString spritePath, unsigned short int _numberOfHorizontalSprites): characterWidth(characterWidth_), characterHeight(characterHeight_), numberOfHorizontalSprites(_numberOfHorizontalSprites){
    //setting the sprite
    movementTimer = new QTimer(this);

    spriteSheet.load(spritePath);
    actualSprite = spriteSheet.copy(coordinateSpriteX,coordinateSpriteY,characterWidth,characterHeight);
    setPixmap(actualSprite);
    connect(movementTimer, &QTimer::timeout, this, &Character::setSprite);
}


//GETTERS

int Character::getCoordinateSpriteY()
{
    return coordinateSpriteY;
}

int Character::getCoordinateSpriteX()
{
    return coordinateSpriteX;
}

int Character::getCounterSprite()
{
    return counterSprite;
}

qreal Character::getMovementDirection()
{
    return movementDirection;
}

short int Character::getHealth()
{
    return health;
}

short int Character::getDirectionSprite()
{
    return directionSprite;
}

qreal Character::getCharacterWidth()
{
    return characterWidth;
}

qreal Character::getCharacterHeight()
{
    return characterHeight;
}

int Character::getSpriteWidth()
{
    return spriteWidth;
}

int Character::getSpriteHeight()
{
    return spriteHeight;
}


//SETTERS

void Character::setDirectionSprite(short _directionSprite)
{
    directionSprite = _directionSprite;
}

void Character::setMovementDirection(qreal _movementDirection)
{
    movementDirection = _movementDirection;
}

void Character::setCoordinateSpriteY(int _CoordinateSpriteY)
{
    coordinateSpriteY = _CoordinateSpriteY;
}

void Character::setCoordinateSpriteX(int _CoordinateSpriteX)
{
    coordinateSpriteX = _CoordinateSpriteX;
}

void Character::setCounterSprite(int _counterSprite)
{
    counterSprite = _counterSprite;
}

void Character::setHealth(short int _health)
{
    health = _health;
}

void Character::setSprite(){

    coordinateSpriteX = characterWidth*counterSprite;
    coordinateSpriteY = movementDirection;
    actualSprite = spriteSheet.copy(coordinateSpriteX,coordinateSpriteY,characterWidth,characterHeight);
    setPixmap(actualSprite);
    counterSprite++;
    //this is an exclusive line of code for bart, it's a protagonist instance
    if(movementDirection == 355 && directionSprite == 1){
        if(counterSprite == 3){
            movementTimer->stop();
            counterSprite = 0;
        }
    }
    else if(movementDirection == 495.66 && directionSprite == -1){
        if(counterSprite == numberOfHorizontalSprites){
            movementTimer->stop();
            counterSprite = 0;
        }
    }
    if(counterSprite == numberOfHorizontalSprites){
        movementTimer->stop();
        counterSprite = 0;
    }
    if(this->getMovementDirection() == this->getCharacterHeight()){
        qDebug() << "Right kamehameha";
    }

}



