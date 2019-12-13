#include "passengerwidget.h"
#include "ui_passengerwidget.h"
#include "passenger.h"
#include "user.h"

PassengerWidget::PassengerWidget(QWidget *parent, Passenger *passenger) :
    QWidget(parent),
    m_passenger(passenger),
    ui(new Ui::PassengerWidget)
{
    ui->setupUi(this);
    connect(ui->pushButtonGetInfo, SIGNAL(clicked(bool)), this, SLOT(executeRequest()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(enabledCertainLineEdit(int)));
    ui->comboBox->setCurrentIndex(-1);

    ui->lineEditTrainway->setValidator( new QIntValidator(0, 999999999, this) );
    ui->lineEditNumTrain->setValidator( new QIntValidator(0, 999999999, this) );
}

PassengerWidget::~PassengerWidget()
{
    delete ui;
}

void PassengerWidget::routesOfTrainSpeceficTrainway(int numTrainway)
{
    QStringList result;
    // получаем список рейсов
    QList<TrainWay> listTrainway = m_passenger->getStorage()->listTrainway();
    for (auto itTrainway = listTrainway.begin(); itTrainway != listTrainway.end(); ++itTrainway) {
        // если нужный рейс
        if (itTrainway->number() == numTrainway) {
            // получаем список поездов
            auto listTrain = itTrainway->listTrain();
            for (auto itTrain = listTrain.begin(); itTrain != listTrain.end(); ++itTrain) {
                result.append(QString("Номер поезда: %1 ").arg(itTrain->number()));
                result.append(QString("Пункт отправления: %1 ").arg((itTrain->soursePoint())));
                result.append(QString("Пункт прибытия: %1 ").arg((itTrain->destinationPoint())));
                result.append("-------------------------------------------------\n");
            }
        }
    }
    if (result.isEmpty())
        ui->plainTextEdit->setPlainText("По данному рейсу нет информации");
    else {
        foreach (QString str, result) {
            ui->plainTextEdit->appendPlainText(str);
        }
    }
}

void PassengerWidget::trainOnSpecificRoute(QString source, QString destination)
{
    bool isEmpty = true;
    QStringList result;
    QList<TrainWay> listTrainway = m_passenger->getStorage()->listTrainway();
    for (auto itTrainway = listTrainway.begin(); itTrainway != listTrainway.end(); ++itTrainway) {
        auto listTrain = itTrainway->listTrain();
        for (auto itTrain = listTrain.begin(); itTrain != listTrain.end(); ++itTrain) {
            if ((itTrain->soursePoint()) == source &&
                    (itTrain->destinationPoint()) == destination) {
                result.clear();
                result.append(QString("Номер рейcа: %1").arg(itTrainway->number()));
                result.append(QString("Номер поезда: %1").arg(itTrain->number()));
                result.append(QString("Пункт отправления: %1").arg((itTrain->soursePoint())));
                result.append(QString("Дата отправления: %1").arg((itTrain->dateArrival())));
                result.append(QString("Время отправления: %1").arg((itTrain->timeArrival())));
                result.append(QString("Пункт прибытия: %1").arg((itTrain->destinationPoint())));
                result.append(QString("Дата прибытия: %1").arg((itTrain->dateDeparture())));
                result.append(QString("Время прибытия: %1").arg((itTrain->timeDeparture())));
                result.append(QString("Время прибытия: %1").arg((itTrain->timeDeparture())));
                result.append("-------------------------------------------------\n");

                foreach (QString str, result) {
                    ui->plainTextEdit->appendPlainText(str);
                }
                isEmpty = false;
            }
        }
    }
    if (isEmpty)
        ui->plainTextEdit->setPlainText("По данному маршруту нет поездов");

}

void PassengerWidget::infoAboutTrain(int numTrain)
{
    bool isEmpty = true;
    QStringList result;
    QList<TrainWay> listTrainway = m_passenger->getStorage()->listTrainway();
    for (auto itTrainway = listTrainway.begin(); itTrainway != listTrainway.end(); ++itTrainway) {
        auto listTrain = itTrainway->listTrain();
        for (auto itTrain = listTrain.begin(); itTrain != listTrain.end(); ++itTrain) {
            if (itTrain->number() == numTrain) {
                result.clear();
                result.append(QString("Номер рейcа: %1").arg(itTrainway->number()));
                result.append(QString("Номер поезда: %1").arg(itTrain->number()));
                result.append(QString("Пункт отправления: %1").arg((itTrain->soursePoint())));
                result.append(QString("Дата отправления: %1").arg((itTrain->dateArrival())));
                result.append(QString("Время отправления: %1").arg((itTrain->timeArrival())));
                result.append(QString("Пункт прибытия: %1").arg((itTrain->destinationPoint())));
                result.append(QString("Дата прибытия: %1").arg((itTrain->dateDeparture())));
                result.append(QString("Время прибытия: %1").arg((itTrain->timeDeparture())));
                result.append(QString("Время прибытия: %1").arg((itTrain->timeDeparture())));

                QList<Carriage> listCarriage = itTrain->listCarriage();

                int costSV = 0;
                int costEconom = 0;
                int costCompartment = 0;

                int countSV = 0;
                int countEconom = 0;
                int countCompartment = 0;

                int countPlaceSV = 0;
                int countPlaceEconom = 0;
                int countPlaceCompartment = 0;

                for (QList<Carriage>::iterator it = listCarriage.begin(); it != listCarriage.end(); ++it) {
                    switch ((*it).type()) {
                    case Carriage::SV:
                        ++countSV;
                        costSV = (*it).costTicket();
                        countPlaceSV = (*it).countFreePlace();
                        break;
                    case Carriage::EconomCarriage:
                        ++countEconom;
                        costEconom = (*it).costTicket();
                        countPlaceEconom = (*it).countFreePlace();
                        break;
                    case Carriage::CompartmentCarriage:
                        ++countCompartment;
                        costCompartment = (*it).costTicket();
                        countPlaceCompartment = (*it).countFreePlace();
                        break;
                    default:
                        break;
                    }
                }

                result.append(QString("Количество вагонов СВ: %1").arg(countSV));
                result.append(QString("Количество свободных мест СВ : %1").arg(countPlaceSV));
                result.append(QString("Стоимость места СВ : %1").arg(costSV));

                result.append(QString("Количество вагонов Купе: %1").arg(countCompartment));
                result.append(QString("Количество свободных мест Купе : %1").arg(countPlaceCompartment));
                result.append(QString("Стоимость места Купе : %1").arg(costCompartment));

                result.append(QString("Количество вагонов Плацкарт: %1").arg(countEconom));
                result.append(QString("Количество свободных мест Плацкарт : %1").arg(countPlaceEconom));
                result.append(QString("Стоимость места Плацкарт : %1").arg(costEconom));
                result.append("-------------------------------------------------\n");

                foreach (QString str, result) {
                    ui->plainTextEdit->appendPlainText(str);
                }
                isEmpty = false;
            }
        }
    }

    if (isEmpty)
        ui->plainTextEdit->setPlainText("По данному поезду нет информации");
}

void PassengerWidget::executeRequest()
{
    ui->plainTextEdit->clear();
    int indexCommand = ui->comboBox->currentIndex();
    // по индексу команды выполняем действие
    switch (indexCommand) {
    case 0:
        routesOfTrainSpeceficTrainway(ui->lineEditTrainway->text().toInt());
        break;
    case 1:
        trainOnSpecificRoute(ui->lineEditSource->text(), ui->lineEditDestination->text());
        break;
    case 2:
        infoAboutTrain(ui->lineEditNumTrain->text().toInt());
        break;
    default:
        break;
    }

    ui->comboBox->setCurrentIndex(-1);
    ui->lineEditDestination->clear();
    ui->lineEditNumTrain->clear();
    ui->lineEditSource->clear();
    ui->lineEditTrainway->clear();
}

void PassengerWidget::enabledCertainLineEdit(int index)
{
    // по опр. инексы какие-то поля делаем активными а какие-то наоборот
    switch (index) {
    case 0:
        ui->lineEditDestination->setDisabled(true);
        ui->lineEditNumTrain->setDisabled(true);
        ui->lineEditSource->setDisabled(true);
        ui->lineEditTrainway->setEnabled(true);
        break;
    case 1:
        ui->lineEditDestination->setEnabled(true);
        ui->lineEditNumTrain->setDisabled(true);
        ui->lineEditSource->setEnabled(true);
        ui->lineEditTrainway->setDisabled(true);
        break;
    case 2:
        ui->lineEditDestination->setDisabled(true);
        ui->lineEditNumTrain->setEnabled(true);
        ui->lineEditSource->setDisabled(true);
        ui->lineEditTrainway->setDisabled(true);
        break;
    default:
        break;
    }
}
