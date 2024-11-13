#include "Obstacle.h"

Obstacle::Obstacle(){
    //drawing the rectangle
    QPixmap projectileImage(":/imagesEmancipation/bullet.png");
    QPixmap redimensionedImage = projectileImage.scaled(20, 20, Qt::KeepAspectRatio);
    setPixmap(redimensionedImage);
    //connect
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(5);
}

void Obstacle::setDirection(short int _direction){
    direction = _direction;
}

void Obstacle::move()
{
    //moving the obstacle up and rigth/left
    setPos(x() + (1.7*direction) ,y());
    if(pos().x() + 10 < 0 || pos().x() +10 > 800){
        scene()->removeItem(this);
        delete this;
        qDebug() << "obstacle deleted";
    }
}
