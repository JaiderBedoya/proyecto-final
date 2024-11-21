#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Enemy.h"
#include "Protagonist.h"
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
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
