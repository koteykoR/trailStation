#include "dialoglogin.h"
#include "ui_dialoglogin.h"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    m_login = "";
    m_password = "";
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setData()));
    // устанавливаем возможные введенные данные
    ui->lineEditLogin->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9]+"), this ));
    ui->lineEditPassword->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9]+"), this ));
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

QString DialogLogin::login() const
{
    return m_login;
}

void DialogLogin::setLogin(const QString &login)
{
    m_login = login;
}

QString DialogLogin::password() const
{
    return m_password;
}

void DialogLogin::setPassword(const QString &password)
{
    m_password = password;
}

void DialogLogin::setData()
{
    setLogin(ui->lineEditLogin->text());
    setPassword(ui->lineEditPassword->text());
    close();
    emit dataDone();
}
