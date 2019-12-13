#ifndef PASSENGER_H
#define PASSENGER_H

#include <QObject>
#include "user.h"

// класс пассажир
class Passenger : public User
{
    Q_OBJECT
public:
    explicit Passenger(QObject *parent = nullptr);
    explicit Passenger(QString login = "", QString password = "");
    Passenger(const Passenger &obj);

    bool guest() const;
    void setGuest(bool guest);

signals:

public slots:

private:
    bool m_guest;
};

#endif // PASSENGER_H
