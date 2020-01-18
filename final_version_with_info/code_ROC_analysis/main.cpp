#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowIcon(QIcon("C:/Users/user/Downloads/aryuna/sgmu.png"));

    return a.exec();
}
