#include "player.h"
#include <stdlib.h>
#include <ctime>

#include <QDebug>

Player::Player(int x, int y, int size) {
    health = 100;
    damage = 5;
    score = 0;
    type = close_combat;
    player_position = nullptr;
    count_for_slow = 0;
    zoneX = 100;
    zoneY = 100;
    money = 100;
    spawn_player(x, y);
    myHand = new handPlayer(size);
}
Player::~Player()
{
    delete player_position;
    delete myHand;
}

Point* Player::get_position() const
{
    return player_position;
}

int Player::get_x() const
{
    return this->player_position->get_point_x();
}

int Player::get_y() const
{
    return this->player_position->get_point_y();
}

Point& Player::set_position()
{
    return *player_position;
}

void Player::set_score(int s)
{
    this->score = score + s;
}

void Player::set_damage(int value)
{
    this->damage = value;
}

void Player::set_zoneX(int v)
{
    this->zoneX = v;
}

void Player::set_zoneY(int v)
{
    this->zoneY = v;
}

void Player::set_count_for_slow(int val)
{
    this->count_for_slow += val;
}


void Player::spawn_player(int x, int y)
{
    this->player_position = new Point(x, y, unlock);
}

void Player::player_journey(int dx, int dy)
{
    this->set_position().set_point_x(dx);
    this->set_position().set_point_y(dy);
    qDebug() << player_position->get_point_x() << " " << player_position->get_point_y();
}

void Player::change_typeBattle()
{
    if (this->type == close_combat){
        this->type = ranged_combat;
        this->set_damage(3);
    }
    else{
        this->type = close_combat;
        this->set_damage(5);
    }
}

TypeBattle Player::get_typeBattle() const
{
    return this->type;
}

Directions Player::get_direction() const
{
    return this->dir;
}

int Player::get_score() const
{
    return this->score;
}

int Player::get_damage() const
{
    return this->damage;
}

int Player::get_zoneX() const
{
    return zoneX;
}

int Player::get_zoneY() const
{
    return zoneY;
}

int Player::get_money() const
{
    return money;
}

int Player::get_count_for_slow() const
{
    return count_for_slow;
}

handPlayer* Player::get_hand()
{
    return myHand;
}

void Player::change_direction_attack(Directions d)
{
    this->dir = d;
}

void Player::change_health(int n)
{
    health = n;
}

void Player::add_money(int val)
{
    this->money += val;
}

void Player::spend_money(int val)
{
    this->money -= val;
}

int Player::get_health() const
{
    return health;
}


std::vector<int> Player::close_attack()
{
    std::vector<int> info_attack;
    info_attack.push_back(this->get_x());
    info_attack.push_back(this->get_y());
    info_attack.push_back(this->damage);
    return info_attack;
}


std::vector<int> Player::ranged_atack()
{
    int user_x = this->get_x();
    int user_y = this->get_y();

    int d = this->get_direction();

    switch(d){
    case 0:
        this->set_zoneX(user_x - 1);
        this->set_zoneY(user_y - 7);
        break;
    case 1:

        this->set_zoneX(user_x - 1);
        this->set_zoneY(user_y + 5);
        break;
    case 2:

        this->set_zoneX(user_x + 5);
        this->set_zoneY(user_y - 1);
        break;
    case 3:

        this->set_zoneX(user_x - 7);
        this->set_zoneY(user_y - 1);
        break;
    }

    std::vector<int> info_attack;
    info_attack.push_back(this->get_x());
    info_attack.push_back(this->get_y());
    info_attack.push_back(this->damage);
    info_attack.push_back(this->dir);
    return info_attack;
}
