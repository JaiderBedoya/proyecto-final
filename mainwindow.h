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

private:
    Ui::MainWindow *ui;

    QGraphicsPixmapItem *firstBackGround;
    QGraphicsPixmapItem *secondBackGround;
    unsigned short int backGroundWidth;
    unsigned short int scrollSpeed;

private slots:
    void scrollBackground();

};
#endif // MAINWINDOW_H
