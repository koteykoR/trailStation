#include "passenger.h"

Passenger::Passenger(QObject *parent)
{
    m_guest = true;
}

Passenger::Passenger(QString login, QString password) : User(login, password, Type::PassengerType)
{
    if (login.isEmpty() || password.isEmpty())
        m_guest = true;
    else
        m_guest = false;
}

bool Passenger::guest() const
{
    return m_guest;
}

void Passenger::setGuest(bool guest)
{
    m_guest = guest;
}
