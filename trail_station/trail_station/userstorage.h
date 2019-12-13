#ifndef USERSTORAGE_H
#define USERSTORAGE_H

#include <QObject>
#include "user.h"

// Класс Хранение Пользователей
class UserStorage : public QObject
{
    Q_OBJECT
public:
    explicit UserStorage(QObject *parent = nullptr);
    ~UserStorage();
    QList<User> listUser() const;

signals:

public slots:
    // добавить пользователя
    void addUser(const User &user);
    // ред. пользователя
    void editUser(QString login, const User &user);
    // удалитьь пользователя
    void removeUser(QString login);
    // есть ли такой пользователь с таким логином
    bool isHaveUser(QString login);

    friend QDataStream &operator<< (QDataStream &out, const UserStorage &rhs)
    {
        out << rhs.m_list;
        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, UserStorage &rhs)
    {
        in >> rhs.m_list;
        return in;
    }

private:
    QList<User> m_list;
};

#endif // USERSTORAGE_H
