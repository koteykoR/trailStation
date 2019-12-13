#ifndef CARRIAGE_H
#define CARRIAGE_H

#include <QDataStream>

// класс Вагон
class Carriage
{
public:
    // тип вагона
    enum Type { Undefined, SV, CompartmentCarriage, EconomCarriage };

    Carriage();
    Carriage(int countPlace, int countFreePlace, int costTicket, Type type);
    Carriage(const Carriage &obj);
    Carriage &operator=(const Carriage &obj);

    int countPlace() const;
    void setCountPlace(int countPlace);

    int countFreePlace() const;
    void setCountFreePlace(int countFreePlace);

    int costTicket() const;
    void setCostTicket(int costTicket);

    Type type() const;
    void setType(const Type &type);

    // перегрузка оператора вывода для записи в бин. файл
    friend QDataStream &operator<< (QDataStream &out, const Carriage &rhs)
    {
        out << (qint32)rhs.type() << rhs.countPlace() << rhs.countFreePlace() << rhs.costTicket();
        return out;
    }

    // перегрузка оператора ввода для записи в бин. файл
    friend QDataStream &operator>> (QDataStream &in, Carriage &rhs)
    {
        int type;
        in >> type >> rhs.m_countPlace >> rhs.m_countFreePlace >> rhs.m_costTicket;
        rhs.m_type = static_cast<Carriage::Type>(type);
        return in;
    }

private:
    Carriage::Type m_type;
    int m_countPlace;
    int m_countFreePlace;
    int m_costTicket;
};

#endif // CARRIAGE_H
