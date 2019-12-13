#include "trailstation.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrailStation w;
    w.show();
    w.openDialogLogin();
    return a.exec();
}
