#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>

class Admin;
class User;
class UserStorage;

namespace Ui {
class AdminWidget;
}

class AdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWidget(QWidget *parent = 0, Admin *admin = nullptr, UserStorage *userStorage = nullptr);
    ~AdminWidget();
    void openDialog(const QVector<int> &numbers);

public slots:
    // выполнить действие над рейсами
    void genAction();
    // выполнить действие над пользователями
    void genActionForUser();
    // отобразить панель с рейсами
    void viewActionTrailwayPanel();
    // отобразить панель с пользователями
    void viewActionUserPanel();
    // заполнить комбо бокс номерами рейсов
    void fillComboBoxTrainNumber(QString numTrainwayStr);
    // заполнить полья рейса
    void fillDataFieldTrainway(QString numTrainStr);

private slots:
    // очистить выбор пользователя
    void clearAllFieldTrailwayAction();
    // очистить поля с входными значениями
    void clearInputData();
    // очистить поля пользователя
    void clearUserField();
    // очистить поля данных пользователя
    void clearUserFieldData();
    // заполнить список пользователей
    void fillComboBoxUserList(int index);

private:
    Ui::AdminWidget *ui;
    Admin *m_admin;
    UserStorage *m_userStorage;
};

#endif // ADMINWIDGET_H
