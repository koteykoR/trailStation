#include "cashierwidget.h"
#include "ui_cashierwidget.h"
#include "cashier.h"

CashierWidget::CashierWidget(QWidget *parent, Cashier *cashier) :
    QWidget(parent),
    m_cashier(cashier),
    ui(new Ui::CashierWidget)
{
    ui->setupUi(this);

    ui->frameSellReturnTicket->setVisible(false);

    connect(ui->pushButtonDoOperation, SIGNAL(clicked(bool)), this, SLOT(genAction()));

    connect(ui->radioButtonReturnTicket, SIGNAL(clicked(bool)), this, SLOT(openFrameSellReturnTicket()));
    connect(ui->radioButtonSell, SIGNAL(clicked(bool)), this, SLOT(openFrameSellReturnTicket()));

    ui->lineEditNumTrainway->setValidator( new QIntValidator(0, 999999999, this) );
    ui->lineEditNumTrain->setValidator( new QIntValidator(0, 999999999, this) );
}

CashierWidget::~CashierWidget()
{
    delete ui;
}

void CashierWidget::genAction()
{
    if (ui->radioButtonSell->isChecked())
        sellTicket();
    else if (ui->radioButtonReturnTicket->isChecked())
        returnTicket();
}

void CashierWidget::openFrameSellReturnTicket()
{
    ui->frameSellReturnTicket->setVisible(true);
    ui->lineEditNumTrainway->clear();
    ui->spinBoxCountTicket->clear();
    ui->lineEditNumTrain->clear();
    ui->labelResult->setText(QString("Результат операции: "));
}

void CashierWidget::sellTicket()
{
    // получаем данные с полей
    int numTrainway = ui->lineEditNumTrainway->text().toInt();
    int numTrain = ui->lineEditNumTrain->text().toInt();
    int countTicket = ui->spinBoxCountTicket->value();
    // продаем билеты
    int resTicket = m_cashier->sellTicket(numTrainway, numTrain, countTicket);
    QString result;
    // анализ результата продажи
    if (resTicket == -1)
        result = QString("Не существует такого рейса");
    else if (resTicket == 0) {
        result = QString("Результат: продано %1 билетов на рейс %2").arg(countTicket).arg(numTrainway);
    } else {
        result = QString("Результат: продано %1 билетов на рейс %2. Еще %3 необходимых билетов в наличии нет").arg(countTicket - resTicket).arg(numTrainway).arg(resTicket);
    }

    ui->labelResult->setText(result);

}

void CashierWidget::returnTicket()
{
    int numTrainway = ui->lineEditNumTrainway->text().toInt();
    int numTrain = ui->lineEditNumTrain->text().toInt();
    int countTicket = ui->spinBoxCountTicket->value();
    int resTicket = m_cashier->returnTicket(numTrainway, numTrain, countTicket);

    QString result;
    // анализ результата возврата
    if (resTicket == -1)
        result = QString("Не существует такого рейса");
    else if (resTicket == 0) {
        result = QString("Результат: все билеты возвращены");
    } else {
        result = QString("Невозможно вернуть %1 билетов на рейс, так как их количество превышено!").arg(countTicket - resTicket);
    }

    ui->labelResult->setText(result);
}
