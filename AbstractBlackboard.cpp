#include <iostream>


#include "AbstractBlackboard.h"



AbstractBlackboard::AbstractBlackboard()
{
    m_actionMap.clean();
}

virtual AbstractBlackboard::~AbstractBlackboard()
{
    AbstractAction * tempAction;
    auto mapBegin = m_actionMap.begin();
    auto mapEnd = m_actionMap.end();

    for (auto temp = mapBegin; auto != mapEnd; temp++)
        if ((tempAction = temp->second) != nullptr)
            delete tempAction;

    m_actionMap.clean()
}

bool AbstractBlackboard::setAbstractActionByType(int type, AbstractAction * abstractAction)
{
    auto ret;
    AbstractAction * quondamAction = nullptr;

    if (abstractAction == nullptr)
        return false;
    if (type > AbstractActionType_Alphabetizer or type < AbstractActionType_Input)
        return false;
    if ((quondamAction = m_actionMap[type].second) != nullptr)
        delete quondamAction;   // 如果是直接覆盖可能会内存泄漏

    ret = m_actionMap.insert(ActionMapPair(type, abstractAction));

    if (ret->second == false)
        return false;
    return true;
}

AbstractAction * AbstractBlackboard::getAbstractActionByType(int type)
{
    return m_actionMap[type].second;
}
