#ifndef PROTAGONIST_H
#define PROTAGONIST_H
#include <Character.h>

class Protagonist: public Character
{
private:

public:
    Protagonist();
    Protagonist(qreal characterWidth, qreal characterHeight, const QString &spritePath);
    void keyPressEvent(QKeyEvent* event);
};

#endif // PROTAGONIST_H
