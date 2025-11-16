#ifndef POISON_H
#define POISON_H
#include "spellcard.h"
#include "visitor.h"
#include "constants.h"

class Poison : public spellCard
{
public:
    Poison();
    ~Poison() = default;
    virtual bool use_card(Visitor& visitor, int x, int y) override;
    int get_damage() const;
    virtual int get_price() const override;
    void upgrade(int level) override;

private:
    int damage;
    int price;
    int radius;

};

#endif // POISON_H
