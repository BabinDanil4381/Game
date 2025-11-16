#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include "tower.h"
#include "enemy.h"
#include "map.h"
#include "player.h"
#include "spawnbuilding.h"
#include "observable.h"
#include "buttons.h"
#include "leon.h"


class GameModel : public Observable{
private:
    Tower* enemyTower;
    SpawnBuilding* build;
    Map* mapGame;
    Player* user;
    Enemy* computer;
    std::vector<Leon*> myLeons;
    std::vector<Observer *> obs;
    Buttons* myButtons;
    int score;
    int flagAtack;
    bool m_inGame;

public:
    GameModel();
    ~GameModel();
    Player& get_player();
    Enemy& get_enemy();
    Tower& get_tower();
    Map& get_map();
    SpawnBuilding& get_build();
    std::vector<Leon*>& get_leons();
    Buttons& get_buttons();
    void add_leon(int x, int y);
    void set_score(int s);
    int get_score(int s) const;
    std::vector<int> check_coords_map(int x, int y, int count, int type_character);
    bool get_inGame();
    int get_flagAtack();
    void change_flagAtack(int val);
    void change_inGame(bool val);
    void leon_journey();
    void hill(int xp, int x, int y);
    void player_close_attack();
    void player_ranged_attack();
    void enemy_journey();
    void enemy_attack();
    void tower_attack();
};

#endif // GAMEMODEL_H
