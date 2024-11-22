#include "Homero.h"

Homero::Homero() {}

Homero::Homero(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short numberOfHorizontalSprites) :  Character(characterWidth, characterHeight, spritePath, numberOfHorizontalSprites),  verticalVelocity(0), gravity(0.5), jetPackImpulse(-1), isFlying(false)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    QTimer* timerHomero = new QTimer(this);
    connect(timerHomero, &QTimer::timeout, this, &Homero::updateMovement);
    timerHomero->start(16);
}

void Homero::keyPressEvent(QKeyEvent* event){
        if(event->key() == Qt::Key_Space){
        qDebug()<<"space bar has been clicked";
            if(!movementTimer->isActive()){
                movementTimer->start(100);
            }
            this->setIsFlying(true);
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
        }

        verticalVelocity += gravity; // Aplica la gravedad
        setY(y() + verticalVelocity); // Actualiza la posición vertical

        if (y() < 0) {
            setY(0);
            verticalVelocity = 0;
        } else if (y() > 490) { // Suponiendo un límite inferior de la pantalla
            setY(490);
            verticalVelocity = 0;
        }
}

