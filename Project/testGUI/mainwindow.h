#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpClientSocket.h"
#include <iostream>
#include <string>

using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, string networkAddress = "127.0.0.1", uint portNumber = 2000);
    ~MainWindow();
//    cs457::tcpClientSocket clientSocket;

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    cs457::tcpClientSocket clientSocket;
};

#endif // MAINWINDOW_H
