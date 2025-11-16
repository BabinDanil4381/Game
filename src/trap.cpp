#include "trap.h"


Trap::Trap() {
    damage = 6;
    price = 35;
}

bool Trap::use_card(Visitor& visitor, int x, int y)
{
    return visitor.visitMap(x, y);
}

int Trap::get_price() const
{
    return this->price;
}

void Trap::upgrade(int level)
{
    damage += level;
}

int Trap::get_damage() const
{
    return damage;
}
