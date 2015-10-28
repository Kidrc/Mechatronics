#include "hodor_gyro.h"
#include <peripheral/i2c.h>
#include "BOARD.h"
#include "globalmacros.h"
#include "IO_Ports.h"
#include <xc.h>

void I2C_StartTransfer(void)
{
    while(!I2CBusIsIdle(GYRO_I2C_MODULE))
    {
        dbugprintf("WAITING FOR BUS\n");
        while(!IsTransmitEmpty());
    }
    
    if (I2CStart(GYRO_I2C_MODULE) != I2C_SUCCESS)
    {
        dbugprintf("COLLISION DETECTED\n");
        while(1);
    }
    while(!(I2CGetStatus(GYRO_I2C_MODULE)&I2C_START))
    {
        dbugprintf("WAITING FOR START\n");
        while(!IsTransmitEmpty());
    }
 /*   IdleI2C2();
    StartI2C2();
*/
}
void I2C_RestartTransfer(void)
{
    if (I2CRepeatStart(GYRO_I2C_MODULE) != I2C_SUCCESS)
    {
        dbugprintf("COLLISION DETECTED WHILE RESTARTING\n");
        while(1);
    }
    while(!(I2CGetStatus(GYRO_I2C_MODULE)&I2C_START))
    {
        dbugprintf("WAITING FOR RESTART\n");
        while(!IsTransmitEmpty());
    }
 /*   IdleI2C2();
    RestartI2C2();*/
}
void I2C_SendByte(uint8_t data)
{
    while(!I2CTransmitterIsReady(GYRO_I2C_MODULE))
    {
        dbugprintf("WAITING FOR TRANSMITTER READY\n");
        while(!IsTransmitEmpty());
    }
    if (I2CSendByte(GYRO_I2C_MODULE, data) != I2C_SUCCESS)
    {
        dbugprintf("COLLISION DETECTED WHILE SENDING\n");
        while(1);
    }
    while(!I2CTransmissionHasCompleted(GYRO_I2C_MODULE))
    {
        dbugprintf("WAITING FOR TRANSMISSION COMPLETE\n");
        while(!IsTransmitEmpty());
    }
    while(!I2CByteWasAcknowledged(GYRO_I2C_MODULE))
    {
        dbugprintf("WAITING FOR ACK\n");
    }
/*    IdleI2C2();
    MasterWriteI2C2(data);*/
}
BYTE I2C_RecvByte(BOOL ack)
{
    BYTE returndata;

    I2CReceiverEnable(GYRO_I2C_MODULE, TRUE);
    while(!I2CReceivedDataIsAvailable(GYRO_I2C_MODULE))
    {
        dbugprintf("WAITING FOR RECEIVED DATA AVAILABLE\n");
        while(!IsTransmitEmpty());
    }
    I2CAcknowledgeByte(GYRO_I2C_MODULE, ack);
    returndata = I2CGetByte(GYRO_I2C_MODULE);

    while(!I2CAcknowledgeHasCompleted(GYRO_I2C_MODULE))
    {
        dbugprintf("WAITING FOR ACK COMPLETE\n");
        while(!IsTransmitEmpty());
    }

/*    IdleI2C2();
    returndata = MasterReadI2C2();
    NotAckI2C2();*/

    return returndata;
}
void I2C_StopTransfer(void)
{
    I2CStop(GYRO_I2C_MODULE);

    while(!(I2CGetStatus(GYRO_I2C_MODULE)&I2C_STOP))
    {
        dbugprintf("WAITING FOR STOP\n");
        while(!IsTransmitEmpty());
    }
  
/*    IdleI2C2();
    StopI2C2();*/
}

void Gyro_Init(void)
{    
    I2CConfigure(GYRO_I2C_MODULE, 0);
    printf("I2C Frequency = %d\n",I2CSetFrequency(GYRO_I2C_MODULE, BOARD_GetPBClock(), GYRO_I2C_FREQUENCY));
//    I2CSetSlaveAddress(GYRO_I2C_MODULE, GYRO_I2C_ADDRESS, 0, I2C_USE_7BIT_ADDRESS);
    I2CEnable(GYRO_I2C_MODULE, TRUE);

    I2C_StartTransfer();
    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_WRITE);
    I2C_SendByte(GYRO_REG_PWR_MGMT1);
    I2C_SendByte(0x00);
    I2C_StopTransfer();
    
    I2C_StartTransfer();
    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_WRITE);
    I2C_SendByte(GYRO_REG_GYRO_CONFIG);
    I2C_SendByte(0x10);
    I2C_StopTransfer();

    I2C_StartTransfer();
    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_WRITE);
    I2C_SendByte(GYRO_REG_GYRO_CONFIG);
    I2C_RestartTransfer();
    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_READ);
    printf("CONFIG=%d\n", I2C_RecvByte(FALSE));
    I2C_StopTransfer();

    I2C_StartTransfer();
    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_WRITE);
    I2C_SendByte(GYRO_REG_WHOAMI);
    I2C_RestartTransfer();
    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_READ);
    printf("GYRO NUMBER=%d\n", I2C_RecvByte(FALSE));
    I2C_StopTransfer();

    I2C_StartTransfer();
    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_WRITE);
    I2C_SendByte(GYRO_REG_ZOUT_L);
    I2C_RestartTransfer();
    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_READ);
    printf("ZOUTL=%d\n", I2C_RecvByte(FALSE));
    I2C_StopTransfer();

}

int Gyro_ReadZ(void)
{
    int16_t data = 0;

    I2C_StartTransfer();

    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_WRITE);
    I2C_SendByte(GYRO_REG_ZOUT_H);

    I2C_RestartTransfer();

    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_READ);
    data = I2C_RecvByte(FALSE) << 8;

    I2C_StopTransfer();

    I2C_StartTransfer();

    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_WRITE);
    I2C_SendByte(GYRO_REG_ZOUT_L);

    I2C_RestartTransfer();

    I2C_SendByte((GYRO_I2C_ADDRESS<<1)|I2C_READ);
    data |= I2C_RecvByte(FALSE);

    I2C_StopTransfer();

    return data;
}

void Gyro_Test(void)
{
    char c = 0;

    printf("Gyro Test\n");
    while(c != 'q')
    {
        c = getchar();
        
        printf("GyroZ = %d\n", Gyro_ReadZ());
        while(!IsTransmitEmpty());
    }
}