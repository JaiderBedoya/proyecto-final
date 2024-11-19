#include "Obstacle.h"

Obstacle::Obstacle(const QString& obstacleImage, qreal size){
    //drawing the rectangle
    QPixmap projectileImage(obstacleImage);
    QPixmap redimensionedImage = projectileImage.scaled(size, size, Qt::KeepAspectRatio);
    setPixmap(redimensionedImage);
    //connect
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timerMovPar = new QTimer(this); //Siempre se debe inicializar
    connect(timerMovPar, &QTimer::timeout, this, [=]() {
        parabolicMove();
    });
    velocity = 15;
    angle = 45;
    angle = angle*M_PI/180;
    timer->start(20);
}

void Obstacle::setDirection(short int _direction){
    direction = _direction;
}

void Obstacle::setTimeLapsed(qreal _timeLapsed)
{
    timeLapsed = _timeLapsed;
}

void Obstacle::setVelocity(qreal _velocity)
{
    velocity = _velocity;
}

qreal Obstacle::getTimeLapsed()
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
        deleteLater();
        qDebug() << "obstacle deleted";
    }
}

void Obstacle::parabolicMove()
{
    timer->stop();
    qreal X,Y;
    qreal initialX = x(), initialY = y();
    qreal initialVelocityX, initialVelocityY;

    initialVelocityX = velocity*qCos(angle);
    initialVelocityY = velocity*qSin(angle);

    X = initialX - initialVelocityX*timeLapsed;
    Y = initialY + (-initialVelocityY*timeLapsed) + (0.5*9.8*timeLapsed*timeLapsed);
   // X = velocity * qCos(angle) * timeLapsed * direction;
   // Y = (velocity * qSin(angle) * timeLapsed - 0.5 * 9.8 * qPow(timeLapsed, 2));
    setPos(X,Y);
    timeLapsed += 0.1;


    //this->setVelocity(this->getVelocity()+0.1);
    if(pos().x() + 10 < 0 || pos().x() +10 > 800){
        scene()->removeItem(this);
        delete this;
        qDebug() << "obstacle deleted";
    }
}
