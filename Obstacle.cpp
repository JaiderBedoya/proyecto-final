#include "Obstacle.h"

Obstacle::Obstacle(){
    //drawing the rectangle
    QPixmap projectile(":/imagesEmancipation/bullet.png");
    QPixmap redimensionedImage = projectile.scaled(20, 20, Qt::KeepAspectRatio);
    setPixmap(redimensionedImage);
    //connect
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(5);
}

void Obstacle::move()
{
    //moving the obstacle up and rigth/left
    setPos(x()+1,y());
    if(pos().y() + 10 < 0){
        scene()->removeItem(this);
        delete this;
        qDebug() << "obstacle deleted";
    }
}
