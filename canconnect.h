#ifndef CANCONNECT_H
#define CANCONNECT_H

#include <QObject>
#include "controlcan.h"

class CANConnect : public QObject
{
    Q_OBJECT

public:
    explicit CANConnect(QObject *parent = nullptr);
    void Init();
    void Close();

    void SendSteerCommend(int steer);
    void SendThottleCommend(int thottle);
    void SendBrakeCommend(int brake);
    void SendControlCommend(int steer , int throttle , int brake);
private:
    int  can_open();
    int  can_start(int channel_index);
    int  can_write(int channel,unsigned int id,unsigned char *buf,int len);
    int  can_read();
    int  ConvertToSigned(int data, int size);

private:
    VCI_BOARD_INFO pInfo;
};

#endif // CANCONNECT_H
