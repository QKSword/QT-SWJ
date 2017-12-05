#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void putData(const QByteArray &data);

private slots:
    void on_clearButton_clicked();
    void on_openButton_clicked();
    void Read_Data();


private:
    void fillPortsParameters();
    void openSerialPort();


private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

};

#endif // MAINWINDOW_H
