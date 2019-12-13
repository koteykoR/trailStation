#ifndef TRAINWAYINFODIALOG_H
#define TRAINWAYINFODIALOG_H

#include <QDialog>
#include "trainway.h"

namespace Ui {
class TrainWayInfoDialog;
}

class TrainWayInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainWayInfoDialog(QWidget *parent = 0);
    ~TrainWayInfoDialog();
    void openDialog(const QVector<int> &numbers);

signals:
    void addTrainway(const TrainWay &obj);
    void editTrainway(const TrainWay &obj);
    void removeTrainway(const TrainWay &obj);

public slots:
    void genAction();

private:
    void addNumberTrain(const QVector<int> &numbers);
    //void clearAllField();

private:
    Ui::TrainWayInfoDialog *ui;
};

#endif // TRAINWAYINFODIALOG_H
