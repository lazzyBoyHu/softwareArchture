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
        int m_type;
    protected:
        AbstractBlackboard * m_owner;
    public:
        AbstractAction(int type);
        AbstractAction(int type, AbstractBlackboard *owner);
        virtual ~AbstractAction() {}
        bool setOwner(AbstractBlackboard * abstractBlackboard);
        void fire();
        virtual void doAction() = 0
};



#endif
