#include "teammate.h"
#include <QDebug>

Teammate::Teammate() {
    price = 80;
    x = 10000;
    y = 10000;
    count = 1;
}

bool Teammate::use_card(Visitor& visitor, int x, int y)
{
    qDebug() << "COUNT" << count;
    return visitor.visitGame(x, y, count);
}

int Teammate::get_price() const
{
    return this->price;
}

void Teammate::upgrade(int level)
{
    count += level/2 + 1;
    qDebug() << "UPGRADE" << " count" << count;
}
