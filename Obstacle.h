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
    qreal velocity,angle,sizeObstacle, amplitude, frequency;
public:
    Obstacle(const QString& obstacleImage, qreal size, qreal sizeHeight);

    qreal getTimeLapsed();
    qreal getVelocity();
    qreal getSizeObstacle();
    qreal getAmplitude();

    QTimer *timerMovPar;
    QTimer* timer;
    QTimer* oscillatoryTimer;
    QTimer* randomSpawnTimer;

    void setSizeObstacle(qreal _sizeObstacle);
    void setDirection(short int _direction);
    void setTimeLapsed(qreal _timeLapsed);
    void setVelocity(qreal _velocity);
    void setAmplitude(qreal newAmplitude);

    void checkCollision();

    void setFrequency(qreal newFrequency);

    qreal getFrequency();

public slots:
    void move();
    void parabolicMove();
    void oscillatoryMove();
};

#endif // OBSTACLE_H
