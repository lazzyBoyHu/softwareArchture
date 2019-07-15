#include <iostream>


#include "AbstractAction.h"
#include "AbstractBlackboard.h"



AbstractAction::AbstractAction(int type, AbstractBlackboard *owner) : m_type(type), m_owner(owner)
{
}

bool AbstractAction::setOwner(AbstractBlackboard * abstractBlackboard)
{
    if (abstractBlackboard == nullptr)
        return false;

    m_owner = abstractBlackboard;

    return true;
}

void AbstractAction::fire()
{
    if (m_owner == nullptr)
        return;

    doAction();

    m_owner->changeState();
    m_owner->call();
}





