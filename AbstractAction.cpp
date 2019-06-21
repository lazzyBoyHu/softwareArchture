#include <iostream>



#include "AbstractAction.h"



AbstractAction::AbstractAction(int type) : m_type(type), m_owner(nullptr)
{
}

AbstractAction::AbstractAction(int type, AbstractBlackboard *owner) : m_type(type), m_owner(owner)
{
}

bool AbstractAction::setOwner(AbstractBlackboard * abstractBlackboard)
{
    if (abstractBlackboard == nullptr)
        return false;

    owner = abstractBlackboard;

    return true;
}


void AbstractAction::fire()
{
    doAction();
    m_owner->;
}





