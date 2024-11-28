#include "Bart.h"
#include "Obstacle.h"

QProgressBar *Bart::getBartHealthBar()
{
    return bartHealthBar;
}

void Bart::setBartHealthBar(int _healthBar)
{
    bartHealthBar->setValue(_healthBar);
    if(this->getHealth()< 100 && ayCaramba){
        QMediaPlayer* music = new QMediaPlayer;
        music->setSource(QUrl("qrc:/sounds/soundsEmancipation/ay-caramba.mp3"));
        QAudioOutput* audioOutput = new QAudioOutput(this);

        music->setAudioOutput(audioOutput);
        audioOutput->setVolume(0.5);
        music->play();
        this->setAyCaramba(false);
        ayCarambaTimer->start(500);
    }
}

void Bart::setCanShoot(bool _canShoot)
{
    canShoot = _canShoot;
}

void Bart::setAyCaramba(bool _ayCaramba)
{
    ayCaramba = _ayCaramba;
}

bool Bart::getAyCaramba()
{
    return ayCaramba;
}

bool Bart::getCanShoot()
{
    return canShoot;
}

Bart::Bart() {

}
Bart::Bart(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites): Character(characterWidth, characterHeight, spritePath, numberOfHorizontalSprites){
    setFlag(QGraphicsItem::ItemIsFocusable);

    movementUpdateTimer = new QTimer(this);
    connect(movementUpdateTimer, &QTimer::timeout, this, &Bart::updateMovement);
    movementUpdateTimer->start(16);

    shootCooldownTimer = new QTimer(this);
    shootCooldownTimer->setSingleShot(true);
    ayCarambaTimer = new QTimer(this);
    ayCarambaTimer->setSingleShot(true);

    connect(shootCooldownTimer, &QTimer::timeout, this, &Bart::resetShootCooldown);
    connect(ayCarambaTimer, &QTimer::timeout, this, &Bart::ayCarambaCooldown);
    this->setAyCaramba(true);
    this->setCanShoot(true);

    bartHealthBar= new QProgressBar();
    bartHealthBar->setRange(0, 100);
    bartHealthBar->setValue(this->getHealth());
    bartHealthBar->setTextVisible(false);

}

void Bart::keyPressEvent(QKeyEvent *event){
    activeKeys.insert(event->key());
}
void Bart::keyReleaseEvent(QKeyEvent *event)
{
    activeKeys.remove(event->key());
}

void Bart::updateMovement()
{
    if (activeKeys.contains(Qt::Key_A)) {

        this->setDirectionSprite(-1);

        if(pos().x() > 0)
            setPos(x()-5,y());

        this->setMovementDirection(266.25);
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
        qDebug() << "You pressed the A key";
    }

    if (activeKeys.contains(Qt::Key_D)) {

        this->setDirectionSprite(1);
        if(pos().x() + this->getCharacterWidth() < 800)
            setPos(x()+5,y());
        this->setMovementDirection(0);
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
    }

    if (activeKeys.contains(Qt::Key_W)) {

        if(pos().y() > 340)
            setPos(x(),y()-5);
        this->setMovementDirection(177.5);
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
    }

    if (activeKeys.contains(Qt::Key_S)) {

        if(pos().y() + this->getCharacterHeight() < 600)
            setPos(x(),y()+5);
        this->setMovementDirection(88.75);
        if(!movementTimer->isActive()){
            movementTimer->start(100);
        }
    }

    if (activeKeys.contains(Qt::Key_Space)) {
        if(canShoot){
            this->setMovementDirection(355);
            (this->getDirectionSprite() == 1) ? counterSprite = 0 : counterSprite = 3;

            if(!movementTimer->isActive()){
                movementTimer->start(100);
            }
        //create obstacle
        Obstacle  *projectile = new Obstacle(":/imagesEmancipation/BartBullet.png",10,10,"rock",1);
        projectile->timer->start(20);

        if(this->getDirectionSprite() == 1){
            projectile->setDirection(1);
            projectile->setPos(x()+this->getCharacterWidth(),y()+(this->getCharacterHeight()/2));
        }
        else{
            projectile->setDirection(-1);
            projectile->setPos(x(),y()+(this->getCharacterHeight()/2));
        }

        scene()->addItem(projectile);
        qDebug() << "Obstacle created";
        this->setCanShoot(false);
        shootCooldownTimer->start(1000);
        }
    }
}

void Bart::resetShootCooldown()
{
    this->setCanShoot(true);
    shootCooldownTimer->stop();
}

void Bart::ayCarambaCooldown(){
    this->setAyCaramba(true);
    ayCarambaTimer->stop();
}
