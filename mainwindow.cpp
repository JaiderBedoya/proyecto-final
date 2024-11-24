#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), firstBackGround(nullptr) , secondBackGround(nullptr), backGroundWidth(0), scrollSpeed(5)
{
    ui->setupUi(this);

    secondLevelScene();

    /*
    firstLevelScene();
    qDebug()<<"Se finalizo el primer nivel";
    */
}

void MainWindow::firstLevelScene(){

    //Create a scene
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(0,30,800,600);

    QPixmap* bartAndHomerFace = new QPixmap(":/imagesEmancipation/Bart y homero FotosCara.png");

    QPixmap* bartFace = new QPixmap(bartAndHomerFace->copy(0, 0, 230, 315));
    QPixmap* homerFace = new QPixmap(bartAndHomerFace->copy(230,0,230,315));
    QPixmap* scaledBartFace = new QPixmap(bartFace->scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QPixmap* scaledHomerFace = new QPixmap(homerFace->scaled(50,50,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QGraphicsPixmapItem* bartFaceItem = new QGraphicsPixmapItem(*scaledBartFace);
    QGraphicsPixmapItem* homerFaceItem = new QGraphicsPixmapItem(*scaledHomerFace);
    bartFaceItem->setPos(20, 40);
    homerFaceItem->setPos(800-70,40);
    scene->addItem(bartFaceItem);
    scene->addItem(homerFaceItem);


    //Create an enemy and the protagonist
    Bart *player = new Bart(70.33,88.75,":/imagesEmancipation/bartConAtaque.png",6);
    Enemy *enemy = new Enemy(90,99,":/imagesEmancipation/SpriteHomeroCompleto.png",8);

    //adding items to our scene
    scene->addItem(player);
    scene->addItem(enemy);

    QGraphicsProxyWidget* bartHealthBarProxy = scene->addWidget(player->getBartHealthBar());
    bartHealthBarProxy->setPos(70, 65);

    QGraphicsProxyWidget* homerHealthBarProxy = scene->addWidget(enemy->getHomerHealthBar());
    homerHealthBarProxy->setPos(800-280,65);


    //make player focusable for the key press events
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->graphicsView->show();
    ui->graphicsView->setFixedSize(800,600);

    QPixmap backGroundPixmap(":/imagesEmancipation/simpsons house.jfif");
    QBrush backGroundBrush(backGroundPixmap.scaled(ui->graphicsView->size(), Qt::KeepAspectRatioByExpanding));
    ui->graphicsView->setBackgroundBrush(backGroundBrush);

    player->setPos(10,500);
    enemy->setPos(700,480);

    QMediaPlayer* music = new QMediaPlayer;
    music->setSource(QUrl("qrc:/sounds/soundsEmancipation/television-closing-theme.mp3"));
    QAudioOutput* audioOutput = new QAudioOutput(this);

    music->setAudioOutput(audioOutput);
    audioOutput->setVolume(1.0);
    music->play();

    connect(music, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            music->setPosition(0);
            music->play();
        }
    });
}

void MainWindow::secondLevelScene(){

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    Homero *homero = new Homero(80.16,154,":/imagesEmancipation/HomeroSkate.png",6);

    //QGraphicsProxyWidget* homerHealthBarProxy = scene->addWidget(homero->getHomerHealthBar());
    //homerHealthBarProxy->setPos(70, 65);


    QPixmap backGroundPixmap(":/imagesEmancipation/SkateParkBackGroundOne.png");

    backGroundWidth = backGroundPixmap.width();

    firstBackGround = scene->addPixmap(backGroundPixmap);
    secondBackGround = scene->addPixmap(backGroundPixmap);

    firstBackGround->setPos(0, 0);
    secondBackGround->setPos(backGroundWidth, 0);

    ui->graphicsView->setFixedSize(backGroundWidth, backGroundPixmap.height());
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->show();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::scrollBackground);
    timer->start(30);


    homero->setFlag(QGraphicsItem::ItemIsFocusable);

    scene->addItem(homero);
    homero->setPos(10,300);

    QPixmap* bartAndHomerFace = new QPixmap(":/imagesEmancipation/Bart y homero FotosCara.png");
    QPixmap* coin = new QPixmap(":/imagesEmancipation/images-removebg-preview.png");
    QPixmap* scaledCoin = new QPixmap(coin->scaled(50,50,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QGraphicsPixmapItem* coinScore = new QGraphicsPixmapItem(*scaledCoin);
    coinScore->setPos(800-100,20);
    scene->addItem(coinScore);


    QPixmap* homerFace = new QPixmap(bartAndHomerFace->copy(230,0,230,315));
    QPixmap* scaledHomerFace = new QPixmap(homerFace->scaled(50,50,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QGraphicsPixmapItem* homerFaceItem = new QGraphicsPixmapItem(*scaledHomerFace);
    homerFaceItem->setPos(20,20);
    scene->addItem(homerFaceItem);

    QTimer* spawnRandomObstacleTimer = new QTimer();
    connect(spawnRandomObstacleTimer, &QTimer::timeout, this, &MainWindow::spawnRandomObstacle);


    scoreItem = new QGraphicsTextItem("X"+ QString::number(homero->getScoreGame()));
    scoreItem->setDefaultTextColor(Qt::white);
    scoreItem->setFont(QFont("Arial", 20));
    scoreItem->setPos(800-50,35);
    scene->addItem(scoreItem);

    connect(homero, &Homero::scoreChanged, this, &MainWindow::updateScore);


    spawnRandomObstacleTimer->start(2000);

}

void MainWindow::setBackGroundWidth(unsigned short _backGroundWidth)
{
    backGroundWidth = _backGroundWidth;
}

void MainWindow::setScrollSpeed(unsigned short _scrollSpeed)
{
    scrollSpeed = _scrollSpeed;
}

unsigned short MainWindow::getBackGroundWidth()
{
    return backGroundWidth;
}

unsigned short MainWindow::getScrollSpeed()
{
    return scrollSpeed;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::scrollBackground() {

    firstBackGround->moveBy(-scrollSpeed, 0);
    secondBackGround->moveBy(-scrollSpeed, 0);

    if (firstBackGround->x() + backGroundWidth <= 0) {
        firstBackGround->setPos(secondBackGround->x() + backGroundWidth, 0);
    }
    if (secondBackGround->x() + backGroundWidth <= 0) {
        secondBackGround->setPos(firstBackGround->x() + backGroundWidth, 0);
    }
}

void MainWindow::updateScore(int newScore){
    scoreItem->setPlainText("X" + QString::number(newScore));
}

void MainWindow::spawnRandomObstacle(){

    unsigned short int randomNumber = QRandomGenerator::global()->bounded(3);
    unsigned short int randomYPosition = QRandomGenerator::global()->bounded(100,500);
    Obstacle* obstacle = new Obstacle(":/imagesEmancipation/duff-removebg-preview.png",50,100,"duff");
    Obstacle* obstacle2 = new Obstacle(":/imagesEmancipation/images-removebg-preview.png",40,40,"coin");
    Obstacle* obstacle3 = new Obstacle(":/imagesEmancipation/HomeroBullet.png",40,40,"cannonBullet");

    switch (randomNumber) {
    case 0:

        ui->graphicsView->scene()->addItem(obstacle);
        obstacle->setPos(750,300);
        obstacle->oscillatoryTimer->start(50);
        /*
        ui->graphicsView->scene()->addItem(obstacle2);
        obstacle2->setPos(750,randomYPosition);
        obstacle2->timer->start(50);
        obstacle2->setDirection(-1);
        */
        break;
    case 1:

        ui->graphicsView->scene()->addItem(obstacle2);
        obstacle2->setPos(750,randomYPosition);
        obstacle2->timer->start(50);
        obstacle2->setDirection(-1);


        break;
    case 2:
        /*
        ui->graphicsView->scene()->addItem(obstacle3);
        obstacle3->setPos(750,0);
        obstacle3->timerMovPar->start(50);
        obstacle3->setDirection(-1);
        obstacle3->setAngle(0);
        */
        ui->graphicsView->scene()->addItem(obstacle2);
        obstacle2->setPos(750,randomYPosition);
        obstacle2->timer->start(50);
        obstacle2->setDirection(-1);
        break;
    default:
        break;
    }
}



