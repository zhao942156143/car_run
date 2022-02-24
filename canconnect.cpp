#include <QtGui>
#include "canconnect.h"

CANConnect::CANConnect(QObject *parent) : QObject(parent)
{
}

void CANConnect::Init()
{
    can_open();
    can_start(0);       //暂时打开一个口子就够了
    //can_start(1);
}

void CANConnect::Close()
{
    VCI_CloseDevice(VCI_USBCAN2,0);
}

int CANConnect::can_open()
{
    if(VCI_OpenDevice(VCI_USBCAN2,0,0) == 1)
    {
        printf(">>open deivce success!\n");
    }
    else
    {
        printf(">>open deivce error!\n");
        return -1;
    }

    if(VCI_ReadBoardInfo(VCI_USBCAN2,0,&pInfo)==1)
    {
        printf(">>Get VCI_ReadBoardInfo success!\n");

        printf(" %08X", pInfo.hw_Version);printf("\n");
        printf(" %08X", pInfo.fw_Version);printf("\n");
        printf(" %08X", pInfo.dr_Version);printf("\n");
        printf(" %08X", pInfo.in_Version);printf("\n");
        printf(" %08X", pInfo.irq_Num);printf("\n");
        printf(" %08X", pInfo.can_Num);printf("\n");

        printf(">>Serial_Num:");
        for(int i = 0;i < 20;i++)
        {
            printf("%c",pInfo.str_Serial_Num[i]);
        }
        printf("\n");

        printf(">>hw_Type:");
        for(int i = 0;i < 10;i++)
        {
            printf("%c",pInfo.str_hw_Type[i]);
        }
        printf("\n");

        return 0;
        //m_pRealTimePlotWidget->setStatusSign(2);
    }else
    {
        printf(">>Get VCI_ReadBoardInfo error!\n");
        exit(1);
    }
}

int CANConnect::can_start(int channel_index)
{
    VCI_INIT_CONFIG config;

    config.AccCode  =0;
    config.AccMask  =0xffffffff;
    config.Filter   =1;
    config.Mode     =0;

    //use 500khz
    config.Timing0  = 0x00;   // BTR0   0014 -1M 0016-800K 001C-500K 011C-250K 031C-12K
    config.Timing1  = 0x1c;   // BTR1   041C-100K 091C-50K 181C-20K 311C-10K BFFF-5K

    if(VCI_InitCAN(VCI_USBCAN2,0,channel_index,&config)!=1)
    {
        printf("init CAN error\n");
        VCI_CloseDevice(VCI_USBCAN2,0);
        return 0;
    }

    if(VCI_StartCAN(VCI_USBCAN2,0,channel_index)!=1)
    {
        printf("Start CAN error\n");
        VCI_CloseDevice(VCI_USBCAN2,0);
        return 0;
    }

    printf("Start CAN ok\n");

    return 1;
}

int CANConnect::can_write(int channel,unsigned int id,unsigned char *buf,int len)
{
    unsigned long sndCnt;

    VCI_CAN_OBJ send[1];

    memset(send,0x00,sizeof(send));

    send[0].ID          = id;
    send[0].SendType    = 0;  // 0-正常发送;1-单次发送;2-自发自收;3-单次自发自收
    send[0].RemoteFlag  = 0;  // 0-数据帧； 1-远程帧
    send[0].ExternFlag  = 0;  // 0-标准帧； 1-扩展帧

    for(int i = 0;i<len;i++)
    {
        send[0].Data[i] = buf[i];
    }

    send[0].DataLen     = len; //DL

    sndCnt = VCI_Transmit(VCI_USBCAN2, 0, channel, send, 1);
    return sndCnt;
}


int CANConnect::ConvertToSigned(int data, int size)
{
    if ((data & (1 << (size - 1))) == 0)
        return data;
    return (data - (1 << size));
}

//本次实训暂时用不到
int CANConnect::can_read()
{
    return 1;
    VCI_CAN_OBJ rec[2500];//spec recommanded buffer length
    int reclen = 0;
    if(((reclen = VCI_Receive(VCI_USBCAN2,0,0,rec,2500,100))>0))
    {
        for(int j = 0;j<reclen;j++)
        {
            VCI_CAN_OBJ frame = rec[j];
            if(frame.ID == 0x101)
            {
                /*
                model = frame.Data[0];
                angle = frame.Data[1]*256 + frame.Data[2];
                if(angle>=32767) angle=angle-65536;
                brake = frame.Data[3];
                throtte = frame.Data[4];
                */
            }

            /**
            if(frame.ID == 0x02B0){
                if(frame.Data[3] == 0x07){
                    steer_d = frame.Data[1]*256 + frame.Data[0];
                    if(steer_d>=32767)steer_d=steer_d-65536;
                    steer_d = steer_d;
                    steer_d = -steer_d*0.1;
                    adm.SteerAngle = steer_d;
                    m_fRealSteer = steer_d;
                }
            }
            else if(frame.ID == 0x00DB){
                int speed_i =(int)(frame.Data[2] *256 + frame.Data[3]);
                speed_d = 0.0;
                if(speed_i < 1){
                    speed_d = 0;
                }else{
                    speed_d = speed_i * 4.0 / 250;
                }
               // adm.CarSpeed = speed_d;
            }
            else if(frame.ID == 0x0070)    {
                int    rate_i = (int)(frame.Data[0] *256 + frame.Data[1]);
                rate_d = (rate_i - 32768) * 0.12219;
                int    acc_x_i  = (int)(frame.Data[2] * 16 + (frame.Data[3] >> 4));
                acc_x_d  = (acc_x_i - 4028) * 0.002768;
                int    acc_y_i  = (int)((frame.Data[3] & 0x0f) *256 + frame.Data[4]);
                acc_y_d  = (acc_y_i - 4028) * 0.002768;
                int    acc_z_i  = (int)(frame.Data[5] * 16 + (frame.Data[6] >> 4));
                acc_z_d  = (acc_z_i - 4028) * 0.002768;
                adm.YawRate = rate_d;
            }
            else if(frame.ID == 0x22)    {
                brake_pedal = frame.Data[0];
            }
            else if(frame.ID == 0x30)    {
                m_fRealPressure = frame.Data[3];
            }
            **/
        }
    }
    //    if(((reclen = VCI_Receive(VCI_USBCAN2,0,1,rec,2500,100))>0))
    //    {
    //        for(int j = 0;j<reclen;j++)
    //        {
    //            SolveERadarObject(rec[j]);
    //        }
    //    }
}

void CANConnect::SendSteerCommend(int Steer)
{
    unsigned char buf[8] = {0};
    int steer = (int)(10 * (Steer));
    buf[0] = 0x48;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = (steer>>8) & 0xff;
    buf[4] = steer & 0xff;
    buf[5] = 0x00;
    buf[6] = 0x00;
    buf[7] = 0x00;
    can_write(0,0x00e2,buf,8);
}

void CANConnect::SendThottleCommend(int thottle)
{
    int tho = thottle+20;
    if(tho>120 )tho = 120;

    unsigned char buf[8] = {0};
    buf[0] = 0x28;
    buf[1] = (byte)(tho);
    buf[2] = 0;
    buf[3] = 0x00;
    buf[4] = 0x00;
    buf[5] = 0x00;
    buf[6] = 0x00;
    buf[7] = 0x00;
    can_write(0,0x00e2,buf,8);
}

void CANConnect::SendBrakeCommend(int brake)
{
    unsigned char buf[8] = {0};
    buf[0] = 0x88;
    buf[1] = 0;
    buf[2] = (byte)(brake);
    buf[3] = 0x00;
    buf[4] = 0x00;
    buf[5] = 0x00;
    buf[6] = 0x00;
    buf[7] = 0x00;
    can_write(0,0x00e2,buf,8);
}

void CANConnect::SendControlCommend(int steer , int throttle , int brake){
    unsigned char buf[8] = {0};
    int theSteer = (int)(10 * (steer));
    int theTho   = throttle + 20;
    int theBreak = brake;
    if(theTho > 100){
        theTho = 100;
    }

    buf[0] = 0xff;
    buf[1] = (byte)(theTho);
    buf[2] = (byte)(theBreak);
    buf[3] = (theSteer>>8) & 0xff;
    buf[4] = theSteer & 0xff;
    buf[5] = 0x00;
    buf[6] = 0x00;
    buf[7] = 0x00;
    can_write(0,0x00e2,buf,8);
}

