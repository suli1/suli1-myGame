#ifndef _ALG_ASTARITEM_H_
#define _ALG_ASTARITEM_H_

// A*算法中的节点信息类
#include "cocos2d.h"

USING_NS_CC;

class AstarItem : public Ref
{
public:
    CREATE_FUNC(AstarItem);
protected:
    AstarItem();
    ~AstarItem();

    virtual bool init();

public:
    void setPos(int col, int row);
    int getCol() { return _id_col; }
    int getRow() { return _id_row; }

private:
    int         _id_col;   // 列
    int         _id_row;   // 行

    CC_SYNTHESIZE(int, _id_g, G);       // 实际代价
    CC_SYNTHESIZE(int, _id_h, H);       // 估计代价
    CC_SYNTHESIZE(int, _id_fid, Fid);   // 父节点 
    CC_SYNTHESIZE(int, _id_f, F);       // 估价函数 f = g + h 

};

#endif // end _ALG_ASTARITEM_H_