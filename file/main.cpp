#include "file.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    file w;
    w.show();

    return a.exec();
}
