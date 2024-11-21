#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    firstLevelScene();
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
    Protagonist *player = new Protagonist(70.33,88.75,":/imagesEmancipation/bartConAtaque.png",6);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}



