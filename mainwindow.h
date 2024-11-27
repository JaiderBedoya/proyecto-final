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

    void initialMenu();
    void firstLevelScene();
    void secondLevelScene();

    void setBackGroundWidth(unsigned short _backGroundWidth);
    void setScrollSpeed(unsigned short _scrollSpeed);

    unsigned short getBackGroundWidth();
    unsigned short getScrollSpeed();

    void spawnRandomObstacle();

    QTimer* spawnRandomObstacleTimer;

    QGraphicsTextItem* scoreItem;
    void updateScore(int newScore);

    void exit();
    void mainMenu();
private:
    Ui::MainWindow *ui;

    QGraphicsPixmapItem *firstBackGround;
    QGraphicsPixmapItem *secondBackGround;
    unsigned short int backGroundWidth;
    unsigned short int scrollSpeed;

    QGraphicsScene* sceneMenu;
    QGraphicsScene* sceneLevelOne;
    QGraphicsScene* sceneLevelTwo;
    QGraphicsProxyWidget *proxy;

private slots:
    void scrollBackground();
    void on_levelOneButton_clicked();
    void on_levelTwoButton_clicked();
    void on_exitButton_clicked();
};
#endif // MAINWINDOW_H
