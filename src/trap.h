#ifndef TRAP_H
#define TRAP_H
#include "spellcard.h"
#include "visitor.h"

class Trap : public spellCard
{
public:
    Trap();
    ~Trap() = default;
    virtual bool use_card(Visitor& visitor, int x, int y) override;
    virtual int get_price() const override;
    virtual void upgrade(int level) override;
    int get_damage() const;

private:
    int damage;
    int price;
};

#endif // TRAP_H
