#ifndef ABSTRACTBLACKBOARD_H_
#define ABSTRACTBLACKBOARD_H_

#include <map>


#include "AbstractAction.h"


typedef std::pair<int, AbstractAction*> ActionMapPair;

// 数据操作枚举定义
enum BlackBoardState
{
    BlackBoardState_Null,
    BlackBoardState_Input,
    BlackBoardState_Shift,
    BlackBoardState_Sort,
    BlackBoardState_Output,
};

/**
 * 定义抽象黑板, 便于应对数据结构的改变
 * 这个类设计时, 每个类型只能有一个对象
 * 为避免替换对象时, 出现野指针
 */
class AbstractBlackboard
{
    private:
        int m_state;                                          // 数据的状态
        std::map<int, AbstractAction*> m_action_map;         // AbstractAction 的管理器
    public:
        /**
         * 构造
         */
        AbstractBlackboard();
        /**
         * 析构
         */
        virtual ~AbstractBlackboard();
        /**
         * 根据行为类型, 将其保存在 AbstractAction 管理器中
         */
        bool setAbstractActionByType(int type, AbstractAction * abstractAction);
        /**
         * 寻找下一个所要触发的行为
         */
        virtual void call() = 0;
        /**
         * 改变数据的状态
         */
        virtual void changeState() = 0;
    protected:
        /**
         * 根据行为类型获取行为对象
         */
        AbstractAction * getAbstractActionByType(int type);
        /**
         * 根据类型消除指定的行为 Action 对象
         */
        void eraseAbstractActionByType(int type);
        /**
         * 查看管理器中是否含有该类型的对象
         */
        bool inline findAbstractActionByType(int type);
};





#endif
