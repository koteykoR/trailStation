#include "adminwidget.h"
#include "ui_adminwidget.h"
#include <QMessageBox>
#include "admin.h"
#include "trainway.h"
#include "userstorage.h"

AdminWidget::AdminWidget(QWidget *parent, Admin *admin, UserStorage *userStorage) :
    QWidget(parent),
    m_admin(admin),
    m_userStorage(userStorage),
    ui(new Ui::AdminWidget)
{
    ui->setupUi(this);
    ui->frameActionTralway->setVisible(false);
    ui->frameActionUser->setVisible(false);
    ui->lineEditDestination_3->setValidator(new QRegExpValidator( QRegExp("[А-Яа-я]+"), this ));
    ui->lineEditSource_3->setValidator(new QRegExpValidator( QRegExp("[А-Яа-я]+"), this ));

    // настраиваем видимость полей и действия в зависимости от выбора
    connect(ui->radioButtonActionUserRecord, SIGNAL(clicked(bool)), this, SLOT(viewActionUserPanel()));
    connect(ui->pushButtonAction, SIGNAL(clicked(bool)), this, SLOT(genActionForUser()));
    connect(ui->pushButtonDoActionTrailway, SIGNAL(clicked(bool)), this, SLOT(genAction()));
    connect(ui->comboBoxUserType, SIGNAL(currentIndexChanged(int)), this, SLOT(fillComboBoxUserList(int)));

    connect(ui->radioButtonRemove, SIGNAL(clicked(bool)), this, SLOT(clearUserFieldData()));
    connect(ui->radioButtonAdd, SIGNAL(clicked(bool)), this, SLOT(clearUserFieldData()));
    connect(ui->radioButtonEdit, SIGNAL(clicked(bool)), this, SLOT(clearUserFieldData()));

    connect(ui->radioButtonAdd_3, SIGNAL(clicked(bool)), ui->comboBoxNumTrailway_3, SLOT(setDisabled(bool)));
    connect(ui->radioButtonAdd_3, SIGNAL(clicked(bool)), ui->comboBoxNumTrain, SLOT(setDisabled(bool)));
    connect(ui->radioButtonEdit_3, SIGNAL(clicked(bool)), ui->comboBoxNumTrailway_3, SLOT(setEnabled(bool)));
    connect(ui->radioButtonEdit_3, SIGNAL(clicked(bool)), ui->comboBoxNumTrain, SLOT(setEnabled(bool)));
    connect(ui->radioButtonRemove_3, SIGNAL(clicked(bool)), ui->comboBoxNumTrailway_3, SLOT(setEnabled(bool)));
    connect(ui->radioButtonRemove_3, SIGNAL(clicked(bool)), ui->comboBoxNumTrain, SLOT(setEnabled(bool)));

    connect(ui->radioButtonAdd_3, SIGNAL(clicked(bool)), ui->frameInputData, SLOT(setEnabled(bool)));
    connect(ui->radioButtonEdit_3, SIGNAL(clicked(bool)), ui->frameInputData, SLOT(setEnabled(bool)));
    connect(ui->radioButtonRemove_3, SIGNAL(clicked(bool)), ui->frameInputData, SLOT(setDisabled(bool)));

    connect(ui->radioButtonEdit_3, SIGNAL(clicked(bool)), this, SLOT(clearInputData()));
    connect(ui->radioButtonRemove_3, SIGNAL(clicked(bool)), this, SLOT(clearInputData()));

    connect(ui->radioButtonActionTraiway, SIGNAL(clicked(bool)), this, SLOT(viewActionTrailwayPanel()));
    connect(ui->comboBoxNumTrailway_3, SIGNAL(currentTextChanged(QString)), this, SLOT(fillComboBoxTrainNumber(QString)));
    connect(ui->comboBoxNumTrain, SIGNAL(currentTextChanged(QString)), this, SLOT(fillDataFieldTrainway(QString)));

    // устанавливаем символы которые могут вводится в поля
    ui->lineEditNumTrailway_3->setValidator( new QIntValidator(0, 999999999, this) );
    ui->lineEditNumTrain->setValidator( new QIntValidator(0, 999999999, this) );
    ui->lineEditLogin->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9]+"), this ));
    ui->lineEditPassword->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9]+"), this ));
}

AdminWidget::~AdminWidget()
{
    delete ui;
}

void AdminWidget::genAction()
{

    if ((ui->dateEditDeparture_3->text().isEmpty() || ui->timeEditDeparture_->text().isEmpty()
            ||ui->dateEditArrival->text().isEmpty()||
            ui->timeEditArrival->text().isEmpty() ||
            ui->lineEditDestination_3->text().isEmpty()||
        ui->lineEditSource_3->text().isEmpty()||
        ui->lineEditNumTrailway_3->text().isEmpty()||
        ui->lineEditNumTrain->text().isEmpty())
            && (ui->radioButtonAdd_3->isChecked()||ui->radioButtonRemove_3->isChecked()) )
    {
        QMessageBox::warning(this, "Ввод данных", "Заполните все поля", QMessageBox::Ok);
    }
 else
    {
        // создаем поезд и заполняем его данные из полей ввода на форме
        Train train;
        train.setNumber(ui->lineEditNumTrain->text().toInt());
        train.setDateDeparture( ui->dateEditDeparture_3->text() );
        train.setTimeDeparture( ui->timeEditDeparture_->text() );
        train.setDateArrival( ui->dateEditArrival->text() );
        train.setTimeArrival( ui->timeEditArrival->text() );
        train.setSoursePoint( ui->lineEditSource_3->text() );
        train.setDestinationPoint( ui->lineEditDestination_3->text() );


        // добавляем вагоны
        for (int i = 0; i < ui->spinBoxCountSV_3->value(); ++i) {
            train.addCarriage(Carriage(ui->spinBoxCountPlaceSV_3->value(), ui->spinBoxCountPlaceSV_3->value(), ui->spinBoxCostSV_3->value(), Carriage::Type::SV));
        }

        for (int i = 0; i < ui->spinBoxCountCompartment_3->value(); ++i) {
            train.addCarriage(Carriage(ui->spinBoxCountPlaceCompartment_3->value(), ui->spinBoxCountPlaceCompartment_3->value(), ui->spinBoxCostCompartment_3->value(), Carriage::Type::CompartmentCarriage));
        }

        for (int i = 0; i < ui->spinBoxCountEconom_3->value(); ++i) {
            train.addCarriage(Carriage(ui->spinBoxCountPlaceEconom_3->value(), ui->spinBoxCountPlaceEconom_3->value(), ui->spinBoxCostEconom_3->value(), Carriage::Type::EconomCarriage));
        }

        // создаем рейс с опредленным номером и добавляем к нему поезд
        TrainWay trainway;
        trainway.setNumber(ui->lineEditNumTrailway_3->text().toInt());
        trainway.addTrain(train);
        // добавляем рейс
        if (ui->radioButtonAdd_3->isChecked()) {
            ui->comboBoxNumTrailway_3->addItem(QString::number((trainway.number())));
            ui->comboBoxNumTrain->addItem(QString::number((train.number())));
            ui->comboBoxNumTrailway_3->update();
            ui->comboBoxNumTrain->update();
            m_admin->addTrainway(trainway.number(), train);
        }
        // редактируем рейс
        else if (ui->radioButtonEdit_3->isChecked())
            m_admin->editTrainway(trainway.number(), train);
        // удаляем рейс
            if (ui->radioButtonRemove_3->isChecked())
                m_admin->removeTrainway(trainway.number(), train.number());
        // очищаем все пля
        clearAllFieldTrailwayAction();
    }


    }



void AdminWidget::genActionForUser()
{
    // получаем пользователя
    QString curTextCombo = ui->comboBoxAllUserThatType->currentText();
    // если удаляем его
    if (ui->radioButtonRemove->isChecked()) {
        if (m_admin->login() != curTextCombo)
            m_userStorage->removeUser(curTextCombo);
        else
            QMessageBox::critical(this, "Ошибка", "Невозможно удалить действующий аккаунт.\nВыйдите из аккаунта", QMessageBox::Ok);
    }

    // создаем пользователя
    User user(ui->lineEditLogin->text(), ui->lineEditPassword->text(), User::UndefinedType);
    // определяем тип пользователя
    if (ui->comboBoxUserType->currentIndex() == 0)
        user.setType(User::AdminType);
    else if (ui->comboBoxUserType->currentIndex() == 1)
        user.setType(User::CashierType);
    else if (ui->comboBoxUserType->currentIndex() == 2)
        user.setType(User::PassengerType);
    // подключаем пользователя к базе
    user.connectToStorage(m_admin->getStorage());

    // если мы добавляем пользоватедя
    if (ui->radioButtonAdd->isChecked()) {
        // проверяем что такого логина нет
        if (!m_userStorage->isHaveUser(user.login())) {
            ui->comboBoxAllUserThatType->addItem(user.login());
            ui->comboBoxAllUserThatType->update();
            m_userStorage->addUser(user);
        } else
            QMessageBox::critical(this, "Ошибка", "Аккаунт с таким именем уже есть.", QMessageBox::Ok);
    }
    // если редактируем пользователя
    else if (ui->radioButtonEdit->isChecked())
        m_userStorage->editUser(m_admin->login(), user);

    clearUserField();
}

void AdminWidget::fillComboBoxTrainNumber(QString numTrainwayStr)
{
    ui->comboBoxNumTrain->clear();
    QVector<int> numbersTrain = m_admin->getVectorNumbersTrain(numTrainwayStr.toInt());
    for (int i = 0; i < numbersTrain.size(); ++i) {
        ui->comboBoxNumTrain->addItem(QString::number(numbersTrain[i]));
    }
    ui->comboBoxNumTrain->setCurrentIndex(-1);
}

void AdminWidget::clearAllFieldTrailwayAction()
{
    ui->radioButtonAdd_3->setAutoExclusive(false);
    ui->radioButtonAdd_3->setChecked(false);
    ui->radioButtonAdd_3->setAutoExclusive(true);

    ui->radioButtonEdit_3->setAutoExclusive(false);
    ui->radioButtonEdit_3->setChecked(false);
    ui->radioButtonEdit_3->setAutoExclusive(true);

    ui->radioButtonRemove_3->setAutoExclusive(false);
    ui->radioButtonRemove_3->setChecked(false);
    ui->radioButtonRemove_3->setAutoExclusive(true);

    ui->comboBoxNumTrailway_3->clear();
    ui->comboBoxNumTrain->clear();
    ui->dateEditDeparture_3->setDate(QDate());
    ui->timeEditDeparture_->setDate(QDate());
    ui->dateEditArrival->setDate(QDate());
    ui->timeEditArrival->setDate(QDate());
    ui->lineEditDestination_3->clear();
    ui->lineEditSource_3->clear();
    ui->lineEditNumTrailway_3->clear();
    ui->lineEditNumTrain->clear();
    ui->spinBoxCostCompartment_3->clear();
    ui->spinBoxCostSV_3->clear();
    ui->spinBoxCostEconom_3->clear();
    ui->spinBoxCountCompartment_3->clear();
    ui->spinBoxCountSV_3->clear();
    ui->spinBoxCountEconom_3->clear();
    ui->spinBoxCountPlaceCompartment_3->clear();
    ui->spinBoxCountPlaceSV_3->clear();
    ui->spinBoxCountPlaceEconom_3->clear();

    ui->frameActionTralway->setVisible(false);

    ui->radioButtonActionTraiway->setAutoExclusive(false);
    ui->radioButtonActionTraiway->setChecked(false);
    ui->radioButtonActionTraiway->setAutoExclusive(true);
}

void AdminWidget::clearInputData()
{
    ui->dateEditDeparture_3->setDate(QDate());
    ui->timeEditDeparture_->setDate(QDate());
    ui->dateEditArrival->setDate(QDate());
    ui->timeEditArrival->setDate(QDate());
    ui->lineEditDestination_3->clear();
    ui->lineEditSource_3->clear();
    ui->lineEditNumTrailway_3->clear();
    ui->lineEditNumTrain->clear();
    ui->spinBoxCostCompartment_3->clear();
    ui->spinBoxCostSV_3->clear();
    ui->spinBoxCostEconom_3->clear();
    ui->spinBoxCountCompartment_3->clear();
    ui->spinBoxCountSV_3->clear();
    ui->spinBoxCountEconom_3->clear();
    ui->spinBoxCountPlaceCompartment_3->clear();
    ui->spinBoxCountPlaceSV_3->clear();
    ui->spinBoxCountPlaceEconom_3->clear();
}

void AdminWidget::clearUserField()
{
    ui->radioButtonAdd->setAutoExclusive(false);
    ui->radioButtonAdd->setChecked(false);
    ui->radioButtonAdd->setAutoExclusive(true);

    ui->radioButtonEdit->setAutoExclusive(false);
    ui->radioButtonEdit->setChecked(false);
    ui->radioButtonEdit->setAutoExclusive(true);

    ui->radioButtonRemove->setAutoExclusive(false);
    ui->radioButtonRemove->setChecked(false);
    ui->radioButtonRemove->setAutoExclusive(true);

    ui->lineEditLogin->clear();
    ui->lineEditPassword->clear();

    ui->comboBoxAllUserThatType->clear();
    ui->comboBoxUserType->setCurrentIndex(-1);
}

void AdminWidget::clearUserFieldData()
{
    if (ui->radioButtonAdd->isChecked())
        ui->comboBoxAllUserThatType->setEnabled(false);
    else
        ui->comboBoxAllUserThatType->setEnabled(true);

    if (ui->radioButtonRemove->isChecked()) {
        ui->lineEditLogin->setEnabled(false);
        ui->lineEditPassword->setEnabled(false);
    } else {
        ui->lineEditLogin->setEnabled(true);
        ui->lineEditPassword->setEnabled(true);
    }

    ui->lineEditLogin->clear();
    ui->lineEditPassword->clear();

    ui->comboBoxAllUserThatType->clear();
    ui->comboBoxUserType->setCurrentIndex(-1);
}

void AdminWidget::fillComboBoxUserList(int index)
{
    ui->comboBoxAllUserThatType->clear();
    if (m_userStorage) {
        QList<User> userStorage = m_userStorage->listUser();
        // по индексу смотрим какой тип пользователя выбран и заполняем комбо бокс с их именами
        switch (index) {
        case 0:
            for (QList<User>::iterator it = userStorage.begin(); it != userStorage.end(); ++it) {
                if ((*it).getType() == User::AdminType)
                    ui->comboBoxAllUserThatType->addItem((*it).login());
            }
            break;
        case 1:
            for (QList<User>::iterator it = userStorage.begin(); it != userStorage.end(); ++it) {
                if ((*it).getType() == User::CashierType)
                    ui->comboBoxAllUserThatType->addItem((*it).login());
            }
            break;
        case 2:
            for (QList<User>::iterator it = userStorage.begin(); it != userStorage.end(); ++it) {
                if ((*it).getType() == User::PassengerType)
                    ui->comboBoxAllUserThatType->addItem((*it).login());
            }
            break;
        default:
            break;
        }
        ui->comboBoxAllUserThatType->setCurrentIndex(-1);
    }
}

void AdminWidget::viewActionTrailwayPanel()
{
    ui->frameActionUser->setVisible(false);
    ui->frameActionTralway->setVisible(true);

    ui->comboBoxNumTrailway_3->clear();
    // получаем номера рейсов
    QVector<int> numbers = m_admin->getVectorNumbersTrailway();
    // заплняем возможные рейсы в комбо боксе
    for (int i = 0; i < numbers.size(); ++i) {
        ui->comboBoxNumTrailway_3->addItem(QString::number(numbers[i]));
    }
    ui->comboBoxNumTrailway_3->setCurrentIndex(-1);
}

void AdminWidget::viewActionUserPanel()
{
    ui->frameActionTralway->setVisible(false);
    ui->frameActionUser->setVisible(true);
    clearUserField();
    ui->comboBoxUserType->setCurrentIndex(-1);
}

void AdminWidget::fillDataFieldTrainway(QString numTrainStr)
{
    int numTrain = numTrainStr.toInt();
    // получаем объект поезд по номеру
    Train train = m_admin->getTrainInfo(ui->comboBoxNumTrailway_3->currentText().toInt(), numTrain);
    // список его вагонов
    QList<Carriage> listCarriage = train.listCarriage();

    int costSV = 0;
    int costEconom = 0;
    int costCompartment = 0;

    int countSV = 0;
    int countEconom = 0;
    int countCompartment = 0;

    int countPlaceSV = 0;
    int countPlaceEconom = 0;
    int countPlaceCompartment = 0;

    // заполняем инфу о вагонах (место , стоимость и т.д.)
    for (QList<Carriage>::iterator it = listCarriage.begin(); it != listCarriage.end(); ++it) {
        switch ((*it).type()) {
        case Carriage::SV:
            ++countSV;
            costSV = (*it).costTicket();
            countPlaceSV = (*it).countPlace();
            break;
        case Carriage::EconomCarriage:
            ++countEconom;
            costEconom = (*it).costTicket();
            countPlaceEconom = (*it).countPlace();
            break;
        case Carriage::CompartmentCarriage:
            ++countCompartment;
            costCompartment = (*it).costTicket();
            countPlaceCompartment = (*it).countPlace();
            break;
        default:
            break;
        }
    }

    // заполняем поля, беря инфу от поезда
    ui->lineEditNumTrain->setText(QString::number(train.number()));
    ui->lineEditNumTrailway_3->setText(ui->comboBoxNumTrailway_3->currentText());
    ui->lineEditSource_3->setText((train.soursePoint()));
    ui->lineEditDestination_3->setText((train.destinationPoint()));
    ui->dateEditDeparture_3->setDate(QDate::fromString((train.dateDeparture())));
    ui->timeEditDeparture_->setDate(QDate::fromString((train.timeDeparture())));
    ui->dateEditArrival->setDate(QDate::fromString((train.dateArrival())));
    ui->timeEditArrival->setDate(QDate::fromString((train.timeArrival())));

    ui->spinBoxCountSV_3->setValue(countSV);
    ui->spinBoxCostSV_3->setValue(costSV);
    ui->spinBoxCountPlaceSV_3->setValue(countPlaceSV);

    ui->spinBoxCountEconom_3->setValue(countEconom);
    ui->spinBoxCostEconom_3->setValue(costEconom);
    ui->spinBoxCountPlaceEconom_3->setValue(countPlaceEconom);

    ui->spinBoxCountCompartment_3->setValue(countCompartment);
    ui->spinBoxCostCompartment_3->setValue(costCompartment);
    ui->spinBoxCountPlaceCompartment_3->setValue(countPlaceCompartment);
}

