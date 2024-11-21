#include "Obstacle.h"

qreal Obstacle::getSizeObstacle()
{
    return sizeObstacle;
}

Obstacle::Obstacle(const QString& obstacleImage, qreal size){
    //drawing the rectangle
    QPixmap projectileImage(obstacleImage);
    this->setSizeObstacle(size);
    QPixmap redimensionedImage = projectileImage.scaled(size, size, Qt::KeepAspectRatio);
    setPixmap(redimensionedImage);
    //connect
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timerMovPar = new QTimer(this);
    connect(timerMovPar, &QTimer::timeout, this, [=]() {
        parabolicMove();
    });
    velocity = 15;
    angle = 45;
    angle = angle*M_PI/180;
    timer->start(20);
}

void Obstacle::setSizeObstacle(qreal _sizeObstacle)
{
    sizeObstacle = _sizeObstacle;
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
    //checking collision
    checkCollision();

}

void Obstacle::parabolicMove()
{
    timer->stop();
    qreal X,Y;
    qreal initialX = x(), initialY = y();
    qreal initialVelocityX, initialVelocityY;

    initialVelocityX = velocity*qCos(angle);
    initialVelocityY = velocity*qSin(angle);

    X = initialX + (initialVelocityX*timeLapsed)*direction;
    Y = initialY + (-initialVelocityY*timeLapsed) + (0.5*9.8*timeLapsed*timeLapsed);
    setPos(X,Y);
    timeLapsed += 0.1;


    //this->setVelocity(this->getVelocity()+0.1);
    if(pos().x() + 10 < 0 || pos().x() +10 > 800){
        scene()->removeItem(this);
        deleteLater();
        qDebug() << "obstacle deleted";
    }
    //checking collision
    checkCollision();
}

void Obstacle::checkCollision(){
    QList<QGraphicsItem *> collidingBullets = collidingItems();
    for(unsigned short int i = 0; i < collidingBullets.size();i++){


        if(typeid(*(collidingBullets[i])) == typeid(Enemy) && this->getSizeObstacle() == 10){

            Enemy* enemyColliding = dynamic_cast<Enemy*>(collidingBullets[i]);
            if (enemyColliding) {

                enemyColliding->setHealth((enemyColliding->getHealth()-2));
                enemyColliding->setHomerHealthBar((enemyColliding->getHealth()-2));
                //Homero lost
                if (enemyColliding->getHealth() <= 0) {
                    enemyColliding->setHomerHealthBar(0);
                    scene()->removeItem(enemyColliding);
                    delete enemyColliding;
                }
                scene()->removeItem(this);
                deleteLater();
            }
        }
        else if(typeid(*(collidingBullets[i])) == typeid(Protagonist) && this->getSizeObstacle() == 30){

            Protagonist* protagonistReceivingDamage = dynamic_cast<Protagonist*>(collidingBullets[i]);

            if (protagonistReceivingDamage) {

                protagonistReceivingDamage->setHealth((protagonistReceivingDamage->getHealth()-20));
                protagonistReceivingDamage->setBartHealthBar((protagonistReceivingDamage->getHealth()-20));

                //Bart Lost
                if (protagonistReceivingDamage->getHealth() <= 0) {
                    protagonistReceivingDamage->setBartHealthBar(0);
                    scene()->removeItem(protagonistReceivingDamage);
                    delete protagonistReceivingDamage;
                }
                scene()->removeItem(this);
                deleteLater();
            }

        }
    }
}
