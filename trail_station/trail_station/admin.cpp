#include "admin.h"
//#include "trainwayinfodialog.h"
#include <list>
#include <QVector>

using namespace std;

Admin::Admin(QObject *parent)
{
}

Admin::Admin(QString login, QString password) : User(login, password, AdminType)
{

}

Admin::~Admin()
{
}

void Admin::addTrainway(int numTrainway, const Train &train)
{
    m_storage->addTrainWay(numTrainway, train);
}

void Admin::editTrainway(int numTrainway, const Train &train)
{
    m_storage->editTrainway(numTrainway, train);
}

void Admin::removeTrainway(int numTrainway, int numTrain)
{
    m_storage->removeTrainway(numTrainway, numTrain);
}
