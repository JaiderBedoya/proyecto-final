#include "Obstacle.h"

Obstacle::Obstacle(){

}

Obstacle::Obstacle(const QString& obstacleImage, qreal size, qreal sizeHeight, QString _identificator, unsigned short int _obstacleLevel) :identificator(_identificator), rotate(false), obstacleLevel(_obstacleLevel){

    QPixmap projectileImage(obstacleImage);

    this->setSizeObstacle(size);

    QPixmap redimensionedImage = projectileImage.scaled(size, sizeHeight, Qt::KeepAspectRatio);

    setPixmap(redimensionedImage);

    timer = new QTimer();
    timerMovPar = new QTimer();
    oscillatoryTimer = new QTimer();
    circularTimer = new QTimer();

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(timerMovPar, &QTimer::timeout, this, [=]() {
        parabolicMove();
    });

    connect(oscillatoryTimer,SIGNAL(timeout()),this,SLOT(oscillatoryMove()));
    connect(circularTimer,SIGNAL(timeout()),this,SLOT(circularMovement()));

    velocity = 15;
    angle = 45;
    angle = angle*M_PI/180;
}

Obstacle::~Obstacle(){
}

qreal Obstacle::getSizeObstacle()
{
    return sizeObstacle;
}
qreal Obstacle::getSizeHeight(){
    return sizeHeight;
}

qreal Obstacle::getAmplitude()
{
    return amplitude;
}

unsigned short int Obstacle::getObstacleLevel(){
    return obstacleLevel;
}

short Obstacle::getDirection()
{
    return direction;
}

qreal Obstacle::getAngle()
{
    return angle;
}

qreal Obstacle::getFrequency()
{
    return frequency;
}

bool Obstacle::getRotate(){
    return rotate;
}

QString Obstacle::getIdentificator()
{
    return identificator;
}

qreal Obstacle::getTimeLapsed()
{
    return timeLapsed;
}

qreal Obstacle::getVelocity()
{
    return velocity;
}

void Obstacle::setAmplitude(qreal _amplitude)
{
    amplitude = _amplitude;
}

void Obstacle::setFrequency(qreal _frequency)
{
    frequency = _frequency;
}

void Obstacle::setAngle(qreal _angle)
{
    angle = _angle;
}

void Obstacle::setRotate(bool _rotate)
{
    rotate = _rotate;
}

void Obstacle::setSizeHeight(qreal _sizeHeight)
{
    sizeHeight = _sizeHeight;
}

void Obstacle::setObstacleLevel(unsigned short _obstacleLevel)
{
    obstacleLevel = _obstacleLevel;
}

void Obstacle::setIdentificator(const QString &_identificator)
{
    identificator = _identificator;
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



void Obstacle::move()
{
    setPos(x() + (velocity*direction) ,y());
    if(pos().x() + this->getSizeObstacle() < 0 || pos().x() + this->getSizeObstacle() > 800){
        scene()->removeItem(this);
        deleteLater();
        qDebug() << "obstacle deleted";
    }
    checkCollision();
}

void Obstacle::parabolicMove()
{
    qreal X,Y;
    qreal initialX = x(), initialY = y();
    qreal initialVelocityX, initialVelocityY;

    initialVelocityX = velocity*qCos(angle);
    initialVelocityY = velocity*qSin(angle);

    X = initialX + (initialVelocityX*timeLapsed)*direction;
    Y = initialY + (-initialVelocityY*timeLapsed) + (0.5*9.8*timeLapsed*timeLapsed);
    setPos(X,Y);
    timeLapsed += 0.1;
    if(pos().x() + this->getSizeObstacle() < 0 || pos().x() + this->getSizeObstacle() > 800){
        scene()->removeItem(this);
        deleteLater();
        qDebug() << "obstacle deleted";
    }
    checkCollision();
}


void Obstacle::oscillatoryMove(){

    this->setDirection(-1);
    qreal X,Y;
    qreal initialX = x(), initialY = y();
    frequency = 0.8;
    amplitude = 5;
    qreal W = (2 * M_PI * frequency);
    X = initialX + ((velocity*qSin(angle))*timeLapsed)*direction;
    Y = initialY - amplitude*(qSin(W*timeLapsed));

    setPos(X,Y);
    if(rotate){
        qreal currentRotation = this->rotation();
        this->setRotation(currentRotation + 20);
    }

    timeLapsed += 0.016;

    if(pos().x() + this->getSizeObstacle() < 0 || pos().x() + this->getSizeObstacle() > 800){
        if (!(this->scene() == nullptr)) {
            scene()->removeItem(this);
            deleteLater();
            qDebug() << "obstacle deleted";
        }

    }
    checkCollision();
}

void Obstacle::circularMovement(){
    this->timer->start(30);
    this->setDirection(-1);
    qreal X,Y;
    qreal initialX = x(), initialY = y();
    frequency = 0.8;
    amplitude = 5;
    qreal W = (2 * M_PI * frequency);
    X = initialX + (amplitude*(qCos(W*timeLapsed))*direction);
    Y = initialY - amplitude*(qSin(W*timeLapsed));

    setPos(X,Y);
    if(rotate){
        qreal currentRotation = this->rotation();
        this->setRotation(currentRotation + 20);
    }

    timeLapsed += 0.016;

    if(pos().x() + this->getSizeObstacle() < 0 || pos().x() + this->getSizeObstacle() > 800){
        if (!(this->scene() == nullptr)) {
            scene()->removeItem(this);
            deleteLater();
            qDebug() << "obstacle deleted";
        }

    }
    checkCollision();

}

void Obstacle::checkCollision(){
    QList<QGraphicsItem *> collidingItemsWithObstacle = collidingItems();
    for(unsigned short int i = 0; i < collidingItemsWithObstacle.size();i++){

        if(this->getObstacleLevel() == 1){
            if(typeid(*(collidingItemsWithObstacle[i])) == typeid(Enemy) && this->getIdentificator() == "rock"){

                Enemy* enemyColliding = dynamic_cast<Enemy*>(collidingItemsWithObstacle[i]);
                if (enemyColliding) {

                    enemyColliding->setHealth((enemyColliding->getHealth()-2));
                    enemyColliding->setHomerHealthBar((enemyColliding->getHealth()-2));
                    //Homero lost
                    if (enemyColliding->getHealth() <= 0) {
                        enemyColliding->setHomerHealthBar(0);
                        enemyColliding->emitWinOrLost(true,1);
                    }
                    else{
                        scene()->removeItem(this);
                        deleteLater();
                    }
                }
            }
            else if(typeid(*(collidingItemsWithObstacle[i])) == typeid(Bart) && (this->getIdentificator() == "kamehameha" || this->getIdentificator() == "cannonBullet")){

                Bart* protagonistReceivingDamage = dynamic_cast<Bart*>(collidingItemsWithObstacle[i]);

                if (protagonistReceivingDamage) {

                    protagonistReceivingDamage->setHealth((protagonistReceivingDamage->getHealth()-20));
                    protagonistReceivingDamage->setBartHealthBar((protagonistReceivingDamage->getHealth()-20));

                    //Bart Lost
                    if (protagonistReceivingDamage->getHealth() <= 0) {
                        qDebug()<<"Bart perdio y se ejecuta lo proximo";
                        protagonistReceivingDamage->setBartHealthBar(0);
                        protagonistReceivingDamage->emitWinOrLost(false,1);
                    }
                    else{
                        scene()->removeItem(this);
                        deleteLater();
                    }
                }
            }
        }

        else if(this->getObstacleLevel() == 2){
            if(typeid(*(collidingItemsWithObstacle[i])) == typeid(Homero) && this->getIdentificator() == "coin"){

                Homero* homeroGiveCoin = dynamic_cast<Homero*>(collidingItemsWithObstacle[i]);
                if (homeroGiveCoin) {
                    homeroGiveCoin->increaseScore(1);

                    //Homero win
                    if(homeroGiveCoin->getScoreGame() == 50){
                        homeroGiveCoin->emitWinOrLost(true,2);
                    }
                    else{
                        scene()->removeItem(this);
                        deleteLater();
                        qDebug() << "obstacle deleted";
                    }

                }
            }
            else if(typeid(*(collidingItemsWithObstacle[i])) == typeid(Homero) && (this->getIdentificator() == "duff" || this->getIdentificator() == "rocket" || this->getIdentificator() == "skate" || this->getIdentificator() == "skateRail")){
                Homero* homeroColliding = dynamic_cast<Homero*>(collidingItemsWithObstacle[i]);
                if(homeroColliding){

                    if(this->getIdentificator() == "skateRail"){
                        homeroColliding->setHealth((homeroColliding->getHealth()-5));
                        homeroColliding->setHomerHealthBar((homeroColliding->getHealth()-5));
                    }
                    else{
                        scene()->removeItem(this);
                        deleteLater();
                        qDebug() << "obstacle deleted";
                        homeroColliding->setHealth((homeroColliding->getHealth()-15));
                        homeroColliding->setHomerHealthBar((homeroColliding->getHealth()-15));
                    }
                    //Homero lost
                    if (homeroColliding->getHealth() <= 0) {
                        homeroColliding->setHomerHealthBar(0);
                        homeroColliding->emitWinOrLost(false,2);
                    }
                }
            }
        }
    }
}
