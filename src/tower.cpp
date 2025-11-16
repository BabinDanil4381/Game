#include "tower.h"



Tower::Tower(int x, int y) {
    height = 3;
    width = 3;
    left_x = x;
    down_y = y;
    health = 500;
    alive = true;
    tower_position = new Point**[height];

    for(int i = 0; i < height; i++){
        int current_x = i + left_x;
        tower_position[i] = new Point*[width];
        for(int j = 0; j < width; j++){
            int current_y = down_y + j;
            tower_position[i][j] = new Point(current_x, current_y, lock);
        }
    }
}

Tower::~Tower()
{
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            delete tower_position[i][j];
        }
        delete[] tower_position[i];
    }
    delete[] tower_position;
}


Point*** Tower::get_tower_position() const
{
    return tower_position;
}

int Tower::get_left_x() const
{
    return left_x;
}

int Tower::get_down_y() const
{
    return down_y;
}

int Tower::get_health() const
{
    return health;
}

bool Tower::get_alive() const
{
    return alive;
}

void Tower::set_alive(bool f)
{
    this->alive = f;
}

void Tower::sub_health(int damage)
{
    this->health -= damage;

    if(this->health <= 0){
        this->health = 0;
        this->alive = false;
        return;
    }
}

std::vector<int> Tower::attack() const
{
    std::vector<int> info_attack;
    info_attack.push_back(left_x);
    info_attack.push_back(down_y);
    return info_attack;
}
