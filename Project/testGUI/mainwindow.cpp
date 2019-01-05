#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpClientSocket.h"
#include <iostream>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent, string serverIP, uint port) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    clientSocket.setAddress(serverIP);
    clientSocket.setPort(port);
    clientSocket.init();
    clientSocket.setSocketOptions();
    int val = clientSocket.connectSocket();
    ui->plainTextEdit_2->moveCursor (QTextCursor::End);
}

MainWindow::~MainWindow()
{
    string msgExit("EXIT");
    clientSocket.sendString(msgExit,false);
    clientSocket.closeSocket();
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    string sendmsg = ui->lineEdit_2->text().toStdString();
    ui->plainTextEdit_2->moveCursor (QTextCursor::End);
    string displaymsg = "user: " + sendmsg + "\n";
    ui->plainTextEdit_2->insertPlainText (QString::fromStdString(displaymsg));
    clientSocket.sendString(sendmsg,false);
    string rcvmsg;
    ssize_t v;
    tie(rcvmsg,v) =  clientSocket.recvString(4096,false);
    ui->plainTextEdit_2->moveCursor (QTextCursor::End);
    displaymsg = "server: " + rcvmsg + "\n";
    ui->plainTextEdit_2->insertPlainText (QString::fromStdString(displaymsg));
}
