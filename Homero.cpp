#include "Homero.h"

int Homero::getScoreGame()
{
    return scoreGame;
}

void Homero::setScoreGame(int _scoreGame)
{
    scoreGame = _scoreGame;
}

void Homero::increaseScore(int  newScore) {
    scoreGame += newScore;
    emit scoreChanged(scoreGame);
}


Homero::Homero() {}

Homero::Homero(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short numberOfHorizontalSprites) :  Character(characterWidth, characterHeight, spritePath, numberOfHorizontalSprites),  verticalVelocity(0), gravity(0.3), jetPackImpulse(-0.8), isFlying(false)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    QTimer* timerHomero = new QTimer(this);
    connect(timerHomero, &QTimer::timeout, this, &Homero::updateMovement);
    timerHomero->start(16);
}

void Homero::keyPressEvent(QKeyEvent* event){
        if(event->key() == Qt::Key_Space){
        qDebug()<<"space bar has been clicked";
            this->setIsFlying(true);
        }
        //Change gravity with the S key
        else if(event->key() == Qt::Key_S){
            gravity > 0 && jetPackImpulse < 0 ? gravity *= 1, jetPackImpulse *= 1 : gravity *= -1, jetPackImpulse *= -1;
        }
}

void Homero::keyReleaseEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Space){
        this->setIsFlying(false);
    }
}

void Homero::setIsFlying(bool _isFlying)
{
    isFlying = _isFlying;
}

void Homero::updateMovement(){

        if (isFlying) {
            verticalVelocity += jetPackImpulse;
            this->setCounterSprite(1);
            this->setSprite();
            qDebug()<< this->getScoreGame();
        }
        else{
            this->setCounterSprite(4);
            this->setSprite();
        }
        verticalVelocity += gravity;
        setY(y() + verticalVelocity);

        if (y() < 0) {
            setY(0);
            this->setCounterSprite(5);
            this->setSprite();
            verticalVelocity = 0;
        } else if (y() > 400) {
            setY(400);
            this->setCounterSprite(0);
            this->setSprite();
            verticalVelocity = 0;
        }
}
