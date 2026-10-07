#include "lsm303dlhc_i2c.h"
#include <driver/i2c_master.h>
#include <stdio.h>

#define WRITE_SIZE 1
#define TRANSACTION_TIMEOUT -1

static esp_err_t lms303dlhc_acc_write(i2c_master_dev_handle_t dev_handle,
                                      uint8_t reg, uint8_t value) {
  uint8_t write_buf[2] = {reg, value};
  esp_err_t e = i2c_master_transmit(dev_handle, write_buf, sizeof(write_buf),
                                    TRANSACTION_TIMEOUT);

  return e;
}

static esp_err_t lms303dlhc_acc_read(i2c_master_dev_handle_t dev_handle,
                                     uint8_t reg, uint8_t *value) {
  esp_err_t e = i2c_master_transmit_receive(dev_handle, &reg, 1, value, 1,
                                            TRANSACTION_TIMEOUT);

  return e;
}

esp_err_t lms303dlhc_acc_init(i2c_master_dev_handle_t dev_handle,
                              enum lms303dlhc_acc_init_t init_args) {
  esp_err_t e;
  // handle control register 1 - sets datarate, low power mode,
  // z enable, x enable and y enable
  uint8_t ctrl_reg_1_v = 0b1001'0'111;
  e = lms303dlhc_acc_write(dev_handle, LMS303DLHC_ACC_REG_CTRL1, ctrl_reg_1_v);
  if (e != ESP_OK)
    return e;
  // handle control register 2 - sets high pass filter parameters
  e = lms303dlhc_acc_write(dev_handle, LMS303DLHC_ACC_REG_CTRL2, 0);
  if (e != ESP_OK)
    return e;

  // handle control register 3 - handle interrupts and DRDY
  e = lms303dlhc_acc_write(dev_handle, LMS303DLHC_ACC_REG_CTRL3, 0);
  if (e != ESP_OK)
    return e;

  // handle control register 4
  uint8_t ctrl_reg_4_v = 0b10'00'1'00'0;
  e = lms303dlhc_acc_write(dev_handle, LMS303DLHC_ACC_REG_CTRL4, ctrl_reg_4_v);
  if (e != ESP_OK)
    return e;

  // handle control register 5
  uint8_t ctrl_reg_5_v = 0b1'0000000;
  e = lms303dlhc_acc_write(dev_handle, LMS303DLHC_ACC_REG_CTRL5, ctrl_reg_5_v);
  if (e != ESP_OK)
    return e;

  // handle control register 6 - handle interrupts
  e = lms303dlhc_acc_write(dev_handle, LMS303DLHC_ACC_REG_CTRL6, 0);
  if (e != ESP_OK)
    return e;

  return e;
}

esp_err_t lms303dlhc_acc_get_status(i2c_master_dev_handle_t dev_handle,
                                    uint8_t *const status) {

  esp_err_t e =
      lms303dlhc_acc_read(dev_handle, LMS303DLHC_ACC_REG_STATUS, status);
  return e;
}

esp_err_t lms303dlhc_acc_get_x(i2c_master_dev_handle_t dev_handle,
                               int16_t *const x) {
  uint8_t xh = 0;
  uint8_t xl = 0;
  esp_err_t e =
      lms303dlhc_acc_read(dev_handle, LMS303DLHC_ACC_REG_OUT_X_H, &xh);
  if (e != ESP_OK)
    return e;
  e = lms303dlhc_acc_read(dev_handle, LMS303DLHC_ACC_REG_OUT_X_L, &xl);
  if (e != ESP_OK)
    return e;

  *x = ((int16_t)(((uint16_t)(xh) << 8) | xl) >> 4);

  return e;
}

esp_err_t lms303dlhc_acc_get_y(i2c_master_dev_handle_t dev_handle,
                               int16_t *const y) {
  uint8_t yh = 0;
  uint8_t yl = 0;
  esp_err_t e =
      lms303dlhc_acc_read(dev_handle, LMS303DLHC_ACC_REG_OUT_Y_H, &yh);
  if (e != ESP_OK)
    return e;
  e = lms303dlhc_acc_read(dev_handle, LMS303DLHC_ACC_REG_OUT_Y_L, &yl);
  if (e != ESP_OK)
    return e;

  *y = ((int16_t)(((uint16_t)(yh) << 8) | yl) >> 4);

  return e;
}

esp_err_t lms303dlhc_acc_get_z(i2c_master_dev_handle_t dev_handle,
                               int16_t *const z) {
  uint8_t zh = 0;
  uint8_t zl = 0;
  esp_err_t e =
      lms303dlhc_acc_read(dev_handle, LMS303DLHC_ACC_REG_OUT_Z_H, &zh);
  if (e != ESP_OK)
    return e;
  lms303dlhc_acc_read(dev_handle, LMS303DLHC_ACC_REG_OUT_Z_L, &zl);
  if (e != ESP_OK)
    return e;

  *z = ((int16_t)(((uint16_t)(zh) << 8) | zl) >> 4);
  return e;
}

esp_err_t lms303dlhc_acc_get_xyz(i2c_master_dev_handle_t dev_handle, int16_t *x,
                                 int16_t *y, int16_t *z) {

  uint8_t data[6] = {0};

  uint8_t reg =
      LMS303DLHC_ACC_REG_OUT_X_L | 0b1000'0000; // enable auto-increment
  esp_err_t e = i2c_master_transmit_receive(dev_handle, &reg, 1, data, 6,
                                            TRANSACTION_TIMEOUT);

  uint8_t xl = data[0];
  uint8_t xh = data[1];
  uint8_t yl = data[2];
  uint8_t yh = data[3];
  uint8_t zl = data[4];
  uint8_t zh = data[5];

  *x = ((int16_t)(((uint16_t)(xh) << 8) | xl) >> 4);
  *y = ((int16_t)(((uint16_t)(yh) << 8) | yl) >> 4);
  *z = ((int16_t)(((uint16_t)(zh) << 8) | zl) >> 4);

  return e;
}
