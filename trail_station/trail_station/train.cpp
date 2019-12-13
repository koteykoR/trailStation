#include "train.h"

Train::Train()
{
    m_number = -1;
}

Train::Train(int number, QString departureDate, QString departureTime, QString arrivalDate, QString arrivalTime, QString soursePoint, QString destinationPoint)
{
    m_number = number;
    m_dateDeparture = departureDate;
    m_dateArrival = arrivalDate;
    m_timeArrival = arrivalTime;
    m_timeDeparture = departureTime;
    m_soursePoint = soursePoint;
    m_destinationPoint = destinationPoint;

}

Train::Train(const Train &obj)
{
    m_number = obj.m_number;
    m_dateDeparture = obj.m_dateDeparture;
    m_dateArrival = obj.m_dateArrival;
    m_timeArrival = obj.m_timeArrival;
    m_timeDeparture = obj.m_timeDeparture;
    m_soursePoint = obj.m_soursePoint;
    m_destinationPoint = obj.m_destinationPoint;
    m_listCarriage = obj.m_listCarriage;

}

Train &Train::operator=(const Train &obj)
{
    if (this != &obj) {
        m_number = obj.m_number;
        m_dateDeparture = obj.m_dateDeparture;
        m_dateArrival = obj.m_dateArrival;
        m_timeArrival = obj.m_timeArrival;
        m_timeDeparture = obj.m_timeDeparture;
        m_soursePoint = obj.m_soursePoint;
        m_destinationPoint = obj.m_destinationPoint;
        m_listCarriage = obj.m_listCarriage;
    }
    return *this;
}

int Train::number() const
{
    return m_number;
}

void Train::setNumber(int number)
{
    m_number = number;
}

void Train::addCarriage(const Carriage &carriage)
{
    m_listCarriage.push_back(carriage);
}

QList<Carriage> Train::listCarriage() const
{
    return m_listCarriage;
}

QString Train::dateDeparture() const
{
    return m_dateDeparture;
}

void Train::setDateDeparture(const QString &dateDeparture)
{
    m_dateDeparture = dateDeparture;
}

QString Train::timeDeparture() const
{
    return m_timeDeparture;
}

void Train::setTimeDeparture(const QString &timeDeparture)
{
    m_timeDeparture = timeDeparture;
}

QString Train::dateArrival() const
{
    return m_dateArrival;
}

void Train::setDateArrival(const QString &dateArrival)
{
    m_dateArrival = dateArrival;
}

QString Train::timeArrival() const
{
    return m_timeArrival;
}

void Train::setTimeArrival(const QString &timeArrival)
{
    m_timeArrival = timeArrival;
}

QString Train::soursePoint() const
{
    return m_soursePoint;
}

void Train::setSoursePoint(const QString &soursePoint)
{
    m_soursePoint = soursePoint;
}

QString Train::destinationPoint() const
{
    return m_destinationPoint;
}

void Train::setDestinationPoint(const QString &destinationPoint)
{
    m_destinationPoint = destinationPoint;
}

void Train::deleteAllCarriage()
{
    m_listCarriage.clear();
}

void Train::setListCarriage(const QList<Carriage> &listCarriage)
{
    m_listCarriage = listCarriage;
}

