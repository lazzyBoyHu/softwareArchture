#ifndef OUTPUTACTION_H_
#define OUTPUTACTION_H_






#include "AbstractAction.h"
#include "SetenceData.h"


class OutputAction : public AbstractAction
{
    public:
        OutputAction(int type, AbstractBlackboard * owner) : AbstractAction(type, owner)
        {
        }
        ~OutputAction()
        {
        }

        void doAction();

    private:
        void printAll();

        void printOriginData();

        void printSortOriginData();

        void printOneOriginData(SetenceData * tempSetenceData);

        void printOneShiftSetence(SetenceData * tempSetenceData);

        void printAllShiftSetence();

        void printOneSortSetence(SetenceData *tempSetenceData, int index);

        void printOneAllSortSetence(SetenceData *tempSetenceData);

        void printAllSortSetence();

        void spliteString(std::string * result, std::list<std::string*> list);

        void printOneString(std::string * oneString);
};

#endif
