#ifndef ABSTRACTACTION_H_
#define ABSTRACTACTION_H_





#include "AbstractBlackboard.h"


enum AbstractActionType
{
    AbstractActionType_Input,
    AbstractActionType_Output,
    AbstractActionType_Shift,
    AbstractActionType_Alphabetizer,
};

class AbstractAction
{
    private:
        int m_type;                             // 用于标识行为
    protected:
        AbstractBlackboard * m_owner;           // 用于行为类反向找到黑板类
    public:
        /**
         * 构造
         * 可以在构造时绑定黑板, 也可以不用绑定
         */
        AbstractAction(int type, AbstractBlackboard * owner = nullptr);
        /**
         * 析构函数
         */
        virtual ~AbstractAction() {}
        /**
         * 动态绑定黑板
         */
        bool setOwner(AbstractBlackboard * abstractBlackboard);
        /**
         * 触发行为的入口
         */
        void fire();
    protected:
        /**
         * 行为的具体实现接口
         */
        virtual void doAction() = 0;
};



#endif
