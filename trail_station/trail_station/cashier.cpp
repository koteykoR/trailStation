#include "cashier.h"

Cashier::Cashier(QObject *parent)
{

}

Cashier::Cashier(QString login, QString password) : User(login, password, Type::CashierType)
{

}

Cashier::Cashier(const Cashier &obj) : User(obj)
{

}

int Cashier::sellTicket(int numTrainway, int numTrain, int countTicket)
{
    // получаем бъект поезд
    Train train = getTrainInfo(numTrainway, numTrain);
    if (train.number() == -1)
        return -1;
    QList<Carriage> listCarriage = train.listCarriage();

    // проходим по его вагонам
    for (QList<Carriage>::iterator it = listCarriage.begin(); it != listCarriage.end(); ++it) {
        // если мест свободных недостаточно
        if (countTicket > (*it).countFreePlace()) {
            countTicket -= (*it).countFreePlace();
            (*it).setCountFreePlace(0);
        } else {  // если можно продать все билеты
            (*it).setCountFreePlace( (*it).countFreePlace() - countTicket );
            countTicket = 0;
            break;
        }
    }
    train.setListCarriage(listCarriage);

    // ред. инфу рейса с этим поездом
    m_storage->editTrainway(numTrainway, train);

    return countTicket;
}

int Cashier::returnTicket(int numTrainway, int numTrain, int countTicket)
{
    Train train = getTrainInfo(numTrainway, numTrain);
    if (train.number() == -1)
        return -1;
    QList<Carriage> listCarriage = train.listCarriage();

    for (QList<Carriage>::iterator it = listCarriage.begin(); it != listCarriage.end(); ++it) {
        // если билетов для возврата больше чем вообще мест в вагоне
        if (countTicket  + (*it).countFreePlace() > (*it).countPlace() ) {
            countTicket = countTicket - ((*it).countPlace() - (*it).countFreePlace());
            (*it).setCountFreePlace( (*it).countPlace() );
        } else { // если все норм
            (*it).setCountFreePlace( (*it).countFreePlace() + countTicket );
            countTicket = 0;
            break;
        }
    }
    train.setListCarriage(listCarriage);

    m_storage->editTrainway(numTrainway, train);
    return countTicket;
}
