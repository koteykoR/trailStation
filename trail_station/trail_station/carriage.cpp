#include "carriage.h"

Carriage::Carriage()
{
    m_countPlace = 0;
    m_countFreePlace = 0;
    m_costTicket = 0;
    m_type = Undefined;
}

Carriage::Carriage(int countPlace, int countFreePlace, int costTicket, Carriage::Type type)
{
    m_countPlace = countPlace;
    m_countFreePlace = countFreePlace;
    m_costTicket = costTicket;
    m_type = type;
}

Carriage::Carriage(const Carriage &obj)
{
    m_countPlace = obj.m_countPlace;
    m_countFreePlace = obj.m_countFreePlace;
    m_costTicket = obj.m_costTicket;
    m_type = obj.m_type;
}

Carriage &Carriage::operator=(const Carriage &obj)
{
    if (this != &obj) {
        m_countPlace = obj.m_countPlace;
        m_countFreePlace = obj.m_countFreePlace;
        m_costTicket = obj.m_costTicket;
        m_type = obj.m_type;
    }
    return *this;
}


int Carriage::costTicket() const
{
    return m_costTicket;
}

void Carriage::setCostTicket(int costTicket)
{
    m_costTicket = costTicket;
}

Carriage::Type Carriage::type() const
{
    return m_type;
}

void Carriage::setType(const Type &type)
{
    m_type = type;
}

int Carriage::countFreePlace() const
{
    return m_countFreePlace;
}

void Carriage::setCountFreePlace(int countFreePlace)
{
    m_countFreePlace = countFreePlace;
}

int Carriage::countPlace() const
{
    return m_countPlace;
}

void Carriage::setCountPlace(int countPlace)
{
    m_countPlace = countPlace;
}

