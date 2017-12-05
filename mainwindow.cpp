#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPlainTextEdit>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) //查找可用的串口
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox->addItem(serial.portName());
            serial.close();
        }
    }


    fillPortsParameters();

}

MainWindow::~MainWindow()
{
    delete ui;
}


//读取接收的数据
void MainWindow::Read_Data()
{
    QByteArray data = serial->readAll();
    if(!data.isEmpty())
    {
        QString str = ui->textEdit->toPlainText();
        str+=tr(data);
        ui->textEdit->clear();
        ui->textEdit->append(str);
    }
    data.clear();
}

//清空数据
void MainWindow::on_clearButton_clicked()
{
    ui->textEdit->clear();
}

//设置ui显示
void MainWindow::fillPortsParameters()
{    
    ui->comboBox->addItem(tr("COM1"));
    ui->comboBox->addItem(tr("COM2"));
    ui->comboBox->addItem(tr("COM3"));
    ui->comboBox->addItem(tr("COM4"));
    ui->comboBox->addItem(tr("COM5"));
    ui->comboBox->addItem(tr("COM6"));
    ui->comboBox->addItem(tr("COM7"));
    ui->comboBox->addItem(tr("COM8"));
    ui->comboBox->addItem(tr("COM9"));
    ui->comboBox->addItem(tr("COM10"));

    ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudRateBox->addItem(tr("Custom"));

    ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsBox->setCurrentIndex(3);

    ui->parityBox->addItem(tr("0"), QSerialPort::NoParity);

    ui->stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    ui->stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
}

//打开串口
void MainWindow::on_openButton_clicked()
{
    if(ui->openButton->text()==tr("打开串口"))
    {
        serial = new QSerialPort;

        //设置串口名字
        serial->setPortName(ui->comboBox->currentText());
        //设置波特率
        serial->setBaudRate(ui->baudRateBox->currentText().toInt());
        //设置数据位
        switch (ui->dataBitsBox->currentIndex())
        {
        case 5:
            serial->setDataBits(QSerialPort::Data5);
            break;
        case 6:
            serial->setDataBits(QSerialPort::Data6);
            break;
        case 7:
            serial->setDataBits(QSerialPort::Data7);
            break;
        case 8:
            serial->setDataBits(QSerialPort::Data8);
            break;
        default:
            break;
        }
        //设置奇偶位
        switch(ui->parityBox->currentIndex())
        {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;
        default:
            break;
        }
        //设置停止位
        switch (ui->stopBitsBox->currentIndex())
        {
        case 1:
            serial->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            break;
        }
        //设置停止位
        serial->setFlowControl(QSerialPort::NoFlowControl);

        if(serial->open(QIODevice::ReadWrite))
        {
            ui->comboBox->setEnabled(false);
            ui->baudRateBox->setEnabled(false);
            ui->dataBitsBox->setEnabled(false);
            ui->parityBox->setEnabled(false);
            ui->stopBitsBox->setEnabled(false);
            ui->openButton->setText(tr("关闭串口"));
        }
        else
        {
            QMessageBox::critical(this,tr("错误"),serial->errorString());
        }
        connect(serial, &QSerialPort::readyRead, this, &MainWindow::Read_Data);
    }
    else
    {
        serial->clear();
        serial->close();
        serial->deleteLater();
        ui->comboBox->setEnabled(true);
        ui->baudRateBox->setEnabled(true);
        ui->dataBitsBox->setEnabled(true);
        ui->parityBox->setEnabled(true);
        ui->stopBitsBox->setEnabled(true);
        ui->openButton->setText(tr("打开串口"));
    }
}






