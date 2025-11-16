#ifndef IMPROVE_H
#define IMPROVE_H
#include <QPoint>
#include "spellCard.h"
#include "visitor.h"
#include "constants.h"

class Improve : public spellCard
{
public:
    Improve();
    ~Improve() =default;
    virtual bool use_card(Visitor& visitor, int x, int y) override;
    virtual int get_price() const override;
    void upgrade(int level) override;
    int get_level();

private:
    int price;
    int level;
};

#endif // IMPROVE_H
