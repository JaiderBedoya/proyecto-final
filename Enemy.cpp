#include "Enemy.h"
#include "Obstacle.h"

QProgressBar *Enemy::getHomerHealthBar()
{
    return homerHealthBar;
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
    aleatoryAttackTimer->start(1000);

    this->setDirectionSprite(-1);

    homerHealthBar = new QProgressBar();
    homerHealthBar->setRange(0, 100);
    homerHealthBar->setValue(this->getHealth());
    homerHealthBar->setTextVisible(false);

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
    this->checkProtagonistCollision();
    if(y() <= 340){
        moveValor = 10;
        qDebug() << "Bajando";
    }
    if(y()+this->getCharacterHeight() >= 580 && y() > 340){
        moveValor = -10;
        qDebug() << "Subiendo";
    }
}

void Enemy::aleatoryAttack(){
    qDebug()<<this->getHealth();
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

    Obstacle  *kamehameha = new Obstacle(":/imagesEmancipation/KamehamehaParticle.png",30);

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
    qDebug()<<"throwing parabolic Bullet";
    autonomousTimer->stop();

    Obstacle  *cannonBall = new Obstacle(":/imagesEmancipation/HomeroBullet.png",30);
    cannonBall->setDirection(this->getDirectionSprite());
    cannonBall->timerMovPar->start(50);

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
        qDebug()<<"Stop";
        rollCounter = 0;
        aleatoryAttackTimer->start(1000);
        autonomousTimer->start(100);
        movementTimer->start(100);
        rollTimer->stop();
    }
    else{
    qDebug()<<"rolling around the map";
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
    this->checkProtagonistCollision();
    if(x() <= 0){
        moveValor = 20;
        qDebug() << "Girando a la derecha";
        rollCounter++;
        this->setDirectionSprite(1);
    }
    if(x()+this->getCharacterWidth() >= 800){
        moveValor = -20;
        qDebug() << "Girando a la izquierda";
        rollCounter++;
        this->setDirectionSprite(-1);
    }
    }
}

void Enemy::checkProtagonistCollision(){

    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (unsigned short int i = 0; i < collidingItemsList.size(); i++) {
        //Collision with bart
        if (typeid(*(collidingItemsList[i])) == typeid(Protagonist)) {
            Protagonist* bart = dynamic_cast<Protagonist*>(collidingItemsList[i]);
            if (bart) {
                bart->setHealth(bart->getHealth() - 2);
                bart->setBartHealthBar(bart->getHealth()-2);

                if (bart->getHealth() <= 0) {
                     bart->setBartHealthBar(0);
                    scene()->removeItem(bart);
                    delete bart;
                    qDebug() << "Protagonist defeated!";
                }
        }
        }
    }
}

