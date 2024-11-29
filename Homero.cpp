#include "Homero.h"

Homero::Homero() {}

Homero::Homero(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short numberOfHorizontalSprites) :  Character(characterWidth, characterHeight, spritePath, numberOfHorizontalSprites),  verticalVelocity(0), gravity(0.3), skateImpulse(-0.8), isFlying(false)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    QTimer* timerHomero = new QTimer(this);
    connect(timerHomero, &QTimer::timeout, this, &Homero::updateMovement);
    timerHomero->start(16);

    homerHealthBar = new QProgressBar();
    homerHealthBar->setRange(0, 100);
    homerHealthBar->setValue(this->getHealth());
    homerHealthBar->setTextVisible(false);
}

Homero::~Homero(){
}


unsigned short int Homero::getScoreGame()
{
    return scoreGame;
}
qreal Homero::getVerticalVelocity()
{
    return verticalVelocity;
}

qreal Homero::getGravity()
{
    return gravity;
}

qreal Homero::getSkateImpulse()
{
    return skateImpulse;
}

bool Homero::getIsFlying()
{
    return isFlying;
}

QProgressBar *Homero::getHomerHealthBar()
{
    return homerHealthBar;
}

void Homero::setScoreGame(unsigned short int _scoreGame)
{
    scoreGame = _scoreGame;
}

void Homero::setVerticalVelocity(qreal _verticalVelocity)
{
    verticalVelocity = _verticalVelocity;
}

void Homero::setGravity(qreal _gravity)
{
    gravity = _gravity;
}

void Homero::setSkateImpulse(qreal _skateImpulse)
{
    skateImpulse = _skateImpulse;
}

void Homero::setIsFlying(bool _isFlying)
{
    isFlying = _isFlying;
}

void Homero::setHomerHealthBar(int newHealthBar)
{
    homerHealthBar->setValue(newHealthBar);
    if(this->getHealth() < 100){
        QMediaPlayer* music = new QMediaPlayer;
        music->setSource(QUrl("qrc:/sounds/soundsEmancipation/Voicy_Homer Simpson_ Doh 3.mp3"));
        QAudioOutput* audioOutput = new QAudioOutput(this);

        music->setAudioOutput(audioOutput);
        audioOutput->setVolume(0.5);
        music->play();
    }
}

void Homero::keyPressEvent(QKeyEvent* event){
        if(event->key() == Qt::Key_Space){
        qDebug()<<"space bar has been clicked";
            this->setIsFlying(true);
        }
        //Change gravity with the S key
        /*
        else if(event->key() == Qt::Key_S){
            gravity > 0 && jetPackImpulse < 0 ? gravity *= 1, jetPackImpulse *= 1 : gravity *= -1, jetPackImpulse *= -1;
        }
        */
}

void Homero::keyReleaseEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Space){
        this->setIsFlying(false);
    }
}

void Homero::updateMovement(){

        if (isFlying) {
        this->setVerticalVelocity(this->getVerticalVelocity() + this->getSkateImpulse());
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

        if (y() < 75) {
            setY(75);
            this->setCounterSprite(5);
            this->setSprite();
            verticalVelocity = 0;
        } else if (y() > 450) {
            setY(450);
            this->setCounterSprite(0);
            this->setSprite();
            verticalVelocity = 0;
        }
}

void Homero::increaseScore(unsigned short int  newScore) {
    scoreGame += newScore;
    emit scoreChanged(scoreGame);
}
