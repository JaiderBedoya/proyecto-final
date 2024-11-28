#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Enemy.h"
#include "Bart.h"
#include "Homero.h"
#include "Obstacle.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QBrush>
#include <QImage>
#include <QColor>
#include <QFont>
#include <QMediaPlayer>
#include <QUrl>
#include <QAudioOutput>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setBackGroundWidth(unsigned short _backGroundWidth);
    void setScrollSpeed(unsigned short _scrollSpeed);
    void setFirstLevelCreated(bool _firstLevelCreated);
    void setSecondLevelCreated(bool _secondLevelCreated);

    unsigned short getBackGroundWidth();
    unsigned short getScrollSpeed();
    bool getFirstLevelCreated();
    bool getSecondLevelCreated();


    void spawnRandomObstacle();
    void updateScore(int newScore);
    void winOrLostCondition(bool win, unsigned short int sceneNumber);
    void initialMenu();
    void firstLevelScene();
    void secondLevelScene();
    void exit();
    void mainMenu();
    void clearSecondLevel();
    void clearFirstScene();
    void winScreen(unsigned short level);
    void LostScreen(unsigned short level);
private:
    Ui::MainWindow *ui;

    QGraphicsPixmapItem *firstBackGround;
    QGraphicsPixmapItem *secondBackGround;
    unsigned short int backGroundWidth;
    unsigned short int scrollSpeed;

    QGraphicsScene* sceneMenu;
    QGraphicsScene* sceneLevelOne;
    QGraphicsScene* sceneLevelTwo;
    QGraphicsScene* sceneWin;
    QGraphicsScene* sceneLose;

    QGraphicsTextItem* scoreItem;

    bool firstLevelCreated, secondLevelCreated;


    //Necessary items for first level

    QPixmap* bartFace;
    QPixmap* scaledBartFace;
    QGraphicsPixmapItem* bartFaceItem;
    Bart *bart;
    Enemy *homeroEnemy;
    QGraphicsProxyWidget* bartHealthBarProxy;
    QMediaPlayer* musicLevelOne;
    QAudioOutput* audioOutputLevelOne;


    //Necessary items for second level


    Homero *homero;
    QTimer *scrollTimer;
    QPixmap* coin;
    QPixmap* scaledCoin;
    QGraphicsPixmapItem* coinScore;
    QTimer* spawnRandomObstacleTimer = new QTimer();
    QMediaPlayer* musicLevelTwo;
    QAudioOutput* audioOutputLevelTwo;


    //Necessary items for both levels


     QGraphicsProxyWidget* homerHealthBarProxy;
     QPixmap* bartAndHomerFace;
     QPixmap* homerFace;
     QPixmap* scaledHomerFace;
     QGraphicsPixmapItem* homerFaceItem;


private slots:
    void scrollBackground();
    void on_levelOneButton_clicked();
    void on_levelTwoButton_clicked();
    void on_exitButton_clicked();
    void on_backToMenuButton_clicked();
    void on_backToMenuButton_2_clicked();
};
#endif // MAINWINDOW_H
