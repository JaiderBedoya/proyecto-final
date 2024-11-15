#include "Obstacle.h"

Obstacle::Obstacle(){
    //drawing the rectangle
    QPixmap projectileImage(":/imagesEmancipation/bullet.png");
    QPixmap redimensionedImage = projectileImage.scaled(20, 20, Qt::KeepAspectRatio);
    setPixmap(redimensionedImage);
    //connect
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(parabolicMove()));
    velocity = 1.2;
    angle = M_PI_4;
    timer->start(20);
}

void Obstacle::setDirection(short int _direction){
    direction = _direction;
}

void Obstacle::setTimeLapsed(unsigned short _timeLapsed)
{
    timeLapsed = _timeLapsed;
}

void Obstacle::setVelocity(qreal _velocity)
{
    velocity = _velocity;
}

unsigned short Obstacle::getTimeLapsed()
{
    return timeLapsed;
}

qreal Obstacle::getVelocity()
{
    return velocity;
}

void Obstacle::move()
{
    //moving the obstacle up and rigth/left
    setPos(x() + (velocity*direction) ,y());
    if(pos().x() + 10 < 0 || pos().x() +10 > 800){
        scene()->removeItem(this);
        delete this;
        qDebug() << "obstacle deleted";
    }
}

void Obstacle::parabolicMove()
{
    qreal X,Y;
    X = x() + velocity*qCos(angle)*timeLapsed;
    Y = y() - velocity*qSin(angle) + 0.5*9.8* qPow(timeLapsed, 2);
   // X = velocity * qCos(angle) * timeLapsed * direction;
   // Y = (velocity * qSin(angle) * timeLapsed - 0.5 * 9.8 * qPow(timeLapsed, 2));
    setPos(X,Y);
    this->setTimeLapsed(this->getTimeLapsed()+0.1);


    //this->setVelocity(this->getVelocity()+0.1);
    if(pos().x() + 10 < 0 || pos().x() +10 > 800){
        scene()->removeItem(this);
        delete this;
        qDebug() << "obstacle deleted";
    }
}
