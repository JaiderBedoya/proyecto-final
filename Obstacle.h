#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>

class Obstacle: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Obstacle();
public slots:
    void move();

};

#endif // OBSTACLE_H
