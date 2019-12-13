#include "trainway.h"

TrainWay::TrainWay()
{
}

TrainWay::TrainWay(const TrainWay &obj)
{
    m_number = obj.m_number;
    m_list = obj.m_list;
}

TrainWay &TrainWay::operator=(const TrainWay &obj)
{
    if(this != &obj) {
        m_number = obj.m_number;
        m_list = obj.m_list;
    }
    return *this;
}

void TrainWay::addTrain(const Train &train)
{
    m_list.push_back(train);
}

void TrainWay::editTrain(const Train &obj)
{
    for (QList<Train>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if ( (*it).number() == obj.number() ) {
            (*it).setDateArrival( obj.dateArrival() );
            (*it).setTimeArrival( obj.timeArrival() );
            (*it).setTimeDeparture( obj.timeDeparture() );
            (*it).setDateDeparture( obj.dateDeparture() );
            (*it).setSoursePoint( obj.soursePoint());
            (*it).setDestinationPoint( obj.destinationPoint() );
            (*it).deleteAllCarriage();
            QList<Carriage> listCar = obj.listCarriage();
            for (QList<Carriage>::iterator itCar = listCar.begin(); itCar != listCar.end(); ++itCar) {
                (*it).addCarriage((*itCar));
            }

        }
    }
}

void TrainWay::removeTrain(int numTrain)
{
    for (QList<Train>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if ( (*it).number() == numTrain ) {
            m_list.erase(it);
            break;
        }
    }
}

QList<Train> TrainWay::listTrain() const
{
    return m_list;
}

void TrainWay::setList(const QList<Train> &list)
{
    m_list = list;
}

int TrainWay::number() const
{
    return m_number;
}

void TrainWay::setNumber(int number)
{
    m_number = number;
}

