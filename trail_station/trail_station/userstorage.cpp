#include "userstorage.h"

UserStorage::UserStorage(QObject *parent) : QObject(parent)
{

}

UserStorage::~UserStorage()
{

}

void UserStorage::addUser(const User &user)
{
    m_list.push_back(user);
}

void UserStorage::editUser(QString login, const User &user)
{
    for (auto it = m_list.begin(); it != m_list.end(); ++it) {
        if ((*it).login() == login)
            (*it) = user;
    }
}

void UserStorage::removeUser(QString login)
{
    for (auto it = m_list.begin(); it != m_list.end(); ++it) {
        if ((*it).login() == login) {
            m_list.erase(it);
            break;
        }
    }
}

bool UserStorage::isHaveUser(QString login)
{
    for (auto it = m_list.begin(); it != m_list.end(); ++it) {
        if ((*it).login() == login)
           return true;
    }
    return false;
}

QList<User> UserStorage::listUser() const
{
    return m_list;
}
