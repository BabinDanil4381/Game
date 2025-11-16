#include "handplayer.h"
#include <QString>
#include <ctime>
#include <cstdlib>
#include "buttons.h"
#include <QDebug>

handPlayer::handPlayer(int size_hand) {
    spellLight = new Lightning();
    spellTrap = new Trap();
    spellPoison = new Poison();
    spellTeammate = new Teammate();
    spellImprove = new Improve();
    max_size = size_hand;
    current_size = 1;
    list.push_back(spellLight);
    list.push_back(spellTrap);
    list.push_back(spellPoison);
    list.push_back(spellTeammate);
    list.push_back(spellImprove);

}

handPlayer::~handPlayer() {
    delete spellLight;
    delete spellTrap;
    delete spellPoison;
    delete spellTeammate;
    delete spellImprove;
}

void handPlayer::find_and_use(Visitor& visitor, std:: string str, int x, int y) /// ПОМЕНЯТЬ В КОДЕ POS НА X, Y
{
    int number_spell = std::stoi(str);
    spellCard* target_spell = list[number_spell];

    auto target_it = std::find(mySpell.begin(), mySpell.end(), target_spell);
    auto improve_it = std::find(mySpell.begin(), mySpell.end(), spellImprove);

        // Покупка карты
    if (y / DOT_WIDTH > FIELD_WIDTH - 1) {
        if (current_size < max_size && visitor.visitPlayer(target_spell->get_price())) {
            mySpell.push_back(target_spell);
            int count = std::count(mySpell.begin(), mySpell.end(), target_spell);
            visitor.visitButtons(number_spell, count);
            current_size++;
        }
    }

    else if(y / DOT_WIDTH < FIELD_WIDTH && improve_it != mySpell.end() && target_it != mySpell.end()){

        // Улучшаем карту
        (*target_it)->upgrade(spellImprove->get_level());
        (*target_it)->use_card(visitor, x, y);

        // Удаляем улучшаемую карту (если это не карта улучшения)
        if(target_spell != spellImprove) {
            mySpell.erase(target_it);
            current_size--;
        }

        // Удаляем карту улучшения
        mySpell.erase(improve_it);
        int count = std::count(mySpell.begin(), mySpell.end(), list[4]);
        visitor.visitButtons(4, count);
        int count2 = std::count(mySpell.begin(), mySpell.end(), target_spell);                            
        visitor.visitButtons(number_spell, count2);
        current_size --;
    }

    // Использование уже купленной карты
    else if (x / DOT_HEIGHT < FIELD_HEIGHT && y / DOT_WIDTH < FIELD_WIDTH && target_it != mySpell.end())
    {
        if((*target_it)->use_card(visitor, x, y)){
            mySpell.erase(target_it);
            int count = std::count(mySpell.begin(), mySpell.end(), target_spell);
            visitor.visitButtons(number_spell, count);
            current_size--;
        }
    }
}

Poison& handPlayer::get_card_poison()
{
    return *spellPoison;
}

Trap& handPlayer::get_trap_card()
{
    return *spellTrap;
}

Lightning& handPlayer::get_card_lightning()
{
    return *spellLight;
}

Improve& handPlayer::get_improve_card()
{
    return *spellImprove;
}

Teammate& handPlayer::get_teammate_card()
{
    return *spellTeammate;
}



void handPlayer::first_random_card(Visitor& visitor)
{
    std::srand(std::time(nullptr));
    int random_num = std::rand() % 5;
    mySpell.push_back(list[random_num]);
    visitor.visitButtons(random_num, 1);
    current_size = 1;
}
