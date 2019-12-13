#include "trailstation.h"
#include "ui_trailstation.h"
#include <QMessageBox>
#include "trainwaystorage.h"
#include "admin.h"
#include "adminwidget.h"
#include "cashier.h"
#include "cashierwidget.h"
#include "passenger.h"
#include "passengerwidget.h"
#include "dialoglogin.h"
#include "userstorage.h"

TrailStation::TrailStation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrailStation)
{
    ui->setupUi(this);
    m_storage = new TrainWayStorage();
    m_userStorage = new UserStorage();
    ui->actionQuitAccount->setDisabled(true);
    connect(ui->actionQuitApp, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->actionAddAdmin, SIGNAL(triggered(bool)), this, SLOT(openDialogLogin()));
    connect(ui->actionEnterToAccount, SIGNAL(triggered(bool)), this, SLOT(openDialogLogin()));
    connect(ui->actionQuitAccount, SIGNAL(triggered(bool)), this, SLOT(quitAccount()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(load()));
    connect(this, SIGNAL(successOpenAccount(bool)), ui->actionEnterToAccount, SLOT(setDisabled(bool)));
    connect(this, SIGNAL(successOpenAccount(bool)), ui->actionQuitAccount, SLOT(setEnabled(bool)));

    connect(ui->actionAddCashier, SIGNAL(triggered(bool)), this, SLOT(openDialogLogin()));
    connect(ui->actionAddPassanger, SIGNAL(triggered(bool)), this, SLOT(openDialogLogin()));
    Passenger *newPassenger = new Passenger("","");
    newPassenger->connectToStorage(m_storage);
    m_userStorage->addUser(*newPassenger);
    Admin *newAdmin = new Admin("Admin","Admin");
    // подключаем его к базе данных
    newAdmin->connectToStorage(m_storage);
    m_userStorage->addUser(*newAdmin);

}

TrailStation::~TrailStation()
{
    delete m_storage;
    delete m_userStorage;

    delete ui;
}

void TrailStation::openDialogLogin()
{
    if(!m_dialogLogin)
        delete m_dialogLogin;

    // создаем объект диалог ввода логина и пароля
    m_dialogLogin = new DialogLogin();
    QObject *obj = sender();
    // определяем какой подпункт меню нажат и выполняем соответствующее действие
    if (obj == ui->actionAddAdmin) {
        m_dialogLogin->setWindowTitle("Добавить администратора");
        connect(m_dialogLogin, SIGNAL(dataDone()), this, SLOT(addAdmin()));
    } else if (obj == ui->actionAddCashier) {
        m_dialogLogin->setWindowTitle("Добавить касссира");
        connect(m_dialogLogin, SIGNAL(dataDone()), this, SLOT(addCashier()));
    } else if (obj == ui->actionAddPassanger) {
        m_dialogLogin->setWindowTitle("Добавить пассажира");
        connect(m_dialogLogin, SIGNAL(dataDone()), this, SLOT(addPassenger()));
    } else  {
        m_dialogLogin->setWindowTitle("Вход в аккаунт");
        connect(m_dialogLogin, SIGNAL(dataDone()), this, SLOT(openUserAccount()));
    }
    // выводим окно диалога
    m_dialogLogin->show();
}

// выходим из аккаунта
void TrailStation::quitAccount()
{
    // выбираем какой виджет активен и закрываем его и удаляем объект
    if (m_adminWidget) {
        m_adminWidget->close();
        delete m_adminWidget;
        delete m_admin;
        m_adminWidget = nullptr;
        m_admin = nullptr;
    } else if (m_cashierWidget) {
        m_cashierWidget->close();
        delete m_cashierWidget;
        delete m_cashier;
        m_cashierWidget = nullptr;
        m_cashier = nullptr;
    } else if (m_passengerWidget) {
        m_passengerWidget->close();
        delete m_passengerWidget;
        delete m_passenger;
        m_passengerWidget = nullptr;
        m_passenger = nullptr;
    }
    // делаем активным вход в аккаунт
    ui->actionEnterToAccount->setEnabled(true);
    // делаем неактивным выход из аккаунта
    ui->actionQuitAccount->setEnabled(false);
}

// сохраняем в бин. файлы
void TrailStation::save()
{
    saveUsersInfo();
    saveTrainInfo();
    saveTrainwayInfo();
    saveAdminInfo();
    saveCashierInfo();
}

// загружаем из бин. файлы
void TrailStation::load()
{
    // если данные о пользователях успешно загружены
    bool usersLoadDone = openUsersInfo();
    // если данные о рейсах успешно загружены
    bool trainwayLoadDone = openTrainwayInfo();
    if ( usersLoadDone && trainwayLoadDone)
        QMessageBox::information(this, "Загрузить", "база была успешно загружена", QMessageBox::Ok);
}

// сохраняем пользователей
void TrailStation::saveUsersInfo()
{
    QFile fileUsers("users.dat");
    fileUsers.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream stream(&fileUsers);
    auto list = m_userStorage->listUser();
    for(auto it = list.begin(); it != list.end(); ++it) {
        stream << *it;
    }
    fileUsers.close();
    QMessageBox::information(this, "Сохранить", "база была успешно сохранена", QMessageBox::Ok);
}

// загружаем пользователей
bool TrailStation::openUsersInfo()
{
    bool isSuccess = false;
    QFile fileUsers("users.dat");
    fileUsers.open(QIODevice::ReadOnly);
    if (fileUsers.size() != 0) {
        QDataStream stream(&fileUsers);
        while (!stream.atEnd()) {
            User user;
            stream >> user;
            user.connectToStorage(m_storage);
            m_userStorage->addUser(user);
        }
        isSuccess = true;
    } else
        QMessageBox::critical(this, "Открыть файл", "Файл ""Информация о пользователях"" пустой", QMessageBox::Ok);
    fileUsers.close();
    return isSuccess;
}

// сохраняем инфу о поездах
void TrailStation::saveTrainInfo()
{
    QFile fileUsers("train.dat");
    fileUsers.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream stream(&fileUsers);
    auto listTrainway = m_storage->listTrainway();
    for(auto it = listTrainway.begin(); it != listTrainway.end(); ++it) {
        auto listTrain = (*it).listTrain();
        for(auto itTrain = listTrain.begin(); itTrain != listTrain.end(); ++itTrain) {
            stream << (*itTrain);
        }
    }
    fileUsers.close();
}

// загружаем инфу о поездах
bool TrailStation::openTrainInfo()
{
    bool isSuccess = false;
    QFile fileUsers("train.dat");
    fileUsers.open(QIODevice::ReadOnly);
    if (fileUsers.size() != 0) {
        QDataStream stream(&fileUsers);
        QList<Train> listTrain;
        while (!stream.atEnd()) {
            Train train;
            stream >> train;
            listTrain.push_back(train);
        }

        isSuccess = true;
    } else
        QMessageBox::critical(this, "Открыть файл", "Файл ""Информация о поездах"" пустой", QMessageBox::Ok);

    fileUsers.close();

    return isSuccess;
}

// сохраняем инфу о рейсах
void TrailStation::saveTrainwayInfo()
{
    QFile fileUsers("trainway.dat");
    fileUsers.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream stream(&fileUsers);
    auto listTrainway = m_storage->listTrainway();
    for(auto it = listTrainway.begin(); it != listTrainway.end(); ++it) {
        stream << (*it);
    }
    fileUsers.close();
}

// загружаем инфу о рейсах
bool TrailStation::openTrainwayInfo()
{
    bool isSuccess = false;
    QFile fileUsers("trainway.dat");
    fileUsers.open(QIODevice::ReadOnly);
    if (fileUsers.size() != 0) {
        QDataStream stream(&fileUsers);
        while (!stream.atEnd()) {
            TrainWay trainway;
            stream >> trainway;
            auto list = trainway.listTrain();
            for (auto it = list.begin(); it != list.end(); ++it) {
                m_storage->addTrainWay(trainway.number(), (*it));
            }
        }
        isSuccess = true;
    } else
        QMessageBox::critical(this, "Открыть файл", "Файл ""Информация о маршрутах"" пустой", QMessageBox::Ok);

    fileUsers.close();

    return isSuccess;
}

// сохраняем инфу о админах
void TrailStation::saveAdminInfo()
{
    QFile fileUsers("admin.dat");
    fileUsers.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream stream(&fileUsers);
    auto list = m_userStorage->listUser();
    for(auto it = list.begin(); it != list.end(); ++it) {
        if ( (*it).getType() == User::Type::AdminType )
            stream << *it;
    }
    fileUsers.close();
}

// загружаем инфу об админах
bool TrailStation::openAdminInfo()
{
    bool isSuccess = false;
    QFile fileUsers("admin.dat");
    fileUsers.open(QIODevice::ReadOnly);
    if (fileUsers.size() != 0) {
        QDataStream stream(&fileUsers);
        while (!stream.atEnd()) {
                User user;
                stream >> user;
                if ( user.getType() == User::Type::AdminType ) {
                    user.connectToStorage(m_storage);
                    m_userStorage->addUser(user);
                }
        }
        isSuccess = true;
    } else
        QMessageBox::critical(this, "Открыть файл", "Файл ""Информация об аминистраторах"" пустой", QMessageBox::Ok);
    fileUsers.close();
    return isSuccess;
}

// сохраняем инфу о кассирах
void TrailStation::saveCashierInfo()
{
    QFile fileUsers("cashier.dat");
    fileUsers.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream stream(&fileUsers);
    auto list = m_userStorage->listUser();
    for(auto it = list.begin(); it != list.end(); ++it) {
        if ( (*it).getType() == User::Type::CashierType )
            stream << *it;
    }
    fileUsers.close();
}

// загружаем инфу о кассирах
bool TrailStation::openCashierInfo()
{
    bool isSuccess = false;
    QFile fileUsers("cashier.dat");
    fileUsers.open(QIODevice::ReadOnly);
    if (fileUsers.size() != 0) {
        QDataStream stream(&fileUsers);
        while (!stream.atEnd()) {
                User user;
                stream >> user;
                if ( user.getType() == User::Type::CashierType ) {
                    user.connectToStorage(m_storage);
                    m_userStorage->addUser(user);
                }
        }
        isSuccess = true;
    } else
        QMessageBox::critical(this, "Открыть файл", "Файл ""Информация о кассирах"" пустой", QMessageBox::Ok);
    fileUsers.close();

    return isSuccess;
}

// добавить админа
void TrailStation::addAdmin()
{
    // если нет админа с таким именем
    if (!m_userStorage->isHaveUser(m_dialogLogin->login())) {
        // создаем объект Админ
        Admin *newAdmin = new Admin(m_dialogLogin->login(), m_dialogLogin->password());
        // подключаем его к базе данных
        newAdmin->connectToStorage(m_storage);
        m_userStorage->addUser(*newAdmin);
    } else
        QMessageBox::critical(this, "Ошибка", "Админ с таким именем уже есть.", QMessageBox::Ok);
}

void TrailStation::addCashier()
{
    if (!m_userStorage->isHaveUser(m_dialogLogin->login())) {
        Cashier *newCashier = new Cashier(m_dialogLogin->login(), m_dialogLogin->password());
        newCashier->connectToStorage(m_storage);
        m_userStorage->addUser(*newCashier);
    } else
        QMessageBox::critical(this, "Ошибка", "Кассир с таким именем уже есть.", QMessageBox::Ok);
}

void TrailStation::addPassenger()
{
    if (!m_userStorage->isHaveUser(m_dialogLogin->login())) {
        Passenger *newPassenger = new Passenger(m_dialogLogin->login(), m_dialogLogin->password());
        newPassenger->connectToStorage(m_storage);
        m_userStorage->addUser(*newPassenger);
    } else
        QMessageBox::critical(this, "Ошибка", "Пассажир с таким именем уже есть.", QMessageBox::Ok);
}

// открываем аккаунт пользователя
void TrailStation::openUserAccount()
{
    bool isSuccess = false;
    // получаем список пользователей
    auto listUser = m_userStorage->listUser();
    for (auto it = listUser.begin(); it != listUser.end(); ++it) {
        // если пароль и логин совпали
        if ( ((*it).password() == m_dialogLogin->password()) && ((*it).login() == m_dialogLogin->login()) ) {
            // если админ
            if ((*it).getType() == User::AdminType) {
                // если активен предыдущий админ
                if (m_admin)
                    delete m_admin;
                // создаем новый объект
                m_admin = new Admin((*it).login(), (*it).password());
                m_admin->connectToStorage(m_storage);
                if (m_adminWidget)
                    delete m_adminWidget;
                // создаем объект виджет для админа
                m_adminWidget = new AdminWidget(this, m_admin, m_userStorage);
                // устанавливаем его в главную форму
                setCentralWidget(m_adminWidget);
                isSuccess = true;
                break;
            } else if ((*it).getType() == User::CashierType) {
                if ( ((*it).password() == m_dialogLogin->password()) && ((*it).login() == m_dialogLogin->login()) )
                    if (m_cashier)
                        delete m_cashier;
                    m_cashier = new Cashier((*it).login(), (*it).password());
                    m_cashier->connectToStorage(m_storage);
                    if (m_cashierWidget)
                        delete m_cashierWidget;
                    m_cashierWidget = new CashierWidget(this, m_cashier);
                    setCentralWidget(m_cashierWidget);

                    isSuccess = true;
                    break;
            } else if ((*it).getType() == User::PassengerType) {
                if ( ((*it).password() == m_dialogLogin->password()) && ((*it).login() == m_dialogLogin->login()) )
                    if (m_passenger)
                        delete m_passenger;
                    m_passenger = new Passenger((*it).login(), (*it).password());
                    m_passenger->connectToStorage(m_storage);
                    if (m_passengerWidget)
                        delete m_passengerWidget;
                    m_passengerWidget = new PassengerWidget(this, m_passenger);
                    setCentralWidget(m_passengerWidget);

                    isSuccess = true;
                    break;
            }
        }
    }
    if(!isSuccess)
        QMessageBox::warning(this, "Логин", "Не существует данного аккаунта", QMessageBox::Ok);
    emit successOpenAccount(isSuccess);
}
