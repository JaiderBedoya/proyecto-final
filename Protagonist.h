#ifndef PROTAGONIST_H
#define PROTAGONIST_H
#include <Character.h>

class Protagonist: public Character
{
private:

public:
    Protagonist();
    Protagonist(qreal characterWidth, qreal characterHeight, const QString &spritePath, unsigned short int numberOfHorizontalSprites);
    void keyPressEvent(QKeyEvent* event);
};

#endif // PROTAGONIST_H
