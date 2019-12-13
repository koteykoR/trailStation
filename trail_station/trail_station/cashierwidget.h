#ifndef CASHIERWIDGET_H
#define CASHIERWIDGET_H

#include <QWidget>

class Cashier;

namespace Ui {
class CashierWidget;
}

class CashierWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CashierWidget(QWidget *parent = 0, Cashier *cashier = nullptr);
    ~CashierWidget();

public slots:
    // вернуть или продать билеты при нажатии кнопки
    void genAction();
    void openFrameSellReturnTicket();

private:
    // продать
    void sellTicket();
    // вернуть
    void returnTicket();

private:
    Ui::CashierWidget *ui;
    Cashier *m_cashier = nullptr;
};

#endif // CASHIERWIDGET_H
