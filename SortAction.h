#ifndef SORTACTION_H_
#define SORTACTION_H_


#include <map>
#include <vector>

#include "AbstractAction.h"
#include "SetenceData.h"



class SortAction : public AbstractAction
{
    private:
        std::map<char, std::vector<int> > m_letter_map;
    public:
        SortAction(int type, AbstractBlackboard * owner = nullptr);

        ~SortAction();

        void doAction();

    private:
        bool buildLetterMap();

        void clearLetterMap();

        void sortAllData();

        void sort();

        void sortOneSetence(SetenceData * tempSetenceData);
};




#endif
