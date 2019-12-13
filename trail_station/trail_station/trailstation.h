#ifndef TRAILSTATION_H
#define TRAILSTATION_H

#include <QMainWindow>

class DialogLogin;

class User;
class UserStorage;
class Admin;
class AdminWidget;
class Cashier;
class CashierWidget;
class Passenger;
class PassengerWidget;

class TrainWayStorage;

namespace Ui {
class TrailStation;
}

class TrailStation : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrailStation(QWidget *parent = 0);
    ~TrailStation();

signals:
    void successOpenAccount(bool);

public slots:
    void openDialogLogin();
    void quitAccount();
    void save();
    void load();

private slots:
    void addAdmin();
    void addCashier();
    void addPassenger();
    void openUserAccount();

private:
    void saveUsersInfo();
    bool openUsersInfo();

    void saveTrainInfo();
    bool openTrainInfo();

    void saveTrainwayInfo();
    bool openTrainwayInfo();

    void saveAdminInfo();
    bool openAdminInfo();

    void saveCashierInfo();
    bool openCashierInfo();

private:
    Ui::TrailStation *ui;

    // хранит данные о рейсах
    TrainWayStorage *m_storage = nullptr;
    // хранит данные о пользователях
    UserStorage *m_userStorage = nullptr;
    // хранит указатель на объект Ввода логина и пароля
    DialogLogin *m_dialogLogin = nullptr;

    // админ
    Admin *m_admin = nullptr;
    // его виджет
    AdminWidget *m_adminWidget = nullptr;

    Cashier *m_cashier = nullptr;
    CashierWidget *m_cashierWidget = nullptr;

    Passenger *m_passenger = nullptr;
    PassengerWidget *m_passengerWidget = nullptr;
};

#endif // TRAILSTATION_H
