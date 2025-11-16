#include "poison.h"


Poison::Poison() {
    damage = 6;
    price = 30;
    radius = 6;
}

bool Poison::use_card(Visitor& visitor, int x, int y)
{
    return visitor.visitEnemy(x, y, damage, radius, 0);

}

int Poison::get_damage() const
{
    return this-> damage;
}

int Poison::get_price() const
{
    return this->price;
}

void Poison::upgrade(int level)
{
    this->radius += level/2 + 1;
}
