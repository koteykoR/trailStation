#ifndef TRAIN_H
#define TRAIN_H

#include <QString>
#include <QList>
#include <QDataStream>
#include "carriage.h"

// Класс поезд
class Train
{
public:
    Train();
    Train(int number, QString departureDate, QString departureTime, QString arrivalDate, QString arrivalTime, QString soursePoint, QString destinationPoint);
    Train(const Train &obj);
    Train &operator=(const Train &obj);

    int number() const;
    void setNumber(int number);

    // добавить вагон
    void addCarriage(const Carriage &carriage);

    // вернуть список вагонов
    QList<Carriage> listCarriage() const;

    QString dateDeparture() const;
    void setDateDeparture(const QString &dateDeparture);

    QString timeDeparture() const;
    void setTimeDeparture(const QString &timeDeparture);

    QString dateArrival() const;
    void setDateArrival(const QString &dateArrival);

    QString timeArrival() const;
    void setTimeArrival(const QString &timeArrival);

    QString soursePoint() const;
    void setSoursePoint(const QString &soursePoint);

    QString destinationPoint() const;
    void setDestinationPoint(const QString &destinationPoint);

    void deleteAllCarriage();

    void setListCarriage(const QList<Carriage> &listCarriage);

    // перегрузка оператора вывода для записи в бин. файлы
    friend QDataStream &operator<< (QDataStream &out, const Train &rhs)
    {
        out << (qint32)rhs.m_number << rhs.m_destinationPoint << rhs.m_dateDeparture << rhs.m_timeDeparture <<
               rhs.m_soursePoint << rhs.m_dateArrival << rhs.m_timeArrival << rhs.m_listCarriage;
        return out;
    }

    // перегрузка оператора ввода для записи в бин. файлы
    friend QDataStream &operator>> (QDataStream &in, Train &rhs)
    {
        in >>  rhs.m_number >> rhs.m_destinationPoint >> rhs.m_dateDeparture >> rhs.m_timeDeparture >>
               rhs.m_soursePoint >> rhs.m_dateArrival >> rhs.m_timeArrival >> rhs.m_listCarriage;
        return in;
    }

private:
    int m_number;
    QString m_dateDeparture;
    QString m_timeDeparture;
    QString m_dateArrival;
    QString m_timeArrival;
    QString m_soursePoint;
    QString m_destinationPoint;
    QList<Carriage> m_listCarriage;
};

#endif // TRAIN_H
