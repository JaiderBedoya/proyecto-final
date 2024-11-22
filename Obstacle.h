#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Enemy.h"
#include "Bart.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QtMath>
#include <QList>
#include <QMediaPlayer>
#include <QAudioOutput>

class Obstacle: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    short int direction = 1;
    qreal timeLapsed = 0;
    qreal velocity;
    qreal angle;
    qreal sizeObstacle;
public:
    Obstacle(const QString& obstacleImage, qreal size);


    void setDirection(short int _direction);
    void setTimeLapsed(qreal _timeLapsed);
    void setVelocity(qreal _velocity);

    qreal getTimeLapsed();
    qreal getVelocity();
    qreal getSizeObstacle();
    QTimer *timerMovPar;
    QTimer* timer;

    void setSizeObstacle(qreal _sizeObstacle);
    void checkCollision();
public slots:
    void move();
    void parabolicMove();
};

#endif // OBSTACLE_H
