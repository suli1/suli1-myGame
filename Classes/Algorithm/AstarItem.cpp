#include "AstarItem.h"


AstarItem::AstarItem()
    : _id_col(0)
    , _id_row(0)
    , _id_h(0)
    , _id_g(0)
    , _id_fid(0)
    , _id_f(0)
{

}

AstarItem::~AstarItem()
{
}

bool AstarItem::init()
{
    return true;
}


void AstarItem::setPos(int col, int row)
{
    _id_col = col;
    _id_row = row;
}



