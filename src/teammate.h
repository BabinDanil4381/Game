#ifndef TEAMMATE_H
#define TEAMMATE_H
#include "spellcard.h"
#include "visitor.h"

class Teammate : public spellCard
{
public:
    Teammate();
    ~Teammate() = default;
    virtual bool use_card(Visitor& visitor, int x, int y) override;
    virtual int get_price() const override;
    void upgrade(int level) override;

private:
    int price;
    int x;
    int y;
    int count;
};

#endif // TEAMMATE_H
