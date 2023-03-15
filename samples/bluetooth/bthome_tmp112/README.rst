.. _bluetooth-bthome-tmp112-sample:

Bluetooth: BTHome sensor with TMP112
####################################

This application implements a temperature sensor using the nRF52xx and the `TMP112 <https://www.ti.com/product/TMP112>`_.
It advertises in the `BTHome <https://bthome.io>`_ format.

Requirements
************

* A board with BLE support and a TMP112 sensor connected according to the table below.
* A BTHome compatible listener, for example `Home Assistant <https://www.home-assistant.io/>`_ with the BTHome integration running.

The I2C pins for connecting the TMP112 are the default ones for each board as seen in the following table.

.. list-table:: TMP112 pins
   :widths: 30 25 25 25 25
   :header-rows: 1

   * - Board name
     - SDA
     - SCL
     - V+
     - GND
   * - nrf52840dk_nrf52840
     - P0.26
     - P0.27
     - VDD
     - GND
   * - nrf52840dongle_nrf52840
     - P0.26
     - P0.27
     - VDD
     - GND
   * - nrf52dk_nrf52832
     - P0.26
     - P0.27
     - VDD
     - GND
   * - nrf52_adafruit_feather
     - SDA
     - SCL
     - 3.3V
     - GND
