#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(qreal characterWidth, qreal characterHeight, const QString &spritePath): Character(characterWidth, characterHeight, spritePath){
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void Enemy::setAttacking(bool _attacking)
{
    attacking = _attacking;
}

bool Enemy::getAttacking()
{
    return attacking;
}
