#include "trainwaystorage.h"

using namespace std;

TrainWayStorage::TrainWayStorage()
{
}

void TrainWayStorage::addTrainWay(int numTrainway, const Train &train)
{
    bool isFind = false;
    for (QList<TrainWay>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if ( (*it).number() == numTrainway ) {
            (*it).addTrain(train);
            isFind = true;
            break;
        }
    }
    if (!isFind) {
        TrainWay newTrainway;
        newTrainway.setNumber(numTrainway);
        newTrainway.addTrain(train);
        m_list.push_back(newTrainway);
    }
}

void TrainWayStorage::editTrainway(int numTrainway, const Train &train)
{
    for (QList<TrainWay>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if ( (*it).number() == numTrainway ) {
            (*it).editTrain(train);
            break;
        }
    }
}

void TrainWayStorage::removeTrainway(int numTrainway, int numTrain)
{
    for (QList<TrainWay>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if ( (*it).number() == numTrainway ) {
            (*it).removeTrain(numTrain);
            break;
        }
    }
}

QList<TrainWay> TrainWayStorage::listTrainway()
{
    return m_list;
}
