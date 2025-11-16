#include "leon.h"
#include "QDebug"


Leon::Leon(int cx, int cy)
{
    x = cx;
    y = cy;
    health_ability = 2;
    leon_position = new Point(x, y, unlock);
}

Leon::~Leon()
{
    delete leon_position;
}


int Leon::get_leon_x() const
{
    return x;
}

int Leon::get_leon_y() const
{
    return y;
}

int Leon::get_health_ability() const
{
    return health_ability;
}

void Leon::set_point_x(int x)
{
    this->x = x;
}

void Leon::set_point_y(int y)
{
    this->y = y;
}

