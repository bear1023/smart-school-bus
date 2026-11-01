#include "MPU6050_Reg.h"
#include "iic.h"
#include <stdint.h>

#define MPU6050_ADDRESS     0xD0    // I2C从机地址（写模式）
#define MAX_RETRY           3       // 最大重试次数

// 写寄存器（带ACK检查和重试）
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data) {
    uint8_t retry = 0;
    do {
        I2C_Start();
        I2C_SendByte(MPU6050_ADDRESS);
        if (I2C_WaitAck() != 0) { I2C_Stop(); continue; } // 检查ACK
        I2C_SendByte(RegAddress);
        if (I2C_WaitAck() != 0) { I2C_Stop(); continue; }
        I2C_SendByte(Data);
        if (I2C_WaitAck() != 0) { I2C_Stop(); continue; }
        I2C_Stop();
        return; // 成功退出
    } while (retry++ < MAX_RETRY);
    // 失败处理（可添加错误标志）
}

// 读寄存器（带错误处理）
uint8_t MPU6050_ReadReg(uint8_t RegAddress) {
    uint8_t retry = 0, Data = 0xFF;
    do {
        I2C_Start();
        I2C_SendByte(MPU6050_ADDRESS);
        if (I2C_WaitAck() != 0) { I2C_Stop(); continue; }
        I2C_SendByte(RegAddress);
        if (I2C_WaitAck() != 0) { I2C_Stop(); continue; }
        I2C_Start(); // 重复起始条件
        I2C_SendByte(MPU6050_ADDRESS | 0x01);
        if (I2C_WaitAck() != 0) { I2C_Stop(); continue; }
        Data = I2C_ReadByte(0); // 读取数据并发送NACK
        I2C_Stop();
        return Data;
    } while (retry++ < MAX_RETRY);
    return 0xFF; // 返回错误值
}

// 初始化并验证设备ID
void MPU6050_Init(void) {
    I2C_Initia();
    // 检查WHO_AM_I寄存器
    if (MPU6050_ReadReg(MPU6050_WHO_AM_I) != 0x68) {
        // 处理错误（如LED闪烁）
        while(1); // 初始化失败，卡死或重启
    }
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01); // 唤醒设备
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18); // ±2000dps
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18); // ±16g
}

// 获取传感器数据（优化后的代码）
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ) {
    *AccX  = (MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H) << 8) | MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    *AccY  = (MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H) << 8) | MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    *AccZ  = (MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H) << 8) | MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    *GyroX = (MPU6050_ReadReg(MPU6050_GYRO_XOUT_H) << 8)  | MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    *GyroY = (MPU6050_ReadReg(MPU6050_GYRO_YOUT_H) << 8)  | MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    *GyroZ = (MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H) << 8)  | MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
}
