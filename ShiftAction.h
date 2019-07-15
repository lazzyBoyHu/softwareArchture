#ifndef SHIFTACTION_H_
#define SHIFTACTION_H_


#include <list>
#include <string>


#include "AbstractAction.h"
#include "SetenceData.h"



class ShiftAction : public AbstractAction
{
    public:
        ShiftAction(int type, AbstractBlackboard * owner) : AbstractAction(type, owner)
        {
        }
        ~ShiftAction()
        {
        }

        void doAction();

    private:
        void shift();
};

#endif
