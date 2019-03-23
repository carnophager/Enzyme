#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "utility"
#include "enzyme.h"
#include <string.h>

//#include "C"
//#include "enzyme.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    std::cout << "ENZYME_RUN INITIATED\n" << std::endl;
    Enzyme e;


    return a.exec();
}
