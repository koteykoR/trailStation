#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>

namespace Ui {
class DialogLogin;
}

// диалог для входа
class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = 0);
    ~DialogLogin();

    QString login() const;
    void setLogin(const QString &login);

    QString password() const;
    void setPassword(const QString &password);

signals:
    // если данные введены
    dataDone();

private slots:
    // установить данные логин и пароль
    void setData();

private:
    Ui::DialogLogin *ui;
    QString m_login;
    QString m_password;
};

#endif // DIALOGLOGIN_H
