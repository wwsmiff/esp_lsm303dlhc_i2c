idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
										PRIV_REQUIRES lsm303dlhc_i2c
										REQUIRES esp_driver_i2c
										)
