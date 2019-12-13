#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include "trainwaystorage.h"

// Базовый класс для пользователей
class User : public QObject
{
    Q_OBJECT
public:
    // тип пользователя
    enum Type {UndefinedType, AdminType, CashierType, PassengerType};
    explicit User(QObject *parent = nullptr);
    User(QString login, QString password, Type type);
    User(const User& obj);
    User &operator=(const User &obj);
    ~User();

    QString login() const;
    void setLogin(const QString &login);

    QString password() const;
    void setPassword(const QString &password);

    QVector<int> getVectorNumbersTrailway();
    QVector<int> getVectorNumbersTrain(int numTrainWay);

    TrainWay getTrainwayInfo(int numTrainway);
    Train getTrainInfo(int numTrainway, int numTrain);

    // подключить к базе данных о рейсах
    void connectToStorage(TrainWayStorage *storage);

    Type getType() const;
    void setType(const Type &type);

    TrainWayStorage *getStorage() const;

    friend QDataStream &operator<< (QDataStream &out, const User &rhs)
    {
        out << rhs.m_login << rhs.m_password << (int)rhs.m_type;
        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, User &rhs)
    {
        int type;
        in >> rhs.m_login >> rhs.m_password >> type;
        rhs.m_type = static_cast<User::Type>(type);
        return in;
    }


signals:

public slots:

protected:
    // хранит базу рейсов
    TrainWayStorage *m_storage = nullptr;

private:
    QString m_login;
    QString m_password;
    Type m_type;
};

#endif // USER_H
