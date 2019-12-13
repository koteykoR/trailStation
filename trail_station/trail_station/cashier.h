#ifndef CASHIER_H
#define CASHIER_H

#include <QObject>
#include "user.h"

// класс Кассир
class Cashier : public User
{
    Q_OBJECT
public:
    explicit Cashier(QObject *parent = 0);
    explicit Cashier(QString login, QString password);
    Cashier(const Cashier &obj);

signals:

public slots:
    // продать билет
    int sellTicket(int numTrainway, int numTrain, int countTicket);
    // вернуть билет
    int returnTicket(int numTrainway, int numTrain, int countTicket);
};

#endif // CASHIER_H
