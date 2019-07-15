#include <iostream>


#include "ShiftAction.h"




void ShiftAction::doAction()
{
    shift();
}

void ShiftAction::shift()
{
    BlackBoard * bb = dynamic_cast<BlackBoard*>(m_owner);
    auto allDataBegin = bb->allData.begin();
    auto allDataEnd = bb->allData.end();

    for (auto temp = allDataBegin; temp != allDataEnd; temp++)
    {
        SetenceData * tempSetenceData = *temp;
        if (tempSetenceData == nullptr || tempSetenceData->originData.empty())
            continue;

        int length = tempSetenceData->originData.size();
        for (int index = 1; index <= length; index++)
        {
            std::list<std::string*>::iterator copyBegin;
            std::list<std::string*>::iterator copyEnd;
            copyBegin = tempSetenceData->shiftData[index-1].begin();
            copyEnd = tempSetenceData->shiftData[index-1].end();
            if (index == 1)
            {
                copyBegin = tempSetenceData->originData.begin();
                copyEnd = tempSetenceData->originData.end();
            }

            std::list<std::string*> tempList;
            tempList.clear();

            for (auto tempString = copyBegin; tempString != copyEnd; tempString++)
                tempList.push_back(*tempString);

            if (index != 1)
            {
                std::string * copyString = *tempList.begin();
                tempList.pop_front();
                tempList.push_back(copyString);
            }
            tempSetenceData->shiftData[index] = tempList;
        }
    }
}



























