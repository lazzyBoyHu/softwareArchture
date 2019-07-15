#include <iostream>
#include <list>
#include <assert.h>

#include "SortAction.h"
#include "SetenceData.h"



SortAction::SortAction(int type, AbstractBlackboard * owner) : AbstractAction(type, owner)
{
    buildLetterMap();
}

SortAction::~SortAction()
{
    clearLetterMap();
}

bool SortAction::buildLetterMap()
{
    for (char letter = 'A'; letter <= 'Z'; letter++)
    {
        std::vector<int> tempVector;
        m_letter_map.insert(std::pair<char,std::vector<int> >(letter, tempVector));
    }

    return true;
}

void SortAction::clearLetterMap()
{
    auto letterMapBegin = m_letter_map.begin();
    auto letterMapEnd = m_letter_map.end();

    for (auto temMap = letterMapBegin; temMap != letterMapEnd; temMap++)
        temMap->second.clear();
    m_letter_map.clear();
}

void SortAction::doAction()
{
    sortAllData();
}

void SortAction::sortAllData()
{
    char letter = 'A';
    BlackBoard * bb = dynamic_cast<BlackBoard*>(m_owner);
    int length = bb->allData.size();

    for (int index = 0; index < length; index++)
    {
        SetenceData * oneSetence = bb->allData[index];
        if (oneSetence->originData.empty())
            continue;

        auto templist = oneSetence->originData.begin();
        char tempChar = (**templist)[0];
        tempChar = (tempChar >= 'A' && tempChar <= 'Z') ? tempChar : (tempChar-32);
        m_letter_map[tempChar].insert(m_letter_map[tempChar].end(), index);
    }

    for (char letter = 'A'; letter <= 'Z'; letter++)
    {
        std::vector<int> tempVector = m_letter_map[letter];
        if (tempVector.empty())
            continue;

        for (unsigned long j = 1; j <= tempVector.size(); j++)
            bb->allDataSort.insert(bb->allDataSort.end(), tempVector[j]);
    }

    clearLetterMap();
    buildLetterMap();
}

void SortAction::sort()
{
    BlackBoard * bb = dynamic_cast<BlackBoard*>(m_owner);
    auto allDataBegin = bb->allData.begin();
    auto allDataEnd = bb->allData.end();

    for (auto temp = allDataBegin; temp != allDataEnd; temp++)
        sortOneSetence(*temp);
}

void SortAction::sortOneSetence(SetenceData * tempSetenceData)
{
    assert(tempSetenceData != nullptr);
    assert(tempSetenceData->originData.empty() == false);

    int index = 1;
    char letter = 'A';
    auto originBegin = tempSetenceData->originData.begin();
    auto originEnd = tempSetenceData->originData.end();

    for (auto temp = originBegin; temp != originEnd; temp++)
    {
        char tempChar = (**temp)[0];
        tempChar = (tempChar >= 'A' && tempChar <= 'Z') ? tempChar : (tempChar-32);
        m_letter_map[tempChar].insert(m_letter_map[tempChar].end(), index++);
    }

    for (int i = 0; i < 26; i++)
    {
        std::vector<int> tempVector = m_letter_map[letter++];

        if (tempVector.empty())
            continue;

        for (unsigned long j = 1; j <= tempVector.size(); j++)
            tempSetenceData->sortData.insert(tempSetenceData->sortData.end(), tempVector[j]);
    }

    clearLetterMap();
    buildLetterMap();
}





