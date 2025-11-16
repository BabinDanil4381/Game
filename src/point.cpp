#include "point.h"

Point::Point(int x, int y, State opt) {
    this->x = x;
    this->y = y;
    this->option = opt;
}

int Point::get_point_x() const{
    return this->x;
}

int Point::get_point_y() const{
    return this->y;
}

 State Point::get_point_opt() const{
    return this->option;
}

void Point::set_option(State opt)
{
    this->option = opt;
}

void Point::set_point_x(int dx)
{
    this->x += dx;
}

void Point::set_point_y(int dy)
{
    this->y += dy;
}


