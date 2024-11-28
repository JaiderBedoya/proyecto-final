#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Enemy.h"
#include "Bart.h"
#include "Homero.h"
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
    qreal velocity,angle,sizeObstacle,sizeHeight, amplitude, frequency;
    QString identificator;
    bool rotate;
    unsigned short int obstacleLevel;
public:
    Obstacle();
    Obstacle(const QString& obstacleImage, qreal size, qreal sizeHeight, QString _identificator, unsigned short int _obstacleLevel);

    qreal getTimeLapsed();
    qreal getVelocity();
    qreal getSizeObstacle();
    qreal getSizeHeight();
    qreal getAmplitude();
    qreal getFrequency();
    QString getIdentificator();
    bool getRotate();

    QTimer *timerMovPar;
    QTimer* timer;
    QTimer* oscillatoryTimer;
    QTimer* circularTimer;
    QTimer* randomSpawnTimer;

    void setSizeObstacle(qreal _sizeObstacle);
    void setDirection(short int _direction);
    void setTimeLapsed(qreal _timeLapsed);
    void setVelocity(qreal _velocity);
    void setAmplitude(qreal newAmplitude);
    void setRotate(bool newRotate);
    void setFrequency(qreal newFrequency);
    void setAngle(qreal newAngle);

    void checkCollision();
    void setSizeHeight(qreal newSizeHeight);

    void setObstacleLevel(unsigned short _obstacleLevel);
    unsigned short int getObstacleLevel();

public slots:
    void move();
    void parabolicMove();
    void oscillatoryMove();
    void circularMovement();
};

#endif // OBSTACLE_H
