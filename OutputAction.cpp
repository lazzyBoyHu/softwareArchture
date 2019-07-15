#include <iostream>
#include <assert.h>


#include "OutputAction.h"
#include "SetenceData.h"



void OutputAction::doAction()
{
    printAll();
    //printOriginData();
}

void OutputAction::printAll()
{
    printAllShiftSetence();
    printAllSortSetence();
}

void OutputAction::printOriginData()
{
    BlackBoard * bb = dynamic_cast<BlackBoard*>(m_owner);
    auto allDataBegin = bb->allData.begin();
    auto allDataEnd = bb->allData.end();

    for (auto temp = allDataBegin; temp != allDataEnd; temp++)
        printOneOriginData(*temp);
}

void OutputAction::printSortOriginData()
{
    BlackBoard * bb = dynamic_cast<BlackBoard*>(m_owner);
    auto allSortDataBegin = bb->allDataSort.begin();
    auto allSortDataEnd = bb->allDataSort.end();

    for (auto temp = allSortDataBegin; temp != allSortDataEnd; temp++)
        printOneOriginData((bb->allData)[*temp]);
}

void OutputAction::printOneOriginData(SetenceData * tempSetenceData)
{
    assert(tempSetenceData != nullptr);

    std::string result("");
    spliteString(&result, tempSetenceData->originData);
    printOneString(&result);
}

void OutputAction::printOneShiftSetence(SetenceData * tempSetenceData)
{
    assert(tempSetenceData != nullptr);

    auto shiftBegin = tempSetenceData->shiftData.begin();
    auto shiftEnd = tempSetenceData->shiftData.end();

    for (auto temp = shiftBegin; temp != shiftEnd; temp++)
    {
        std::string result("");
        spliteString(&result, temp->second);
        printOneString(&result);
    }
}

void OutputAction::printAllShiftSetence()
{
    BlackBoard * bb = dynamic_cast<BlackBoard*>(m_owner);
    auto allDataBegin = bb->allData.begin();
    auto allDataEnd = bb->allData.end();

    for (auto temp = allDataBegin; temp != allDataEnd; temp++)
        printOneShiftSetence(*temp);
}

void OutputAction::printOneSortSetence(SetenceData *tempSetenceData, int index)
{
    assert(tempSetenceData != nullptr);
    assert(index > 0);
    assert(index < tempSetenceData->sortData.size());

    std::string result("");
    spliteString(&result, tempSetenceData->shiftData[index]);
    printOneString(&result);
}

void OutputAction::printOneAllSortSetence(SetenceData *tempSetenceData)
{
    assert(tempSetenceData != nullptr);

    int max = tempSetenceData->sortData.size();
    for (int index = 1; index <= max; index++)
        printOneSortSetence(tempSetenceData, index);
}

void OutputAction::printAllSortSetence()
{
    BlackBoard * bb = dynamic_cast<BlackBoard*>(m_owner);
    auto allDataBegin = bb->allData.begin();
    auto allDataEnd = bb->allData.end();

    for (auto temp = allDataBegin; temp != allDataEnd; temp++)
        printOneAllSortSetence(*temp);
}

void OutputAction::spliteString(std::string * result, std::list<std::string*> list)
{
    auto listBegin = list.begin();
    auto listEnd = list.end();

    for (auto temp = listBegin; temp != listEnd; temp++)
    {
        result->append(**temp);
        if (temp != list.cend())
            result->append(" ");
    }
}

void OutputAction::printOneString(std::string * oneString)
{
    std::cout << *oneString << std::endl;
}





















