#include "gamemodel.h"



GameModel::GameModel() :
    enemyTower(new Tower(11, 0)),
    build(new SpawnBuilding(23, 0)),
    mapGame(new Map(*enemyTower, *build, FIELD_HEIGHT, FIELD_WIDTH)),
    user(new Player(3, 19, 3)),
    computer(new Enemy(24, 10)),
    myLeons(),
    myButtons(new Buttons())
{
    score = 0;
    flagAtack = 0;
    m_inGame = true;
}



GameModel::~GameModel(){
    delete myButtons;
    delete build;
    delete mapGame;
    delete user;
    delete computer;
    delete enemyTower;

    for (Leon* leon : myLeons) {
        if (leon != nullptr) {
            delete leon;
        }
    }
    myLeons.clear();
}


Player &GameModel::get_player()
{
    return *user;
}

Enemy &GameModel::get_enemy()
{
    return *computer;
}

Tower &GameModel::get_tower()
{
    return *enemyTower;
}

Map &GameModel::get_map()
{
    return *mapGame;
}

SpawnBuilding &GameModel::get_build()
{
    return *build;
}

std::vector<Leon*>& GameModel::get_leons()
{
    return myLeons;
}

Buttons &GameModel::get_buttons()
{
    return *myButtons;
}


void GameModel::add_leon(int x, int y)
{
    myLeons.push_back(new Leon(x, y));
    notify();
}

int GameModel::get_score(int s) const{
    return score;
}

std::vector<int> GameModel::check_coords_map(int dx, int dy, int count, int type_character)
{
    int nx, ny;
    int x_slow, y_slow;
    if(type_character == 0){
        nx = get_player().get_x() + dx;
        ny = get_player().get_y() + dy;
        x_slow = get_player().get_x();
        y_slow = get_player().get_y();
    }
    else{
        nx = get_enemy().get_coord_x() + dx;
        ny = get_enemy().get_coord_y() + dy;
        x_slow = get_enemy().get_coord_x();
        y_slow = get_enemy().get_coord_y();
    }
    std::vector<int> ret_info = {0, 0, 0};
    if(nx < 0 || nx >= mapGame->get_height() || ny < 0 || ny >= mapGame->get_width() ) return ret_info;
    else if(mapGame->get_point(nx, ny).get_point_opt() == lock || mapGame->get_point(nx, ny).get_point_opt() == tower) return ret_info;
    else if(mapGame->get_point(x_slow, y_slow).get_point_opt() == slow && count != 3) {
        if(type_character == 0) get_player().set_count_for_slow(1);
        else get_enemy().set_count_for_slow(1);
        return ret_info;
    }
    else if(type_character == 1 && mapGame->get_point(nx, ny).get_point_opt() == trap){
        mapGame->set_point(nx, ny).set_option(unlock);
        ret_info[0] = dx;
        ret_info[1] = dy;
        ret_info[2] = 1;
        return ret_info;
    }
    if(type_character == 0 && count == 3) get_player().set_count_for_slow(-3);
    else if(type_character == 1 && count == 3)get_enemy().set_count_for_slow(-3);
    ret_info[0] = dx;
    ret_info[1] = dy;
    ret_info[2] = 0;
    return ret_info;
}

void GameModel::set_score(int s)
{
    this->score = s;
    notify();
}

bool GameModel::get_inGame()
{
    return m_inGame;
}

int GameModel::get_flagAtack()
{
    return flagAtack;
}

void GameModel::change_flagAtack(int val)
{
    this->flagAtack = val;
    notify();
}

void GameModel::change_inGame(bool val)
{
    this->m_inGame = val;
    notify();
}

void GameModel::leon_journey()
{
    if (myLeons.empty()) return;
    const int H = mapGame->get_height();
    const int W = mapGame->get_width();

    std::array<std::pair<int, int>, 4> dirs {{ {1,0}, {-1, 0}, {0, 1}, {0, -1}}};
    std::random_shuffle(dirs.begin(), dirs.end());

    if(std::rand() % 100 < 15) return;
    for(Leon* l : get_leons()){
        if(l != nullptr){
            for (auto [dx, dy] : dirs){
                int nx = l->get_leon_x() + dx;
                int ny = l->get_leon_y() + dy;

                if(nx < 0 || nx >= H || ny < 0 || ny >= W ) continue;
                if(mapGame->get_point(nx, ny).get_point_opt() == lock || mapGame->get_point(nx, ny).get_point_opt() == tower) continue;

                l->set_point_x(nx);
                l->set_point_y(ny);
                hill(l->get_health_ability(), l->get_leon_x(), l->get_leon_y());
                notify();
                break;
            }
        }
    }
    notify();
}

void GameModel::hill(int xp, int x, int y)
{
    if(abs(user->get_x()-x) <= 4 && abs(user->get_y()-y) <= 4 && user->get_health() < 100){
        user->change_health(user->get_health() + xp);
    }
    notify();
}

void GameModel::player_close_attack()
{
    std::vector<int> result_info;
    result_info = get_player().close_attack();
    if(abs(get_enemy().get_coord_x() - result_info[0]) <= 1 && abs(get_enemy().get_coord_y() - result_info[1]) <= 1){
        get_enemy().subtract_health(result_info[2]);
        set_score(result_info[2]);
    }

    if(get_enemy().get_health() == 0){
        if(get_tower().get_alive() == true){
            get_enemy().set_alive(false);
            get_build().spawn(get_enemy(), 23, 2);
            get_enemy().set_alive(true);
            get_enemy().recovery_health();
        }
        else{
            get_enemy().set_alive(false);
        }
    }
}

void GameModel::player_ranged_attack()
{
    std::vector<int> result_info;
    result_info = get_player().ranged_atack();

    int user_x = result_info[0];
    int user_y = result_info[1];

    int enemy_x = get_enemy().get_coord_x();
    int enemy_y = get_enemy().get_coord_y();

    int tower_x = get_tower().get_left_x();
    int tower_y = get_tower().get_down_y();

    switch(result_info[3]){
    case 0:
        if((user_y + 5) < FIELD_WIDTH && (abs(enemy_x - user_x) <= 1) && (user_y - enemy_y) >= 5 && (user_y - enemy_y) <= 7){
            get_enemy().subtract_health(result_info[2]);
            set_score(result_info[2]);
        }
        if((user_y + 5) < FIELD_WIDTH && (user_x - 1) == tower_x && (user_y - 7) == tower_y && get_tower().get_alive() == true){
            get_tower().sub_health(result_info[2]);
            set_score(result_info[2]);
        }
        break;
    case 1:
        if((user_y - 5) >= 0 && (abs(enemy_x - user_x) <= 1) && (enemy_y - user_y) >= 5 && (enemy_y - user_y) <= 7){
            get_enemy().subtract_health(result_info[2]);
            set_score(result_info[2]);
        }
        break;
    case 2:
        if((user_x + 5) < FIELD_HEIGHT && (abs(enemy_y - user_y) <= 1) && (enemy_x - user_x) >= 5 && (enemy_x - user_x) <= 7){
            get_enemy().subtract_health(result_info[2]);
            set_score(result_info[2]);
        }
        if((user_x + 5) < FIELD_HEIGHT && (user_x + 5) == tower_x && (user_y - 1) == tower_y && get_tower().get_alive() == true){
            get_tower().sub_health(result_info[2]);
            set_score(result_info[2]);
        }
        break;
    case 3:
        if((user_x + 5) >= 0 && (abs(enemy_y - user_y) <= 1) && (user_y - enemy_y) >= 5 && (user_y - enemy_y) <= 7){
            get_enemy().subtract_health(result_info[2]);
            set_score(result_info[2]);
        }
        if((user_x + 5) >= 0 && (user_x - 7) == tower_x && (user_y - 1) == tower_y && get_tower().get_alive() == true){
            get_tower().sub_health(result_info[2]);
            set_score(result_info[2]);
        }
        break;
    }
    if(get_enemy().get_health() == 0){
        get_enemy().set_alive(false);
        get_build().spawn(get_enemy(), 23, 2);
        get_enemy().set_alive(true);
        get_enemy().recovery_health();
    }
}

void GameModel::enemy_journey()
{
    std::vector<int> info_coord = get_enemy().random_journey();
    info_coord = check_coords_map(info_coord[0], info_coord[1], info_coord[2], info_coord[3]);
    if(info_coord[2] == 1){
        get_enemy().subtract_health(get_player().get_hand()->get_trap_card().get_damage());
        get_enemy().set_position(info_coord[0], info_coord[1]);
    }
    else if(info_coord[0] + info_coord[1] != 0) get_enemy().set_position(info_coord[0], info_coord[1]);
}

void GameModel::enemy_attack()
{
    change_flagAtack(1);
    std::vector<int> info_attack = get_enemy().enemy_atack();
    int x = info_attack[0];
    int y = info_attack[1];

    int u_x = get_player().get_x();
    int u_y = get_player().get_y();

    if(abs(u_x - x) <= 1 && abs(u_y - y) <= 1){
        get_player().change_health(get_player().get_health() - info_attack[2]);
    }
}

void GameModel::tower_attack()
{
    std::vector<int> info_attack = get_tower().attack();

    int left_x = info_attack[0];
    int down_y = info_attack[1];

    int user_x = get_player().get_x();
    int user_y = get_player().get_y();

    if(abs(user_x - (left_x + 1)) <= 7 && abs(user_y - (down_y + 1)) <= 7 && get_tower().get_alive()){
        get_player().change_health(get_player().get_health() - get_player().get_hand()->get_card_poison().get_damage()/2);
    }
}

