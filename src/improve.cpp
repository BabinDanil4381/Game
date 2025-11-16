#include "improve.h"


Improve::Improve() {
    price = 60;
    level = 1;
}

bool Improve::use_card(Visitor& visitor, int x, int y)
{
    return visitor.visitMapForImprove(x, y);
}

int Improve::get_price() const
{
    return price;
}

void Improve::upgrade(int new_level)
{
    this->level = new_level + 1;
}

int Improve::get_level()
{
    return level;
}
