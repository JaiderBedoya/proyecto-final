#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), firstBackGround(nullptr) , secondBackGround(nullptr), backGroundWidth(0), scrollSpeed(5), firstLevelCreated(false), secondLevelCreated(false)
{
    ui->setupUi(this);
    this->statusBar()->hide();
    this->setGeometry(80,80,800,600);
    mainMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

unsigned short MainWindow::getBackGroundWidth()
{
    return backGroundWidth;
}

unsigned short MainWindow::getScrollSpeed()
{
    return scrollSpeed;
}

bool MainWindow::getFirstLevelCreated()
{
    return firstLevelCreated;
}

bool MainWindow::getSecondLevelCreated(){
    return secondLevelCreated;
}

void MainWindow::setFirstLevelCreated(bool _firstLevelCreated)
{
    firstLevelCreated = _firstLevelCreated;
}

void MainWindow::setSecondLevelCreated(bool _secondLevelCreated){
    secondLevelCreated = _secondLevelCreated;
}

void MainWindow::setBackGroundWidth(unsigned short _backGroundWidth)
{
    backGroundWidth = _backGroundWidth;
}

void MainWindow::setScrollSpeed(unsigned short _scrollSpeed)
{
    scrollSpeed = _scrollSpeed;
}


void MainWindow::firstLevelScene(){
    this->setFirstLevelCreated(true);

    sceneLevelOne = new QGraphicsScene(this);
    sceneLevelOne->setSceneRect(0,0,800,600);

    bartAndHomerFace = new QPixmap(":/imagesEmancipation/Bart y homero FotosCara.png");

    bartFace = new QPixmap(bartAndHomerFace->copy(0, 0, 230, 315));
    homerFace = new QPixmap(bartAndHomerFace->copy(230,0,230,315));
    scaledBartFace = new QPixmap(bartFace->scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    scaledHomerFace = new QPixmap(homerFace->scaled(50,50,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    bartFaceItem = new QGraphicsPixmapItem(*scaledBartFace);
    homerFaceItem = new QGraphicsPixmapItem(*scaledHomerFace);
    bartFaceItem->setPos(20, 40);
    homerFaceItem->setPos(800-70,40);
    sceneLevelOne->addItem(bartFaceItem);
    sceneLevelOne->addItem(homerFaceItem);


    bart = new Bart(70.33,88.75,":/imagesEmancipation/bartConAtaque.png",6);
    homeroEnemy = new Enemy(90,99,":/imagesEmancipation/SpriteHomeroCompleto.png",8);
    connect(bart, &Character::winOrLost, this, &MainWindow::winOrLostCondition);
    connect(homeroEnemy, &Character::winOrLost, this, &MainWindow::winOrLostCondition);

    sceneLevelOne->addItem(bart);
    sceneLevelOne->addItem(homeroEnemy);

    bartHealthBarProxy = sceneLevelOne->addWidget(bart->getBartHealthBar());
    bartHealthBarProxy->setPos(70, 65);

    homerHealthBarProxy = sceneLevelOne->addWidget(homeroEnemy->getHomerHealthBar());
    homerHealthBarProxy->setPos(800-280,65);

    bart->setFlag(QGraphicsItem::ItemIsFocusable);
    bart->setFocus();

    ui->graphicsViewLevelOne->setScene(sceneLevelOne);
    ui->graphicsViewLevelOne->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewLevelOne->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsViewLevelOne->show();
    ui->graphicsViewLevelOne->setFixedSize(800,600);
    ui->graphicsViewLevelOne->setGeometry(0,0,800,600);

    QPixmap backGroundPixmap(":/imagesEmancipation/simpsons house.jfif");
    QBrush backGroundBrush(backGroundPixmap.scaled(ui->graphicsViewLevelOne->size(), Qt::KeepAspectRatioByExpanding));
    ui->graphicsViewLevelOne->setBackgroundBrush(backGroundBrush);

    bart->setPos(10,500);
    homeroEnemy->setPos(700,480);

    musicLevelOne = new QMediaPlayer;
    musicLevelOne->setSource(QUrl("qrc:/sounds/soundsEmancipation/television-closing-theme.mp3"));
    audioOutputLevelOne = new QAudioOutput(this);

    musicLevelOne->setAudioOutput(audioOutputLevelOne);
    audioOutputLevelOne->setVolume(1.0);
    musicLevelOne->play();

    connect(musicLevelOne, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            musicLevelOne->setPosition(0);
            musicLevelOne->play();
        }
    });
}

void MainWindow::secondLevelScene(){

    this->setSecondLevelCreated(true);

    sceneLevelTwo = new QGraphicsScene(this);
    ui->graphicsViewLevelTwo->setScene(sceneLevelTwo);
    ui->graphicsViewLevelTwo->setFixedSize(800, 600);

    homero = new Homero(60,114,":/imagesEmancipation/HomeroSkate.png",6);
    connect(homero, &Character::winOrLost, this, &MainWindow::winOrLostCondition);

    QPixmap backGroundPixmap(":/imagesEmancipation/SkateParkBackGroundOne.png");

    backGroundWidth = backGroundPixmap.width();

    firstBackGround = sceneLevelTwo->addPixmap(backGroundPixmap);
    secondBackGround = sceneLevelTwo->addPixmap(backGroundPixmap);

    firstBackGround->setPos(0, 0);
    secondBackGround->setPos(backGroundWidth, 0);

    ui->graphicsViewLevelTwo->setFixedSize(backGroundWidth, backGroundPixmap.height());
    ui->graphicsViewLevelTwo->show();
    ui->graphicsViewLevelTwo->setGeometry(0,0,800,600);
    ui->graphicsViewLevelTwo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewLevelTwo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    scrollTimer = new QTimer(this);
    connect(scrollTimer, &QTimer::timeout, this, &MainWindow::scrollBackground);
    scrollTimer->start(30);

    homerHealthBarProxy = sceneLevelTwo->addWidget(homero->getHomerHealthBar());
    homerHealthBarProxy->setPos(70, 45);

    homero->setFlag(QGraphicsItem::ItemIsFocusable);

    sceneLevelTwo->addItem(homero);
    homero->setPos(10,300);

    bartAndHomerFace = new QPixmap(":/imagesEmancipation/Bart y homero FotosCara.png");
    coin = new QPixmap(":/imagesEmancipation/images-removebg-preview.png");
    scaledCoin = new QPixmap(coin->scaled(50,50,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QGraphicsPixmapItem* coinScore = new QGraphicsPixmapItem(*scaledCoin);
    coinScore->setPos(800-120,20);
    sceneLevelTwo->addItem(coinScore);


    homerFace = new QPixmap(bartAndHomerFace->copy(230,0,230,315));
    scaledHomerFace = new QPixmap(homerFace->scaled(50,50,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    homerFaceItem = new QGraphicsPixmapItem(*scaledHomerFace);
    homerFaceItem->setPos(20,20);
    sceneLevelTwo->addItem(homerFaceItem);

    spawnRandomObstacleTimer = new QTimer(this);
    connect(spawnRandomObstacleTimer, &QTimer::timeout, this, &MainWindow::spawnRandomObstacle);


    scoreItem = new QGraphicsTextItem("X"+ QString::number(homero->getScoreGame()));
    scoreItem->setDefaultTextColor(Qt::white);
    scoreItem->setFont(QFont("Arial", 20));
    scoreItem->setPos(800-70,35);
    sceneLevelTwo->addItem(scoreItem);

    connect(homero, &Homero::scoreChanged, this, &MainWindow::updateScore);

    spawnRandomObstacleTimer->start(2000);

    musicLevelTwo = new QMediaPlayer;
    musicLevelTwo->setSource(QUrl("qrc:/sounds/soundsEmancipation/homero_si_canta.mp3"));
    audioOutputLevelTwo = new QAudioOutput(this);

    musicLevelTwo->setAudioOutput(audioOutputLevelTwo);
    audioOutputLevelTwo->setVolume(0.4);
    musicLevelTwo->play();

    connect(musicLevelTwo, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            musicLevelTwo->setPosition(0);
            musicLevelTwo->play();
        }
    });

}

void MainWindow::clearSecondLevel(){

    if(secondLevelCreated){

        delete sceneLevelTwo;
        sceneLevelTwo = nullptr;
        delete scrollTimer;
        delete coin;
        delete scaledCoin;
        delete spawnRandomObstacleTimer;
        delete musicLevelTwo;
        delete audioOutputLevelTwo;

        delete bartAndHomerFace;
        delete homerFace;
        delete scaledHomerFace;
    }
}

void MainWindow::clearFirstScene(){

    if(firstLevelCreated){
        delete sceneLevelOne;
        sceneLevelOne = nullptr;
        delete bartFace;
        delete scaledBartFace;
        delete musicLevelOne;
        delete audioOutputLevelOne;

        delete bartAndHomerFace;
        delete homerFace;
        delete scaledHomerFace;
    }

}

void MainWindow::mainMenu(){
    ui->stackedWidget->setCurrentIndex(0);
    sceneMenu = new QGraphicsScene(this);
    sceneMenu->setSceneRect(0,0,800,600);

    ui->graphicsViewMenu->setScene(sceneMenu);
    ui->graphicsViewMenu->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewMenu->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsViewMenu->show();
    ui->graphicsViewMenu->setFixedSize(800,600);
    ui->graphicsViewMenu->setGeometry(0,0,800,600);

    QPixmap backGroundPixmap(":/imagesEmancipation/HomeroVsTony.png");
    QBrush backGroundBrush(backGroundPixmap.scaled(ui->graphicsViewMenu->size(), Qt::KeepAspectRatioByExpanding));
    ui->graphicsViewMenu->setBackgroundBrush(backGroundBrush);
}

void MainWindow::winScreen(unsigned short int level){
    QString imagePath;
    if(level == 1){
        imagePath = ":/imagesEmancipation/FirstLevelWin.png";
    }
    else if(level == 2){
        imagePath = ":/imagesEmancipation/SecondLevelWin.PNG";
    }
    ui->stackedWidget->setCurrentIndex(3);
    sceneWin = new QGraphicsScene(this);
    sceneWin->setSceneRect(0,0,800,600);

    ui->graphicsViewWin->setScene(sceneWin);
    ui->graphicsViewWin->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewWin->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsViewWin->show();
    ui->graphicsViewWin->setFixedSize(800,600);
    ui->graphicsViewWin->setGeometry(0,0,800,600);

    QPixmap backGroundPixmap(imagePath);
    QBrush backGroundBrush(backGroundPixmap.scaled(ui->graphicsViewWin->size(), Qt::KeepAspectRatioByExpanding));
    ui->graphicsViewWin->setBackgroundBrush(backGroundBrush);

}

void MainWindow::LostScreen(unsigned short int level){
    QString imagePath;
    if(level == 1){
        imagePath = ":/imagesEmancipation/firstLevelLose.PNG";
    }
    else if(level == 2){
        imagePath = ":/imagesEmancipation/secondLevelLost.PNG";
    }
    ui->stackedWidget->setCurrentIndex(4);
    sceneLose = new QGraphicsScene(this);
    sceneLose->setSceneRect(0,0,800,600);

    ui->graphicsViewLose->setScene(sceneLose);
    ui->graphicsViewLose->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewLose->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsViewLose->show();
    ui->graphicsViewLose->setFixedSize(800,600);
    ui->graphicsViewLose->setGeometry(0,0,800,600);

    QPixmap backGroundPixmap(imagePath);
    QBrush backGroundBrush(backGroundPixmap.scaled(ui->graphicsViewLose->size(), Qt::KeepAspectRatioByExpanding));
    ui->graphicsViewLose->setBackgroundBrush(backGroundBrush);

}


void MainWindow::winOrLostCondition(bool win, unsigned short int sceneNumber){

    if(sceneNumber == 1){
        clearFirstScene();
    }
    else if(sceneNumber == 2){
        clearSecondLevel();
    }

    if(win && sceneNumber == 1){
        bart->achievement(QString::number(bart->getHealth()));
        winScreen(1);
    }
    else if(win && sceneNumber == 2){
        winScreen(2);
    }
    else if(!win && sceneNumber == 1){
        LostScreen(1);
    }
    else if(!win && sceneNumber == 2){
        LostScreen(2);
    }
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

void MainWindow::updateScore(unsigned short int newScore){
    scoreItem->setPlainText("X" + QString::number(newScore));
}

void MainWindow::spawnRandomObstacle(){

    unsigned short int randomNumber = QRandomGenerator::global()->bounded(4);
    unsigned short int randomYPosition = QRandomGenerator::global()->bounded(100,500);
    unsigned short int randomYPositionCoin = QRandomGenerator::global()->bounded(75,500);
    Obstacle* obstacle = new Obstacle(":/imagesEmancipation/duff-removebg-preview.png",50,100,"duff",2);
    Obstacle* obstacle2 = new Obstacle(":/imagesEmancipation/images-removebg-preview.png",40,40,"coin",2);
    Obstacle* obstacle3 = new Obstacle(":/imagesEmancipation/Rocket.png",100,50,"rocket",2);
    Obstacle* obstacle4 = new Obstacle(":/imagesEmancipation/skateRail.png",280,180,"skateRail",2);
    Obstacle* obstacle5 = new Obstacle(":/imagesEmancipation/skate-removebg-preview.png",120,60,"skate",2);

    switch (randomNumber) {
    case 0:

        qDebug()<<"duff created";
        ui->graphicsViewLevelTwo->scene()->addItem(obstacle);
        obstacle->setRotate(true);
        obstacle->setPos(750,randomYPosition);
        obstacle->circularTimer->start(50);
        break;
    case 1:

        qDebug()<<"skate created";
        ui->graphicsViewLevelTwo->scene()->addItem(obstacle5);
        obstacle5->setPos(640,randomYPosition);
        obstacle5->oscillatoryTimer->start(50);

        break;
    case 2:

        qDebug()<<"Rocket created";

        ui->graphicsViewLevelTwo->scene()->addItem(obstacle3);
        obstacle3->setPos(700,randomYPosition);
        obstacle3->timer->start(50);
        obstacle3->setVelocity(40);
        obstacle3->setDirection(-1);
        break;
    case 3:

        qDebug()<<"railSkate created";
        ui->graphicsViewLevelTwo->scene()->addItem(obstacle4);
        obstacle4->setPos(520,480);
        obstacle4->timer->start(50);
        obstacle4->setDirection(-1);
        break;
    default:
        break;
    }
    ui->graphicsViewLevelTwo->scene()->addItem(obstacle2);
    obstacle2->setPos(750,randomYPositionCoin);
    obstacle2->timer->start(50);
    obstacle2->setDirection(-1);
}


void MainWindow::on_levelOneButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    firstLevelScene();
}

void MainWindow::on_levelTwoButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    secondLevelScene();
}

void MainWindow::on_exitButton_clicked()
{
    close();
}


void MainWindow::on_backToMenuButton_clicked()
{
    mainMenu();
}


void MainWindow::on_backToMenuButton_2_clicked()
{
    mainMenu();
}

void MainWindow::exit(){
    close();
}


