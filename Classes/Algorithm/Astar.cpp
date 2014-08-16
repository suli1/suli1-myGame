#include "Astar.h"
#include "AstarItem.h"

Astar::Astar()
    : _curCol(0)
    , _curRow(0)
    , _aimCol(0)
    , _aimRow(0)
    , _map(nullptr)
    , _open(nullptr)
    , _close(nullptr)
    , _path(nullptr)
{

}


Astar::~Astar()
{
    clear();
}

void Astar::clear()
{
    _map = nullptr;
    //CC_SAFE_RELEASE(_open);
    //CC_SAFE_RELEASE(_close);
}



int Astar::getG(int col, int row, int id)
{
    auto item = (AstarItem*)_close->getObjectAtIndex(id);

    int fx = item->getCol();
    int fy = item->getRow();
    int fg = item->getG();
    if(fx - col != 0 && fy - row != 0) {
        return fg + 14;
    } else {
        return fg + 10;
    }

}

int Astar::getH(int col, int row)
{
    return abs(_aimCol - col) * 10 + abs(_aimRow - row) * 10;
}

// ��_open�б��1��object�Ƶ�_close�б�ĩβ
void Astar::fromOpenToClose()
{
    AstarItem* temp = (AstarItem*)_open->getObjectAtIndex(1);
    _close->addObject(temp);
    removeFromOpen();
}

// 
void Astar::removeFromOpen()
{
    //_open->replaceObjectAtIndex(1, _open->getLastObject(), true);
    //_open->removeLastObject();
    _open->removeObjectAtIndex(1);

    int last = _open->count() - 1;
    
    // ������
    int head = 1;
    while( head * 2 + 1 <= last ) {
        int child1 = head*2;
        int child2 = head*2 + 1;

        int childmin = ((AstarItem*)_open->getObjectAtIndex(child1))->getF() < ((AstarItem*)_open->getObjectAtIndex(child2))->getF() ? child1 : child2;

        if( ((AstarItem*)_open->getObjectAtIndex(head))->getF() <= ((AstarItem*)_open->getObjectAtIndex(childmin))->getF() ) {
            break;

        }

        AstarItem* temp = (AstarItem*)_open->getObjectAtIndex(childmin);
        _open->replaceObjectAtIndex(childmin, _open->getObjectAtIndex(head), false);
        _open->replaceObjectAtIndex(head, temp, true);

        // temp->release(); // ?

        head = childmin;

    }


}

void Astar::getPath()
{
    // ������close�������ҳ�·��
    if(_path->count() == 0) {
        _path->addObject(_close->getObjectAtIndex(_close->count() - 1));

    } else {
        _path->insertObject(_close->getObjectAtIndex(_close->count() - 1), _path->count() - 1);
    }

    while(true) {
        if(((AstarItem*)_path->getObjectAtIndex(0))->getG() == 0) {
            // �����յ�
            break;;
        }

        // ����·��������
        _path->insertObject(_close->getObjectAtIndex(((AstarItem*)_path->getObjectAtIndex(0))->getFid()), 0);
        _curCol = _aimCol;
        _curRow = _aimRow;
    }
}

void Astar::starSearch(int fid)
{
    auto item = (AstarItem*)_close->getObjectAtIndex(fid);
    int col = item->getCol();
    int row = item->getRow();

    // ����Ŀǰ�ĵ���ϣ��£������ĸ�����

    // ��
    int mycol = col;
    int myrow = row - 1;
    if(myrow >= 0 && checkMap(mycol, myrow)) {
        if(checkOpen(mycol, myrow, fid) && checkClose(mycol, myrow)) {
            addToOpen(mycol, myrow, fid);
        }
    }

    // ��
    mycol = col - 1;
    myrow = row;
    if(mycol >= 0 && checkMap(mycol, myrow)) {
        if(checkOpen(mycol, myrow, fid) && checkClose(mycol, myrow)) {
            addToOpen(mycol, myrow, fid);
        }
    }

    // ��
    mycol = col;
    myrow = row + 1;
    if(myrow < _map->getMapSize().height && checkMap(mycol, myrow)) {
        if(checkOpen(mycol, myrow, fid) &&checkClose(myrow, myrow)) {
            addToOpen(mycol, myrow, fid);
        }
    }

    // ��
    mycol = col + 1;
    myrow = row;
    if(mycol < _map->getMapSize().height && checkMap(mycol, myrow)) {
        if(checkOpen(mycol, myrow, fid) &&checkClose(myrow, myrow)) {
            addToOpen(mycol, myrow, fid);
        }
    }

}

void Astar::resetSort(int last)
{
    // ���ݲ������ж�����
    while(last > 1) {
        int half = last/2;
        auto itemHalf = (AstarItem*)_open->getObjectAtIndex(half);
        auto itemLast = (AstarItem*)_open->getObjectAtIndex(last);

        if(itemHalf->getF() <= itemLast->getF()) {
            break;
        }

        /*if(((AstarItem*)_open->getObjectAtIndex(half))->getF() <= ((AstarItem*)_open->getObjectAtIndex(last))->getF()) {
            break;
        }*/

        AstarItem* temp = (AstarItem*)_open->getObjectAtIndex(last);
        _open->replaceObjectAtIndex(last, _open->getObjectAtIndex(half), false);
        _open->replaceObjectAtIndex(half, temp, true);

        //temp->release();

        last = half;
    }
}

// ����ͼ�ϸõ��Ƿ���ͨ��
bool Astar::checkMap(int col, int row)
{
    // ����ͼ���Ƿ�����ײ
    if(abs(_aimCol - col) > 0 || abs(_aimRow - row) > 0) {
        TMXLayer* layer = _map->getLayer("grass");
        int tilegid = layer->getTileGIDAt(Point(col, row));

        //Dictionary* tiledic = _map->propertiesForGID(tilegid);
        //String* mvalue = (String*)tiledic->objectForKey("conflict");
        //int mv = mvalue->intValue();
        Value tileValue = _map->getPropertiesForGID(tilegid);
        int touchValue = tileValue.asValueMap().at("conflict").asInt();
        if(touchValue == 1) {
            // ��⵽����ײ
            return false;
        }
    }

    return true;
}

bool Astar::checkClose(int col, int row)
{
    // ���close�б����Ƿ���������
    for(int i = _close->count() - 1; i > 0; i--) {
        if(((AstarItem*)_close->getObjectAtIndex(i))->getCol() == col
            && ((AstarItem*)_close->getObjectAtIndex(i))->getRow() == row) {
                return false;
        }
    }

    return true;
}

bool Astar::checkOpen(int col, int row, int id)
{
    // ���open�б����Ƿ��и�С�Ĳ�����������
    for(int i = _open->count() - 1; i > 0; i--) {
        auto item = (AstarItem*)_open->getObjectAtIndex(i);
        if(item->getCol() == col && item->getRow() == row) {
            int tempG = getG(col, row, id);
            if(tempG < item->getG()) {
                item->setG(tempG);
                item->setFid(id);
                item->setF(tempG + item->getH());
                resetSort(i);
            }
            return false;
        }
    }

    return true;
}

void Astar::addToOpen(int col, int row, int id)
{
    CC_ASSERT(_open != nullptr && "the open is nullptr");

    AstarItem* temp = AstarItem::create();
    temp->setPos(col, row);
    temp->setFid(id);
    int g = getG(col, row, id);
    int h = getH(col, row);
    temp->setG(g);
    temp->setH(h);
    temp->setF(g +h);
    _open->addObject(temp);

    resetSort(_open->count() - 1);
}

__Array* Astar::findPath(int curX, int curY, int aimX, int aimY, TMXTiledMap* passmap)
{
    // �����Լ���¼·�������ʼ��
    _curCol = curX;
    _curRow = curY;
    _aimCol = aimX;
    _aimRow = aimY;

    _map = passmap;
    _path = __Array::create();
    _path->retain();

    _open = __Array::create();

    CC_ASSERT(_path && _open);

    AstarItem* temp = AstarItem::create();
    _open->addObject(temp);

    AstarItem* temp1 = AstarItem::create();
    temp1->setPos(_curCol, _curRow);
    temp1->setG(0);
    int ag = getH(_curCol, _curRow);
    temp1->setH(ag);
    temp1->setFid(0);
    temp1->setF(ag);
    _open->addObject(temp1);

    _close = __Array::create();

    CC_ASSERT(_close);
    
    // ����Ѱ��·��
    while(_open->count() >1) {
        fromOpenToClose();
        int fatherID = _close->count() - 1;
        if(abs(_aimCol - ((AstarItem*)_close->getObjectAtIndex(fatherID))->getCol()) < 1 
            && abs(_aimRow - ((AstarItem*)_close->getObjectAtIndex(fatherID))->getRow()) < 1 )  {
           getPath();
           break;

        } else {
            starSearch(fatherID);
        }
    }

    _open->removeAllObjects();
    _close->removeAllObjects();

    // ��ȡ·��
    if(_path->count() == 0) {
        return nullptr;

    } else {
        if( ((AstarItem*)_path->getLastObject())->getCol() != _aimCol
            || ((AstarItem*)_path->getLastObject())->getRow() != _aimRow ) {
                AstarItem* temp = AstarItem::create();
                temp->setPos(_aimCol, _aimRow);
                _path->addObject(temp);
        }
        return _path;

    }
}
