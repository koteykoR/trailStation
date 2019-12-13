#ifndef TRAINWAY_H
#define TRAINWAY_H

#include <QList>
#include "train.h"

// Класс Рейс
class TrainWay
{
public:
    TrainWay();
    TrainWay(const TrainWay &obj);
    TrainWay &operator=(const TrainWay &obj);

    // добавить поезд
    void addTrain(const Train &train);
    // ред. поезд
    void editTrain(const Train &obj);
    // удалить поезд
    void removeTrain(int numTrain);

    QList<Train> listTrain() const;
    void setList(const QList<Train> &list);

    int number() const;
    void setNumber(int number);

    friend QDataStream &operator<< (QDataStream &out, const TrainWay &rhs)
    {
        out << rhs.m_number << rhs.m_list;
        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, TrainWay &rhs)
    {
        in >> rhs.m_number >> rhs.m_list;
        return in;
    }

private:
    // номер
    int m_number;
    // список поездов
    QList<Train> m_list;
};

#endif // TRAINWAY_H
