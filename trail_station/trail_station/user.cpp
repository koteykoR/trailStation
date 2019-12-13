#include "user.h"
#include <QVector>

User::User(QObject *parent) : QObject(parent)
{

}

User::User(QString login, QString password, Type type)
{
    m_login = login;
    m_password = password;
    m_type = type;
    m_storage = nullptr;
}

User::User(const User &obj)
{
    m_login = obj.m_login;
    m_password = obj.m_password;
    m_type = obj.m_type;
    m_storage = obj.m_storage;
}

User &User::operator=(const User &obj)
{
    if (this != &obj) {
        m_login = obj.m_login;
        m_password = obj.m_password;
        m_type = obj.m_type;
        m_storage = obj.m_storage;
    }
    return *this;
}

User::~User()
{

}

QString User::login() const
{
    return m_login;
}

void User::setLogin(const QString &login)
{
    m_login = login;
}

QString User::password() const
{
    return m_password;
}

void User::setPassword(const QString &password)
{
    m_password = password;
}

void User::connectToStorage(TrainWayStorage *storage)
{
    m_storage = storage;
}

User::Type User::getType() const
{
    return m_type;
}

void User::setType(const Type &type)
{
    m_type = type;
}

TrainWayStorage *User::getStorage() const
{
    return m_storage;
}

QVector<int> User::getVectorNumbersTrailway()
{
    QList<TrainWay> listWay = m_storage->listTrainway();
    QVector<int> numbers;
    for (QList<TrainWay>::iterator it = listWay.begin(); it != listWay.end(); ++it) {
        numbers.push_back((*it).number());
    }
    return numbers;
}

QVector<int> User::getVectorNumbersTrain(int numTrainWay)
{
    QList<TrainWay> listTrainway = m_storage->listTrainway();
    QVector<int> numbers;
    for (QList<TrainWay>::iterator it = listTrainway.begin(); it != listTrainway.end(); ++it) {
        if ((*it).number() == numTrainWay) {
            QList<Train> listTrain = (*it).listTrain();
            for (QList<Train>::iterator itTrain = listTrain.begin(); itTrain != listTrain.end(); ++itTrain) {
                numbers.push_back( (*itTrain).number());
            }
            break;
        }
    }

    return numbers;
}

TrainWay User::getTrainwayInfo(int numTrainway)
{
    QList<TrainWay> listTrainway = m_storage->listTrainway();
    for (QList<TrainWay>::iterator it = listTrainway.begin(); it != listTrainway.end(); ++it) {
        if ((*it).number() == numTrainway) {
            return (*it);
        }
    }
    return TrainWay();
}

Train User::getTrainInfo(int numTrainway, int numTrain)
{
    QList<TrainWay> listTrainway = m_storage->listTrainway();
    for (QList<TrainWay>::iterator it = listTrainway.begin(); it != listTrainway.end(); ++it) {
        if ((*it).number() == numTrainway) {
            QList<Train> listTrain = (*it).listTrain();
            for (QList<Train>::iterator itTrain = listTrain.begin(); itTrain != listTrain.end(); ++itTrain) {
                if ((*itTrain).number() == numTrain) {
                    return (*itTrain);
                }
            }
        }
    }
    return Train();
}
