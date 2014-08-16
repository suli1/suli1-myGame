#ifndef _ALG_ASTAR_H_
#define _ALG_ASTAR_H_

// A*�㷨��ʵ����

#include "cocos2d.h"

USING_NS_CC; 

class Astar
{
public:
    Astar();
    ~Astar();

    __Array* findPath(int curX, int curY, int aimX, int aimY, TMXTiledMap* passmap);

private:
    int getG(int col, int row, int id);
    int getH(int col, int row);

    // ��open�б��е�Ԫ�ص���close�б�
    void fromOpenToClose();

    void removeFromOpen();

    // �������·��
    void getPath();

    void starSearch(int fid);

    void resetSort(int last);

    bool checkMap(int col, int row);

    bool checkClose(int col, int row);

    bool checkOpen(int col, int row, int id);

    void addToOpen(int col, int row, int id);
    
    void clear();

private:
    int         _curCol;
    int         _curRow;
    int         _aimCol;
    int         _aimRow;

    TMXTiledMap*     _map;

    __Array*        _open;
    __Array*        _close;
    __Array*        _path;
};

#endif // end _ALG_ASTAR_H_