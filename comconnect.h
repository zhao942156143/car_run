#ifndef COMCONNECT_H
#define COMCONNECT_H

#include <QObject>
#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>

class COMConnect : public QObject
{
    Q_OBJECT
public:
    explicit COMConnect(QObject *parent = 0);

signals:

public slots:


//define for Gps
public:
    QSerialPort com_serial;                    //串口实例
    QByteArray  com_rawdata;                   //用来阶段性获取数据的参数

    void COMOpen();
    void COMClose();
    //void ComGpsParse();                        //gps解析函数
};

#endif // COMCONNECT_H
