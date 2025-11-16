#include "lightning.h"

Lightning::Lightning() {
    damage = 11;
    price = 30;
    width_damage = 2;
}

bool Lightning::use_card(Visitor& visitor, int x, int y)
{
    return visitor.visitEnemy(x, y, damage, 100, width_damage);
}

int Lightning::get_price() const
{
    return this->price;
}

void Lightning::upgrade(int level)
{
    this->width_damage = level + 1;
}
