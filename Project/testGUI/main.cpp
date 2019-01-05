#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    string serverIP("127.0.0.1");
    uint port = 2000;
    MainWindow w(nullptr, serverIP, port);
    w.show();

    return a.exec();
}
