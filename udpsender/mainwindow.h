#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QUdpSocket>
#define IP "127.0.0.1"
#define PORT 5000
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QUdpSocket *socket;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void senderdata();
    void stopconnection(bool);

private:
    Ui::MainWindow *ui;
public slots:
    void receivedata();
private slots:
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
