#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QString>
#include<string>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket =new QUdpSocket(this);
    socket->bind(QHostAddress("127.0.0.1"),5000);
    connect(socket,SIGNAL(readyRead()),this,SLOT(receivedata()));

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::receivedata()
{
    QByteArray buffer;
    bool data=socket->hasPendingDatagrams();
    if(data)
    {
     //socket->resize(datagram);
    int size= socket->pendingDatagramSize();
    buffer.resize(size);
    QHostAddress addr("127.0.0.1");
    quint16 port =5000;

    socket->readDatagram(buffer.data(),buffer.size(),&addr,&port);
    qDebug()<<buffer;
    ui->listWidget->addItem(buffer);
    }

}
void MainWindow::on_pushButton_clicked()
{

QString str=ui->lineEdit->text();
ui->listWidget->addItem(str);
QByteArray datagram=str.toUtf8();
int size=socket->writeDatagram(datagram,QHostAddress("127.0.0.1"),5000);
qDebug()<<size;
ui->lineEdit->clear();



}

