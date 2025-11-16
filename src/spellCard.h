#ifndef SPELLCARD_H
#define SPELLCARD_H
class Visitor;

class spellCard
{
public:
    virtual bool use_card(Visitor& visitor, int x, int y) = 0;
    virtual int get_price() const = 0;
    virtual void upgrade(int level) = 0;
    virtual ~spellCard() = default;
};

#endif // SPELLCARD_H
