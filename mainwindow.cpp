#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), firstBackGround(nullptr) , secondBackGround(nullptr), backGroundWidth(0), scrollSpeed(5)
{
    ui->setupUi(this);
    this->statusBar()->hide();
    this->setGeometry(80,80,800,600);
    mainMenu();
}
/*
void MainWindow::initialMenu(){

    sceneMenu = new QGraphicsScene(this);
    sceneMenu->setSceneRect(0,0,800,600);

    // Crear contenedor para los botones
    QVBoxLayout *layout = new QVBoxLayout;

    // Crear botones
    QPushButton *buttonLevelOne = new QPushButton("Nivel 1");
    QPushButton *buttonLevelTwo = new QPushButton("Nivel 2");
    QPushButton *buttonExit = new QPushButton("Salir");


    // Agregar botones al layout
    layout->addWidget(buttonLevelOne);
    layout->addWidget(buttonLevelTwo);
    layout->addWidget(buttonExit);
    ui->graphicsView->setLayout(layout);

    // Añadir el widget del menú a la escena
    proxy = sceneMenu->addWidget(ui->graphicsView);
    proxy->setPos(200, 100);

    ui->graphicsView->setScene(sceneMenu);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->show();
    ui->graphicsView->setFixedSize(800,600);
    ui->graphicsView->setGeometry(0,0,800,600);


    // Conectar botones con sus funcionalidades
    connect(buttonLevelOne, &QPushButton::clicked, this, &MainWindow::firstLevelScene);
    connect(buttonLevelTwo, &QPushButton::clicked, this, &MainWindow::secondLevelScene);
    connect(buttonExit, &QPushButton::clicked, this, &MainWindow::exit);

}*/

void MainWindow::exit(){
    close();
}

void MainWindow::mainMenu(){
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



    QMediaPlayer* music = new QMediaPlayer;
    music->setSource(QUrl("qrc:/sounds/soundsEmancipation/television-simpsons.mp3"));
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

void MainWindow::firstLevelScene(){
    //Create a scene
    sceneLevelOne = new QGraphicsScene(this);
    sceneLevelOne->setSceneRect(0,0,800,600);

    QPixmap* bartAndHomerFace = new QPixmap(":/imagesEmancipation/Bart y homero FotosCara.png");

    QPixmap* bartFace = new QPixmap(bartAndHomerFace->copy(0, 0, 230, 315));
    QPixmap* homerFace = new QPixmap(bartAndHomerFace->copy(230,0,230,315));
    QPixmap* scaledBartFace = new QPixmap(bartFace->scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QPixmap* scaledHomerFace = new QPixmap(homerFace->scaled(50,50,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QGraphicsPixmapItem* bartFaceItem = new QGraphicsPixmapItem(*scaledBartFace);
    QGraphicsPixmapItem* homerFaceItem = new QGraphicsPixmapItem(*scaledHomerFace);
    bartFaceItem->setPos(20, 40);
    homerFaceItem->setPos(800-70,40);
    sceneLevelOne->addItem(bartFaceItem);
    sceneLevelOne->addItem(homerFaceItem);


    //Create an enemy and the protagonist
    Bart *player = new Bart(70.33,88.75,":/imagesEmancipation/bartConAtaque.png",6);
    Enemy *enemy = new Enemy(90,99,":/imagesEmancipation/SpriteHomeroCompleto.png",8);

    //adding items to our scene
    sceneLevelOne->addItem(player);
    sceneLevelOne->addItem(enemy);

    QGraphicsProxyWidget* bartHealthBarProxy = sceneLevelOne->addWidget(player->getBartHealthBar());
    bartHealthBarProxy->setPos(70, 65);

    QGraphicsProxyWidget* homerHealthBarProxy = sceneLevelOne->addWidget(enemy->getHomerHealthBar());
    homerHealthBarProxy->setPos(800-280,65);


    //make player focusable for the key press events
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    ui->graphicsViewLevelOne->setScene(sceneLevelOne);
    ui->graphicsViewLevelOne->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewLevelOne->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsViewLevelOne->show();
    ui->graphicsViewLevelOne->setFixedSize(800,600);
    ui->graphicsViewLevelOne->setGeometry(0,0,800,600);
    //ui->graphicsView->resize(800,600);
    //ui->graphicsView->updateGeometry();
    //ui->graphicsView->setFixedSize(800,600);

    QPixmap backGroundPixmap(":/imagesEmancipation/simpsons house.jfif");
    QBrush backGroundBrush(backGroundPixmap.scaled(ui->graphicsViewLevelOne->size(), Qt::KeepAspectRatioByExpanding));
    ui->graphicsViewLevelOne->setBackgroundBrush(backGroundBrush);

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


    sceneLevelTwo = new QGraphicsScene(this);
    ui->graphicsViewLevelTwo->setScene(sceneLevelTwo);
    ui->graphicsViewLevelTwo->setFixedSize(800, 600);

    Homero *homero = new Homero(60,114,":/imagesEmancipation/HomeroSkate.png",6);

    //QGraphicsProxyWidget* homerHealthBarProxy = scene->addWidget(homero->getHomerHealthBar());
    //homerHealthBarProxy->setPos(70, 65);


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



    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::scrollBackground);
    timer->start(30);

    QGraphicsProxyWidget* homerHealthBarProxy = sceneLevelTwo->addWidget(homero->getHomerHealthBar());
    homerHealthBarProxy->setPos(70, 45);

    homero->setFlag(QGraphicsItem::ItemIsFocusable);

    sceneLevelTwo->addItem(homero);
    homero->setPos(10,300);

    QPixmap* bartAndHomerFace = new QPixmap(":/imagesEmancipation/Bart y homero FotosCara.png");
    QPixmap* coin = new QPixmap(":/imagesEmancipation/images-removebg-preview.png");
    QPixmap* scaledCoin = new QPixmap(coin->scaled(50,50,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QGraphicsPixmapItem* coinScore = new QGraphicsPixmapItem(*scaledCoin);
    coinScore->setPos(800-120,20);
    sceneLevelTwo->addItem(coinScore);


    QPixmap* homerFace = new QPixmap(bartAndHomerFace->copy(230,0,230,315));
    QPixmap* scaledHomerFace = new QPixmap(homerFace->scaled(50,50,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QGraphicsPixmapItem* homerFaceItem = new QGraphicsPixmapItem(*scaledHomerFace);
    homerFaceItem->setPos(20,20);
    sceneLevelTwo->addItem(homerFaceItem);

    QTimer* spawnRandomObstacleTimer = new QTimer();
    connect(spawnRandomObstacleTimer, &QTimer::timeout, this, &MainWindow::spawnRandomObstacle);


    scoreItem = new QGraphicsTextItem("X"+ QString::number(homero->getScoreGame()));
    scoreItem->setDefaultTextColor(Qt::white);
    scoreItem->setFont(QFont("Arial", 20));
    scoreItem->setPos(800-70,35);
    sceneLevelTwo->addItem(scoreItem);

    connect(homero, &Homero::scoreChanged, this, &MainWindow::updateScore);


    spawnRandomObstacleTimer->start(2000);

    QMediaPlayer* music = new QMediaPlayer;
    music->setSource(QUrl("qrc:/sounds/soundsEmancipation/homero_si_canta.mp3"));
    QAudioOutput* audioOutput = new QAudioOutput(this);

    music->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.4);
    music->play();

    connect(music, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            music->setPosition(0);
            music->play();
        }
    });

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

    unsigned short int randomNumber = QRandomGenerator::global()->bounded(4);
    unsigned short int randomYPosition = QRandomGenerator::global()->bounded(100,500);
    unsigned short int randomYPositionCoin = QRandomGenerator::global()->bounded(75,500);
    Obstacle* obstacle = new Obstacle(":/imagesEmancipation/duff-removebg-preview.png",50,100,"duff");
    Obstacle* obstacle2 = new Obstacle(":/imagesEmancipation/images-removebg-preview.png",40,40,"coin");
    Obstacle* obstacle3 = new Obstacle(":/imagesEmancipation/Rocket.png",100,50,"rocket");
    Obstacle* obstacle4 = new Obstacle(":/imagesEmancipation/skateRail.png",280,180,"skateRail");
    Obstacle* obstacle5 = new Obstacle(":/imagesEmancipation/skate-removebg-preview.png",120,60,"skate");

    switch (randomNumber) {
    case 0:

        qDebug()<<"duff created";
        ui->graphicsViewLevelTwo->scene()->addItem(obstacle);
        obstacle->setPos(750,randomYPosition);
        obstacle->oscillatoryTimer->start(50);
        /*
        ui->graphicsView->scene()->addItem(obstacle2);
        obstacle2->setPos(750,randomYPosition);
        obstacle2->timer->start(50);
        obstacle2->setDirection(-1);
        */
        break;
    case 1:

        qDebug()<<"skate created";
        ui->graphicsViewLevelTwo->scene()->addItem(obstacle5);
        obstacle5->setRotate(true);
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
        /*
        ui->graphicsView->scene()->addItem(obstacle2);
        obstacle2->setPos(750,randomYPosition);
        obstacle2->timer->start(50);
        obstacle2->setDirection(-1);
        */
        break;
    case 3:

        qDebug()<<"railSkate created";
        ui->graphicsViewLevelTwo->scene()->addItem(obstacle4);
        obstacle4->setPos(520,480);
        obstacle4->timer->start(50);
        obstacle4->setDirection(-1);
        /*
        ui->graphicsView->scene()->addItem(obstacle2);
        obstacle2->setPos(750,randomYPosition);
        obstacle2->timer->start(50);
        obstacle2->setDirection(-1);
        */
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

