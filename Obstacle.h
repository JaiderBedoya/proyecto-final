#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>

class Obstacle: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    short int direction;

public:
    Obstacle();
    void setDirection(short int _direction);
public slots:
    void move();

};

#endif // OBSTACLE_H
