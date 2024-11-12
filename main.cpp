#include "mainwindow.h"
#include "Character.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QBrush>
#include <QImage>
#include <QColor>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Create a scene
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(0,0,800,600);


    //Create a item in this case is a rectangle
    Character *player = new Character(70.33,88.75);

    //changing the width and height of the rectangle
    //player->setRect(0,0,player->characterWidth,player->characterHeight);

    //obstacle1->setRect(400,300,obstacle1->characterWidth,obstacle1->characterHeight);
    //obstacle2->setRect(500,300,obstacle2->characterWidth,obstacle2->characterHeight);
    //adding a item to our scene
    scene->addItem(player);

    //make rectangle focusable

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //adding a view
    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->setScene(scene); this works too but in the constructor is easily to implement


    //showing the view that contains the scene
    view->show();
    view->setFixedSize(800,600);

    QPixmap bgPixmap(":/imagesEmancipation/simpsons house.jfif");
    QBrush bgBrush(bgPixmap.scaled(view->size(), Qt::KeepAspectRatioByExpanding));
    view->setBackgroundBrush(bgBrush);

    player->setPos(10,500);

    //spawn random enemies


    //MainWindow w;
    //w.show();

    return a.exec();
}
