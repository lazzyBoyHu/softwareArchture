#ifndef ABSTRACTBLACKBOARD_H_
#define ABSTRACTBLACKBOARD_H_

#include <map>



typedef std::pair<int, AbstractAction*> ActionMapPair

// 数据操作枚举定义
enum BlackBoardState
{
    BlackBoardState_Null,
    BlackBoardState_Input,
    BlackBoardState_Shift,
    BlackBoardState_Sort,
    BlackBoardState_Output,
};

// 定义抽象黑板, 便于应对数据结构的改变
class AbstractBlackboard
{
    private:
        map<int, AbstractAction*> m_actionMap;
    public:
        AbstractBlackboard();
        virtual ~AbstractBlackboard();
        bool setAbstractActionByType(int type, AbstractAction * abstractAction);
        AbstractAction * getAbstractActionByType(int type);
        virtual void call() = 0;
        virtual void changeState() = 0;
};





#endif
