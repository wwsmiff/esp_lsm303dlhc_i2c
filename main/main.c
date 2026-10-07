#include "lsm303dlhc_i2c.h"
#include <driver/i2c_master.h>
#include <stdio.h>

void app_main(void) {
  i2c_master_bus_config_t i2c_mst_config = {
      .clk_source = I2C_CLK_SRC_DEFAULT,
      .i2c_port = I2C_NUM_0,
      .sda_io_num = 21,
      .scl_io_num = 22,
      .glitch_ignore_cnt = 7,
      .flags.enable_internal_pullup = false,
  };

  i2c_master_bus_handle_t bus_handle;
  ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

  for (int addr = 0x0; addr < 0x7f; ++addr) {
    esp_err_t e = i2c_master_probe(bus_handle, addr, 500);
    if (e == ESP_OK) {
      printf("Found device at address: %x.\n", addr);
    } else {
      printf("No device found at address: %x.\n", addr);
    }
  }

  i2c_device_config_t dev_cfg = {
      .dev_addr_length = I2C_ADDR_BIT_LEN_7,
      .device_address = 0x19,
      .scl_speed_hz = 100'000,
  };

  i2c_master_dev_handle_t dev_handle;

  ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));
  ESP_ERROR_CHECK(lms303dlhc_acc_init(dev_handle, LMS303DLHC_ACC_INIT_DEFAULT));

  while (1) {
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;

    /*ESP_ERROR_CHECK(lms303dlhc_acc_get_x(dev_handle, &x));*/
    /*ESP_ERROR_CHECK(lms303dlhc_acc_get_y(dev_handle, &y));*/
    /*ESP_ERROR_CHECK(lms303dlhc_acc_get_z(dev_handle, &z));*/
    ESP_ERROR_CHECK(lms303dlhc_acc_get_xyz(dev_handle, &x, &y, &z));

    printf("x = %dmg, y = %dmg, z = %dmg\n", x, y, z);
  }
}
