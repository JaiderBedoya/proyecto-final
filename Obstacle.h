#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QtMath>


class Obstacle: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    short int direction = 1;
    qreal timeLapsed = 0;
    qreal velocity;
    qreal angle;
public:
    Obstacle(const QString& obstacleImage, qreal size);
    void setDirection(short int _direction);
    void setTimeLapsed(qreal _timeLapsed);
    void setVelocity(qreal _velocity);
    qreal getTimeLapsed();
    qreal getVelocity();
    QTimer *timerMovPar;
    QTimer* timer;

public slots:
    void move();
    void parabolicMove();
};

#endif // OBSTACLE_H
