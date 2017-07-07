#include "mainwindow.h"
#include "sparse.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    sparse diag;
    diag.show();


    return a.exec();
}
