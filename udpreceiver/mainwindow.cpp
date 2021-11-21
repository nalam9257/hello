#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#define IP "127.0.0.1"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket=new QUdpSocket(this);
    bool res=socket->bind(QHostAddress("127.0.0.1"),1000);
    if(res)
    {
        qDebug()<<"bind successfully"<<res;
    }
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
    QHostAddress addr("192.168.137.1");
    quint16 port =1000;

    socket->readDatagram(buffer.data(),buffer.size(),&addr,&port);
    qDebug()<<buffer.data();
    ui->listWidget->addItem(buffer);
    }

}






void MainWindow::on_pushButton_clicked()
{

       QString str=ui->lineEdit->text();
     QByteArray datagram=str.toUtf8();
        int  no_of_bytes=socket->writeDatagram(datagram,datagram.size(),QHostAddress(IP),5000);
        qDebug()<<"datagram successfully"<<no_of_bytes;
        ui->listWidget->addItem(str);

}

