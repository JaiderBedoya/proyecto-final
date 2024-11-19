#include "Enemy.h"
#include "Obstacle.h"

Enemy::Enemy() {}

Enemy::Enemy(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites): Character(characterWidth, characterHeight, spritePath, numberOfHorizontalSprites){
    setFlag(QGraphicsItem::ItemIsFocusable);

    //QTimer *timer = new QTimer();

    autonomousTimer = new QTimer();
    kamehamehaTimer = new QTimer();
    cannonBallTimer = new QTimer();
    rollTimer = new QTimer();
    aleatoryAttackTimer = new QTimer();

    connect(autonomousTimer, &QTimer::timeout, this, &Enemy::autonomousMovement);
    connect(aleatoryAttackTimer, &QTimer::timeout, this, &Enemy::aleatoryAttack);

    //Homer attacks

    connect(kamehamehaTimer, &QTimer::timeout, this, &Enemy::kamehamehaAttack);
    connect(cannonBallTimer, &QTimer::timeout, this, &Enemy::throwBullet);
    connect(rollTimer, &QTimer::timeout, this, &Enemy::roll);

    //connect(timer, &QTimer::timeout, this, &Enemy::increaseMovementDirection);  
    autonomousTimer->start(100);
    aleatoryAttackTimer->start(2000);


    this->setDirectionSprite(1);

    //timer->start(1000);

}

void Enemy::setAttacking(bool _attacking)
{
    attacking = _attacking;
}

bool Enemy::getAttacking()
{
    return attacking;
}

void Enemy::increaseMovementDirection()
{
    if(!movementTimer->isActive()){
        movementTimer->start(150);
    }
    this->setMovementDirection(this->getMovementDirection()+getCharacterHeight());
    if(this->getMovementDirection()>= getCharacterHeight()*8){
        this->setMovementDirection(0);
    }
}

void Enemy::autonomousMovement()
{
    if(this->getDirectionSprite() == 1){
        this->setMovementDirection(this->getCharacterHeight()*4);
    }
    else{
        qDebug()<<"direction sprite is different to 1";
        this->setMovementDirection(0);
    }
    movementTimer->start(100);

    this->setPos(x(),y()+moveValor);
    if(y() <= 340){
        moveValor = 10;
        qDebug() << "Bajando";
    }
    if(y()+this->getCharacterHeight() >= 600 && y() > 340){
        moveValor = -10;
        qDebug() << "Subiendo";
    }
}

void Enemy::aleatoryAttack(){
    unsigned short int randomNumber = QRandomGenerator::global()->bounded(3);

    switch (randomNumber) {

    case 0:
        if(cannonBallTimer->isActive()){
            cannonBallTimer->stop();
        }
        else if(rollTimer->isActive()){
            rollTimer->stop();
        }
        else if(kamehamehaTimer->isActive()){
            kamehamehaTimer->stop();
            kamehamehaTimer->start(1000);
        }
        else{
            kamehamehaTimer->start(1000);
        }

        break;
    case 1:
        if(cannonBallTimer->isActive()){
            cannonBallTimer->stop();
            cannonBallTimer->start(1000);
        }
        else if(rollTimer->isActive()){
            rollTimer->stop();
        }
        else if(kamehamehaTimer->isActive()){
            kamehamehaTimer->stop();
        }
        else{
            cannonBallTimer->start(1000);
        }

        break;
    case 2:
        if(cannonBallTimer->isActive()){
            cannonBallTimer->stop();
        }
        else if(rollTimer->isActive()){
            rollTimer->stop();
            rollTimer->start(30);
        }
        else if(kamehamehaTimer->isActive()){
            kamehamehaTimer->stop();
        }
        else{
            rollTimer->start(30);
        }
        break;
    default:
        qDebug()<< "an error happened";
        break;
    }
}

void Enemy::kamehamehaAttack()
{
    movementTimer->start(100);
    qDebug()<<"throwing kamehameha";
    autonomousTimer->stop();

    this->setDirectionSprite(-1);
    if(this->getDirectionSprite() == 1){
        this->setMovementDirection(this->getCharacterHeight());
    }
    else if(this->getDirectionSprite() == -1){
        this->setMovementDirection(this->getCharacterHeight()*5);
    }
    Obstacle  *kamehameha = new Obstacle(":/imagesEmancipation/KamehamehaParticle.png",30);
    if(this->getDirectionSprite() == 1){
        kamehameha->setDirection(1);
        kamehameha->setPos(x()+this->getCharacterWidth(),y()+(this->getCharacterHeight()/2));
    }
    else{
        kamehameha->setDirection(-1);
        kamehameha->setPos(x(),y()+(this->getCharacterHeight()/2));
    }
    scene()->addItem(kamehameha);
    autonomousTimer->start(1000);
}

void Enemy::throwBullet()
{
    movementTimer->start(100);
    qDebug()<<"throwing parabolic Bullet";
    autonomousTimer->stop();
    this->setDirectionSprite(-1);
    if(this->getDirectionSprite() == 1){
        this->setMovementDirection(this->getCharacterHeight()*3);
    }
    else if(this->getDirectionSprite() == -1){
        this->setMovementDirection(this->getCharacterHeight()*7);
    }

    Obstacle  *cannonBall = new Obstacle(":/imagesEmancipation/HomeroBullet.png",30);
    cannonBall->timerMovPar->start(50);
    if(this->getDirectionSprite() == 1){
        cannonBall->setDirection(1);
        cannonBall->setPos(x()+this->getCharacterWidth(),y()+(this->getCharacterHeight()/2));
    }
    else{
        cannonBall->setDirection(-1);
        cannonBall->setPos(x(),y()+(this->getCharacterHeight()/2));
    }
    scene()->addItem(cannonBall);
    autonomousTimer->start(1000);

}

void Enemy::roll()
{
    qDebug()<<"rolling around the map";
    autonomousTimer->stop();
    movementTimer->start(20);
    if(this->getDirectionSprite() == 1){
        this->setMovementDirection(this->getCharacterHeight()*2);
    }
    else if(this->getDirectionSprite() == -1){
        this->setMovementDirection(this->getCharacterHeight()*6);
    }

    this->setPos(x()+moveValor,y());
    if(x() <= 0){
        moveValor = 20;
        qDebug() << "Girando a la derecha";
        this->setDirectionSprite(1);
    }
    if(x()+this->getCharacterWidth() >= 800){
        moveValor = -20;
        qDebug() << "Girando a la izquierda";
        this->setDirectionSprite(-1);
    }

}
