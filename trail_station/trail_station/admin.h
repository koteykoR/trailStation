#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class AdminWidget;

class Admin : public User
{
    Q_OBJECT
public:
    explicit Admin(QObject *parent = 0);
    explicit Admin(QString login, QString password);

    ~Admin();

signals:

public slots:
    // добавить рейс
    void addTrainway(int numTrainway, const Train &train);
    // редактировать рейс
    void editTrainway(int numTrainway, const Train &train);
    // удалить рейс
    void removeTrainway(int numTrainway, int numTrain);
};

#endif // ADMIN_H
