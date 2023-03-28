.. _bluetooth-bthome-temp-sensor-sample:

Bluetooth: BTHome temperature sensor
####################################

This application implements a temperature sensor using the :dtcompatible:`ti,tmp112` or the Maxim ds18b20 temperature sensors.
It advertises in the `BTHome <https://bthome.io>`_ format.

Requirements
************

* A board with one of these sensors built in to its :ref:`devicetree <dt-guide>`, or a devicetree
  overlay with such a node added.
  For information on how to connect and use these sensors see the :ref:`TMP112 sample<tmp112_sample>` and :ref:`DS18B20 sample<ds18b20_sample>`
* A BTHome compatible listener, for example `Home Assistant <https://www.home-assistant.io/>`_ with the BTHome integration running.
