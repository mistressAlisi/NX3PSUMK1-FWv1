#!/bin/bash
/home/rasheek/.espressif/python_env/idf4.4_py3.9_env/bin/python ../esp-idf/components/esptool_py/esptool/esptool.py -p /dev/ttyUSB0 -b 2000000 --before default_reset --after hard_reset --chip esp32  write_flash --flash_mode dio --flash_size detect --flash_freq 80m 0x1000 build/bootloader/bootloader.bin 0x8000 build/partition_table/partition-table.bin 0xe000 build/ota_data_initial.bin 0x10000 build/d9-NX3PDU-MK3-FWMK1.bin 0x310000 rootfs.img
