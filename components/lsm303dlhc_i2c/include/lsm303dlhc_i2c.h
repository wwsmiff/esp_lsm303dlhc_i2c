#ifndef LMS303DLHC_I2C_H_
#define LMS303DLHC_I2C_H_

#include "esp_err.h"
#include <driver/i2c_master.h>
#include <stdio.h>

enum lsm303dlhc_dev_addr_t {
  LMS303DLHC_ACC_DEV_ADDR = 0x19,
  LMS303DLHC_MAG_DEV_ADDR = 0x1c
};

enum lsm303dlhc_acc_reg_t {
  LMS303DLHC_ACC_REG_CTRL1 = 0x20,
  LMS303DLHC_ACC_REG_CTRL2,
  LMS303DLHC_ACC_REG_CTRL3,
  LMS303DLHC_ACC_REG_CTRL4,
  LMS303DLHC_ACC_REG_CTRL5,
  LMS303DLHC_ACC_REG_CTRL6,
  LMS303DLHC_ACC_REG_REFERENCE,
  LMS303DLHC_ACC_REG_STATUS,
  LMS303DLHC_ACC_REG_OUT_X_L,
  LMS303DLHC_ACC_REG_OUT_X_H,
  LMS303DLHC_ACC_REG_OUT_Y_L,
  LMS303DLHC_ACC_REG_OUT_Y_H,
  LMS303DLHC_ACC_REG_OUT_Z_L,
  LMS303DLHC_ACC_REG_OUT_Z_H,
  LMS303DLHC_ACC_REG_FIFO_CTRL_REG,
  LMS303DLHC_ACC_REG_FIFO_SRC_REG,
  LMS303DLHC_ACC_REG_INT1_CFG,
  LMS303DLHC_ACC_REG_INT1_SRC,
  LMS303DLHC_ACC_REG_INT1_THS,
  LMS303DLHC_ACC_REG_INT1_DURATION,
  LMS303DLHC_ACC_REG_INT2_CFG,
  LMS303DLHC_ACC_REG_INT2_SRC,
  LMS303DLHC_ACC_REG_INT2_THS,
  LMS303DLHC_ACC_REG_INT2_DURATION,
  LMS303DLHC_ACC_REG_CLICK_CFG,
  LMS303DLHC_ACC_REG_CLICK_SRC,
  LMS303DLHC_ACC_REG_CLICK_THS,
  LMS303DLHC_ACC_REG_TIME_LIMIT,
  LMS303DLHC_ACC_REG_TIME_LATENCY,
  LMS303DLHC_ACC_REG_TIME_WINDOW,
};

enum lsm303dlhc_mag_reg_t {
  LMS303DLHC_MAG_REG_CRA = 0x00,
  LMS303DLHC_MAG_REG_CRB,
  LMS303DLHC_MAG_REG_MR,
  LMS303DLHC_MAG_REG_OUT_X_H,
  LMS303DLHC_MAG_REG_OUT_X_L,
  LMS303DLHC_MAG_REG_OUT_Y_H,
  LMS303DLHC_MAG_REG_OUT_Y_L,
  LMS303DLHC_MAG_REG_OUT_Z_H,
  LMS303DLHC_MAG_REG_OUT_Z_L,
  LMS303DLHC_MAG_REG_SR,
  LMS303DLHC_MAG_REG_IRA,
  LMS303DLHC_MAG_REG_IRB,
  LMS303DLHC_MAG_REG_IRC,
  LMS303DLHC_MAG_REG_TEMP_OUT_H = 0x31,
  LMS303DLHC_MAG_REG_TEMP_OUT_L = 0x32,
};

enum lsm303dlhc_acc_range {
  LMS303DLHC_ACC_RANGE_2G,
  LMS303DLHC_ACC_RANGE_4G,
  LMS303DLHC_ACC_RANGE_8G,
  LMS303DLHC_ACC_RANGE_16G,
};

enum lsm303dlhc_mag_range {
  LMS303DLHC_MAG_RANGE_13,
  LMS303DLHC_MAG_RANGE_19,
  LMS303DLHC_MAG_RANGE_25,
  LMS303DLHC_MAG_RANGE_40,
  LMS303DLHC_MAG_RANGE_47,
  LMS303DLHC_MAG_RANGE_56,
  LMS303DLHC_MAG_RANGE_81,
};

enum lsm303dlhc_acc_sens {
  LMS303DLHC_ACC_SENS_2,
  LMS303DLHC_ACC_SENS_4,
  LMS303DLHC_ACC_SENS_12,
};

enum lsm303dlhc_acc_operartion_t {
  LMS303DLHC_ACC_OP_LOW_POWER,
  LMS303DLHC_ACC_OP_NORMAL,
};

enum lsm303dlhc_mag_operation_t {
  LMS303DLHC_MAG_OP_CONTINUOUS,
  LMS303DLHC_MAG_OP_SINGLE,
  LMS303DLHC_MAG_OP_SLEEP
};

enum lsm303dlhc_acc_init_t { LMS303DLHC_ACC_INIT_DEFAULT };
enum lsm303dlhc_mag_init_t { LMS303DLHC_MAG_INIT_DEFAULT };

// Accelerometer functions.
// fixed initialization for now, handles ctrl_reg {1 - 6}
esp_err_t lsm303dlhc_acc_init(i2c_master_dev_handle_t dev_handle,
                              enum lsm303dlhc_acc_init_t init_args);

esp_err_t lsm303dlhc_acc_get_status(i2c_master_dev_handle_t dev_handle,
                                    uint8_t *const status);
esp_err_t lsm303dlhc_acc_get_x(i2c_master_dev_handle_t dev_handle,
                               int16_t *const x);
esp_err_t lsm303dlhc_acc_get_y(i2c_master_dev_handle_t dev_handle,
                               int16_t *const y);
esp_err_t lsm303dlhc_acc_get_z(i2c_master_dev_handle_t dev_handle,
                               int16_t *const z);

esp_err_t lsm303dlhc_acc_get_xyz(i2c_master_dev_handle_t dev_handle, int16_t *x,
                                 int16_t *y, int16_t *z);
// fifo is yet to be handled for acc.

// Magnetometer functions.
esp_err_t lsm303dlhc_mag_init(i2c_master_dev_handle_t dev_handle);
esp_err_t lsm303dlhc_mag_get_status(i2c_master_dev_handle_t dev_handle,
                                    uint8_t *status);
esp_err_t lsm303dlhc_mag_get_x(i2c_master_dev_handle_t dev_handle, int16_t *x);
esp_err_t lsm303dlhc_mag_get_y(i2c_master_dev_handle_t dev_handle, int16_t *y);
esp_err_t lsm303dlhc_mag_get_z(i2c_master_dev_handle_t dev_handle, int16_t *z);
esp_err_t lsm303dlhc_mag_get_xyz(i2c_master_dev_handle_t dev_handle, int16_t *x,
                                 int16_t *y, int16_t *z);

#endif
