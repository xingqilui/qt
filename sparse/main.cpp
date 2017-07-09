#include "sparse.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sparse w;
    w.show();

    return a.exec();
}
