#ifndef PASSENGERWIDGET_H
#define PASSENGERWIDGET_H

#include <QWidget>
#include <user.h>

class Passenger;

namespace Ui {
class PassengerWidget;
}

// Виджет для пассажира
class PassengerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PassengerWidget(QWidget *parent = 0, Passenger *passenge = nullptr);
    ~PassengerWidget();

public:
    // вывод инф. пути по которому следует рейс
    void routesOfTrainSpeceficTrainway(int numTrainway);
    // вывод инф. о поезде на определенном марщруте
    void trainOnSpecificRoute(QString source, QString destination);
    // вывод инф. о поезде по его номеру
    void infoAboutTrain(int numTrain);
public slots:
    // выполнить запрос
    void executeRequest();

private slots:
    // сделать активным опр. поле ввода
    void enabledCertainLineEdit(int index);

private:
    Ui::PassengerWidget *ui;
    Passenger *m_passenger;
};

#endif // PASSENGERWIDGET_H
