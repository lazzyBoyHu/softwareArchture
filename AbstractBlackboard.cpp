#include <iostream>


#include "AbstractBlackboard.h"



AbstractBlackboard::AbstractBlackboard()
{
    m_state = 0;
    m_action_map.clear();
}

AbstractBlackboard::~AbstractBlackboard()
{
    AbstractAction * tempAction;
    auto mapBegin = m_action_map.begin();
    auto mapEnd = m_action_map.end();

    for (auto temp = mapBegin; temp != mapEnd; temp++)
        if ((tempAction = temp->second) != nullptr)
            delete tempAction;

    m_action_map.clear();
}

bool AbstractBlackboard::setAbstractActionByType(int type, AbstractAction * abstractAction)
{
    AbstractAction * quondamAction = nullptr;

    if (abstractAction == nullptr)
        return false;
    if (type > AbstractActionType_Alphabetizer or type < AbstractActionType_Input)
        return false;
    if ((quondamAction = m_action_map[type]) != nullptr)
        delete quondamAction;   // 如果是直接覆盖可能会内存泄漏

    auto ret = m_action_map.insert(ActionMapPair(type, abstractAction));

    if (ret.second == false)
        return false;
    return true;
}

AbstractAction * AbstractBlackboard::getAbstractActionByType(int type)
{
    return m_action_map[type];
}

void AbstractBlackboard::eraseAbstractActionByType(int type)
{
    AbstractAction * action = m_action_map[type];
    delete action;
}


bool AbstractBlackboard::findAbstractActionByType(int type)
{
    if (m_action_map[type] == nullptr)
        return false;
    return true;
}







