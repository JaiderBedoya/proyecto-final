#include "Enemy.h"
#include "Obstacle.h"

Enemy::Enemy() {}

Enemy::Enemy(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites): Character(characterWidth, characterHeight, spritePath, numberOfHorizontalSprites){
    setFlag(QGraphicsItem::ItemIsFocusable);

    autonomousTimer = new QTimer();
    kamehamehaTimer = new QTimer();
    cannonBallTimer = new QTimer();
    rollTimer = new QTimer();
    aleatoryAttackTimer = new QTimer();

    connect(autonomousTimer, &QTimer::timeout, this, &Enemy::autonomousMovement);
    connect(aleatoryAttackTimer, &QTimer::timeout, this, &Enemy::aleatoryAttack);

    //Timers of Homer attacks

    connect(kamehamehaTimer, &QTimer::timeout, this, &Enemy::kamehamehaAttack);
    connect(cannonBallTimer, &QTimer::timeout, this, &Enemy::throwBullet);
    connect(rollTimer, &QTimer::timeout, this, &Enemy::roll);

    autonomousTimer->start(100);
    aleatoryAttackTimer->start(1000);

    this->setDirectionSprite(-1);

    homerHealthBar = new QProgressBar();
    homerHealthBar->setRange(0, 100);
    homerHealthBar->setValue(this->getHealth());
    homerHealthBar->setTextVisible(false);
}

Enemy::~Enemy()
{
}

QProgressBar *Enemy::getHomerHealthBar()
{
    return homerHealthBar;
}

qreal Enemy::getMoveValor()
{
    return moveValor;
}

bool Enemy::getAttacking()
{
    return attacking;
}

unsigned short Enemy::getRollCounter()
{
    return rollCounter;
}

void Enemy::setRollCounter(unsigned short _rollCounter)
{
    rollCounter = _rollCounter;
}

void Enemy::setAttacking(bool _attacking)
{
    attacking = _attacking;
}

void Enemy::setMoveValor(qreal _moveValor)
{
    moveValor = _moveValor;
}

void Enemy::setHomerHealthBar(int newHealthBar)
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

void Enemy::autonomousMovement()
{
    if(x() <= 200){
        this->setDirectionSprite(-1);
    }
    else if(x() >= 400){
        this->setDirectionSprite(1);
    }
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
        this->setMoveValor(10);
        qDebug() << "Bajando";
    }
    if(y()+this->getCharacterHeight() >= 580 && y() > 340){
        this->setMoveValor(-10);
        qDebug() << "Subiendo";
    }
    this->checkProtagonistCollision();
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

    if(x() <= 200){
        this->setDirectionSprite(1);
    }
    else if(x() >= 400){
        this->setDirectionSprite(-1);
    }

    qDebug()<<"throwing kamehameha";
    autonomousTimer->stop();
    movementTimer->start();
    if(this->getDirectionSprite() == 1){
        this->setMovementDirection(this->getCharacterHeight());
    }
    else if(this->getDirectionSprite() == -1){
        this->setMovementDirection(this->getCharacterHeight()*5);
    }

    QTimer *oneShotTimer = new QTimer();
    oneShotTimer->setSingleShot(true);
    connect(oneShotTimer, &QTimer::timeout, this, &Enemy::createKamehameha);
    oneShotTimer->start(800);

    autonomousTimer->start(1000);
}


void Enemy::createKamehameha(){

    Obstacle  *kamehameha = new Obstacle(":/imagesEmancipation/KamehamehaParticle.png",30,30,"kamehameha",1);
    kamehameha->timer->start(20);
    kamehameha->setVelocity(25);

    if(this->getDirectionSprite() == 1){
        kamehameha->setDirection(1);
        kamehameha->setPos(x()+this->getCharacterWidth(),y()+(this->getCharacterHeight()/2));
    }
    else if(this->getDirectionSprite() == -1){
        kamehameha->setDirection(-1);
        kamehameha->setPos(x(),y()+(this->getCharacterHeight()/2));
    }
    scene()->addItem(kamehameha);
}


void Enemy::throwBullet()
{
    if(x() <= 200){
        this->setDirectionSprite(-1);
    }
    else if(x() >= 400){
        this->setDirectionSprite(1);
    }

    movementTimer->start(70);
    autonomousTimer->stop();

    Obstacle  *cannonBall = new Obstacle(":/imagesEmancipation/HomeroBullet.png",30,30,"cannonBullet",1);
    cannonBall->setDirection(this->getDirectionSprite());
    cannonBall->timerMovPar->start(35);

    if(this->getDirectionSprite() == 1){
        this->setMovementDirection(this->getCharacterHeight()*7);
        cannonBall->setDirection(-1);
        cannonBall->setPos(x(),y()+(this->getCharacterHeight()/2));
    }

    else if(this->getDirectionSprite() == -1){
        this->setMovementDirection(this->getCharacterHeight()*3);
        cannonBall->setDirection(1);
        cannonBall->setPos(x()+this->getCharacterWidth(),y()+(this->getCharacterHeight()/2));
    }
    scene()->addItem(cannonBall);

    autonomousTimer->start(1000);
}

void Enemy::roll()
{
    if(x() <= 200){
        this->setDirectionSprite(-1);
    }
    else if(x() >= 400){
        this->setDirectionSprite(1);
    }
    if(rollCounter == 3){
        this->setRollCounter(0);
        aleatoryAttackTimer->start(1000);
        autonomousTimer->start(100);
        movementTimer->start(100);
        rollTimer->stop();
    }
    else{
    autonomousTimer->stop();
    aleatoryAttackTimer->stop();
    movementTimer->start(20);


    if(this->getDirectionSprite() == 1){
        this->setMovementDirection(this->getCharacterHeight()*2);

    }
    else if(this->getDirectionSprite() == -1){
        this->setMovementDirection(this->getCharacterHeight()*6);

    }

    this->setPos(x()+moveValor,y());

    if(x() <= 0){
        this->setMoveValor(20);
        this->setRollCounter(this->getRollCounter()+1);
        this->setDirectionSprite(1);
    }
    if(x()+this->getCharacterWidth() >= 800){
        this->setMoveValor(-20);
        this->setRollCounter(this->getRollCounter()+1);
        this->setDirectionSprite(-1);
    }
    this->checkProtagonistCollision();
    }
}

void Enemy::checkProtagonistCollision(){

    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (unsigned short int i = 0; i < collidingItemsList.size(); i++) {
        //Collision with bart
        if (typeid(*(collidingItemsList[i])) == typeid(Bart)) {
            Bart* bart = dynamic_cast<Bart*>(collidingItemsList[i]);
            if (bart) {
                bart->setHealth(bart->getHealth() - 2);
                bart->setBartHealthBar(bart->getHealth()-2);

                if (bart->getHealth() <= 0) {
                    bart->setBartHealthBar(0);
                    bart->emitWinOrLost(false,1);
                    qDebug() << "Bart defeated!";
                }
            }
        }
    }
}

