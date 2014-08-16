#ifndef _ALG_ASTARITEM_H_
#define _ALG_ASTARITEM_H_

// A*�㷨�еĽڵ���Ϣ��
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
    int         _id_col;   // ��
    int         _id_row;   // ��

    CC_SYNTHESIZE(int, _id_g, G);       // ʵ�ʴ���
    CC_SYNTHESIZE(int, _id_h, H);       // ���ƴ���
    CC_SYNTHESIZE(int, _id_fid, Fid);   // ���ڵ� 
    CC_SYNTHESIZE(int, _id_f, F);       // ���ۺ��� f = g + h 

};

#endif // end _ALG_ASTARITEM_H_