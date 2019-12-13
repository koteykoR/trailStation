#ifndef TRAINWAYSTORAGE_H
#define TRAINWAYSTORAGE_H

#include "trainway.h"

// Класс для Хранения Рейсов
class TrainWayStorage
{
public:
    TrainWayStorage();
    // добавить поезд к определенном рейсе
    void addTrainWay(int numTrainway, const Train &train);
    // редактировать поезд в определенном рейсе
    void editTrainway(int numTrainway, const Train &train);
    // удалить поезд в определенном рейсе
    void removeTrainway(int numTrainway, int numTrain);
    QList<TrainWay> listTrainway();

private:
    QList<TrainWay> m_list;
};

#endif // TRAINWAYSTORAGE_H
