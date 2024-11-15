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
    unsigned short int timeLapsed = 0;
    qreal velocity;
    qreal angle;
public:
    Obstacle();
    void setDirection(short int _direction);
    void setTimeLapsed(unsigned short int _timeLapsed);
    void setVelocity(qreal _velocity);
    unsigned short int getTimeLapsed();
    qreal getVelocity();

public slots:
    void move();
    void parabolicMove();
};

#endif // OBSTACLE_H
