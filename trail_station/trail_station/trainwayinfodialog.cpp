#include "trainwayinfodialog.h"
#include "ui_trainwayinfodialog.h"

TrainWayInfoDialog::TrainWayInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainWayInfoDialog)
{
    ui->setupUi(this);
    ui->frameInputData->setEnabled(false);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(genAction()));
    connect(ui->radioButtonAdd, SIGNAL(clicked(bool)), ui->FrameChooseTrainway, SLOT(setDisabled(bool)));
    connect(ui->radioButtonEdit, SIGNAL(clicked(bool)), ui->FrameChooseTrainway, SLOT(setEnabled(bool)));
    connect(ui->radioButtonRemove, SIGNAL(clicked(bool)), ui->FrameChooseTrainway, SLOT(setEnabled(bool)));

    connect(ui->radioButtonAdd, SIGNAL(clicked(bool)), ui->frameInputData, SLOT(setEnabled(bool)));
    connect(ui->radioButtonEdit, SIGNAL(clicked(bool)), ui->frameInputData, SLOT(setEnabled(bool)));
    connect(ui->radioButtonRemove, SIGNAL(clicked(bool)), ui->frameInputData, SLOT(setDisabled(bool)));

    ui->lineEditNumTrailway->setValidator( new QIntValidator(0, 999999999, this) );
}

TrainWayInfoDialog::~TrainWayInfoDialog()
{
    delete ui;
}

void TrainWayInfoDialog::openDialog(const QVector<int> &numbers)
{
    //clearAllField();
    addNumberTrain(numbers);
    this->open();
}

void TrainWayInfoDialog::addNumberTrain(const QVector<int> &numbers)
{
    for (int i = 0; i < numbers.size(); ++i) {
        ui->comboBoxNumTrailway->addItem(QString::number(numbers[i]));
    }
    //ui->comboBoxNumTrailway->setCurrentIndex(-1);
}

//void TrainWayInfoDialog::clearAllField()
//{
//    ui->radioButtonAdd->setChecked(false);
//    ui->radioButtonEdit->setChecked(false);
//    ui->radioButtonRemove->setChecked(false);
//    ui->comboBoxNumTrailway->clear();
//    ui->dateEditDeparture->setDate(QDate());
//    ui->timeEditDeparture->setDate(QDate());
//    ui->lineEditDestination->clear();
//    ui->lineEditSource->clear();
//    ui->lineEditNumTrailway->clear();
//    ui->spinBoxCostCompartment->clear();
//    ui->spinBoxCostSV->clear();
//    ui->spinBoxCostEconom->clear();
//    ui->spinBoxCountCompartment->clear();
//    ui->spinBoxCountSV->clear();
//    ui->spinBoxCountEconom->clear();
//    ui->spinBoxCountPlaceCompartment->clear();
//    ui->spinBoxCountPlaceSV->clear();
//    ui->spinBoxCountPlaceEconom->clear();
//}

void TrainWayInfoDialog::genAction()
{
    TrainWay m_trainway;
    Train train(ui->lineEditNumTrailway->text().toInt());

    for (int i = 0; i < ui->spinBoxCountSV->value(); ++i) {
        train.addCarriage(Carriage(ui->spinBoxCountPlaceSV->value(), ui->spinBoxCountPlaceSV->value(), ui->spinBoxCostSV->value(), Carriage::Type::SV));
    }

    for (int i = 0; i < ui->spinBoxCountCompartment->value(); ++i) {
        train.addCarriage(Carriage(ui->spinBoxCountPlaceCompartment->value(), ui->spinBoxCountPlaceCompartment->value(), ui->spinBoxCostCompartment->value(), Carriage::Type::CompartmentCarriage));
    }

    for (int i = 0; i < ui->spinBoxCountEconom->value(); ++i) {
        train.addCarriage(Carriage(ui->spinBoxCountPlaceEconom->value(), ui->spinBoxCountPlaceEconom->value(), ui->spinBoxCostEconom->value(), Carriage::Type::EconomCarriage));
    }

    m_trainway.setTrain(train);
    m_trainway.setDate( ui->dateEditDeparture->text().toStdString() );
    m_trainway.setDepartureTime( ui->timeEditDeparture->text().toStdString() );
    m_trainway.setSoursePoint( ui->lineEditSource->text().toStdString() );
    m_trainway.setDestinationPoint( ui->lineEditDestination->text().toStdString() );

    if (ui->radioButtonAdd->isChecked())
        emit addTrainway(m_trainway);
    else if (ui->radioButtonEdit->isChecked())
        emit editTrainway(m_trainway);
    else if (ui->radioButtonRemove->isChecked())
        emit removeTrainway(m_trainway);
}
