#include <QTimer>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <array>
#include "enemy.h"



Enemy::Enemy(int x, int y)  {
    health = 100;
    damage = 5;
    enemy_position = nullptr;
    f = 0;
    aliveEnemy = true;
    count_for_slow = 0;
    spawn_enemy(x, y);
}

Enemy::~Enemy(){
    delete enemy_position;
}

void Enemy::subtract_health(int value)
{
    this->health -= value;
    if(health < 0){
        this->health = 0;
    }
}

void Enemy::set_alive(bool v)
{
    this->aliveEnemy = v;
}

int Enemy::get_health() const
{
    return this->health;
}

void Enemy::spawn_enemy(int x, int y){
    this->enemy_position = new Point(x, y, unlock);
}

int Enemy::get_coord_x() const
{
    return this->enemy_position->get_point_x();
}

int Enemy::get_coord_y() const
{
    return this->enemy_position->get_point_y();
}

bool Enemy::get_alive() const
{
    return aliveEnemy;
}

int Enemy::get_count_for_slow()
{
    return count_for_slow;
}

void Enemy::recovery_health()
{
    this->health = 100;
}

// void Enemy::random_journey(Player& user, Map& myMap)
// {
//     const int H = FIELD_HEIGHT;
//     const int W = FIELD_WIDTH;

//     std::array<std::pair<int, int>, 4> dirs {{ {1,0}, {-1, 0}, {0, 1}, {0, -1}}};
//     std::random_shuffle(dirs.begin(), dirs.end());

//     if(std::rand() % 100 < 15) return;

//     for (auto [dx, dy] : dirs){
//         int nx = this->enemy_position->get_point_x() + dx;
//         int ny = this->enemy_position->get_point_y() + dy;

//         if(nx < 0 || nx >= H || ny < 0 || ny >= W ) continue;
//         if(myMap.get_point(nx, ny).get_point_opt() == lock || myMap.get_point(nx, ny).get_point_opt() == tower) continue;
//         if(myMap.get_point(nx, ny).get_point_opt() == slow  && f!= 3) continue;
//         if(myMap.get_point(nx, ny).get_point_opt() == trap)
//         {
//             this->subtract_health(user.get_hand().get_trap_card().get_damage());
//             myMap.set_point(nx, ny).set_option(unlock);
//         }

//         this->enemy_position->set_point_x(dx);
//         this->enemy_position->set_point_y(dy);

//         return;
//     }
// }


std::vector<int> Enemy::random_journey(/*int height, int width*/)
{
    // const int H = height;
    // const int W = width;
    std::vector<int> result_info = {0, 0, 0};

    std::array<std::pair<int, int>, 4> dirs {{ {1,0}, {-1, 0}, {0, 1}, {0, -1}}};
    std::random_shuffle(dirs.begin(), dirs.end());

    if(std::rand() % 100 < 15) return result_info;

    for (auto [dx, dy] : dirs){
        // int nx = this->enemy_position->get_point_x() + dx;
        // int ny = this->enemy_position->get_point_y() + dy;

        // if(nx < 0 || nx >= H || ny < 0 || ny >= W ) continue;
        // if(myMap.get_point(nx, ny).get_point_opt() == lock || myMap.get_point(nx, ny).get_point_opt() == tower) continue;
        // if(myMap.get_point(nx, ny).get_point_opt() == slow  && f!= 3) continue;
        // if(myMap.get_point(nx, ny).get_point_opt() == trap)
        // {
        //     this->subtract_health(user.get_hand().get_trap_card().get_damage());
        //     myMap.set_point(nx, ny).set_option(unlock);
        // }

        // this->enemy_position->set_point_x(dx);
        // this->enemy_position->set_point_y(dy);
        result_info[0] = dx;
        result_info[1] = dy;
        result_info[2] = count_for_slow;
        return result_info;
    }
    return result_info;
}

// void Enemy::enemy_atack(Player& us)
// {
//     int x = enemy_position->get_point_x();
//     int y = enemy_position->get_point_y();

//     int u_x = us.get_x();
//     int u_y = us.get_y();

//     if(abs(u_x - x) <= 1 && abs(u_y - y) <= 1){
//         us.change_health(us.get_health() - damage);
//     }

// }


std::vector<int> Enemy::enemy_atack(/*Player& us*/)
{
    int x = enemy_position->get_point_x();
    int y = enemy_position->get_point_y();

    // int u_x = us.get_x();
    // int u_y = us.get_y();

    // if(abs(u_x - x) <= 1 && abs(u_y - y) <= 1){
    //     us.change_health(us.get_health() - damage);
    // }
    std::vector<int> info_attack;
    info_attack.push_back(x);
    info_attack.push_back(y);
    info_attack.push_back(damage);
    // info_attack.push_back(1);
    return info_attack;
}

void Enemy::set_position(int dx, int dy){
    this->enemy_position->set_point_x(dx);
    this->enemy_position->set_point_y(dy);
}

void Enemy::set_count_for_slow(int val)
{
    this->count_for_slow += val;
}
