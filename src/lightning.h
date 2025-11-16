#ifndef LIGHTNING_H
#define LIGHTNING_H
#include "spellcard.h"
#include "visitor.h"
#include "constants.h"

class Lightning : public spellCard
{
public:
    Lightning();
    ~Lightning() = default;
    virtual bool use_card(Visitor& visitor, int x, int y) override;
    virtual int get_price() const override;
    void upgrade(int level) override;

private:
    int damage;
    int price;
    int width_damage;
};

#endif // LIGHTNING_H
