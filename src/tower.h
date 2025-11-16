#ifndef TOWER_H
#define TOWER_H
#include "point.h"
#include <vector>

class Tower
{
public:
    Tower(int x, int y);
    ~Tower();

    Point*** get_tower_position() const;
    int get_left_x() const;
    int get_down_y() const;
    int get_health() const;
    bool get_alive() const;

    void set_alive(bool f);
    void sub_health(int damage);
    std::vector<int> attack() const;

private:
    int height;
    int width;
    int left_x;
    int down_y;
    int health;
    bool alive;
    Point*** tower_position;
};

#endif // TOWER_H
