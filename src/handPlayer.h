#ifndef HANDPLAYER_H
#define HANDPLAYER_H

#include "lightning.h"
#include "poison.h"
#include "trap.h"
#include "teammate.h"
#include "improve.h"
#include <string>
#include "visitor.h"
#include <cstdlib>

class spellCard;


class handPlayer
{
public:
    handPlayer(int hand_size);
    ~handPlayer();
    void find_and_use(Visitor& visitor, std::string str, int x, int y);
    Poison& get_card_poison();
    Trap& get_trap_card();
    Lightning& get_card_lightning();
    Improve& get_improve_card();
    Teammate& get_teammate_card();
    void first_random_card(Visitor& visitor);
private:
    std::vector<spellCard*> list;
    std::vector<spellCard*> mySpell;
    Lightning* spellLight;
    Trap* spellTrap;
    Poison* spellPoison;
    Teammate* spellTeammate;
    Improve* spellImprove;
    int max_size;
    int current_size;
};

#endif // HANDPLAYER_H
