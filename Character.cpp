#include "Character.h"
#include <QDebug>

//CONSTRUCTORS

Character::Character()
{

}

Character::Character(qreal characterWidth_,qreal characterHeight_, QString spritePath): characterWidth(characterWidth_), characterHeight(characterHeight_){
    //setting the sprite
    movementTimer = new QTimer(this);

    spriteSheet.load(spritePath);
    actualSprite = spriteSheet.copy(coordinateSpriteX,coordinateSpriteY,characterWidth,characterHeight);
    setPixmap(actualSprite);

    connect(movementTimer, &QTimer::timeout, this, &Character::setSprite);
}

//GETTERS


qreal Character::getMovementDirection()
{
    return movementDirection;
}

unsigned short int Character::getHealth()
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



