#include "comconnect.h"

COMConnect::COMConnect(QObject *parent) : QObject(parent)
{

}

void COMConnect::COMOpen()
{
    //QSerialPortInfo info;
    com_serial.close();
    com_serial.setPortName("COM1");
    com_serial.setBaudRate(QSerialPort::Baud115200);
    com_serial.setParity(QSerialPort::NoParity);
    com_serial.setDataBits(QSerialPort::Data8);
    com_serial.setStopBits(QSerialPort::OneStop);
    com_serial.setFlowControl(QSerialPort::NoFlowControl);

    com_serial.open(QIODevice::ReadWrite);
    com_serial.clearError();
    com_serial.clear();
}

void COMConnect::COMClose()
{
    com_serial.close();
}
