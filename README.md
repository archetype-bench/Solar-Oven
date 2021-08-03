# Solar-Oven
Android Application for Box-Type Solar Oven developed for data-logging, and real-time experimentation monitoring 

Android application to monitor temperature, humidity and sunlight insolation. The data-logging system records the values on to a SD-Card, and uploaded to Bolt IoT Cloud for real-time monitoring and storing values for further analysis.
The brains of the electronics device is an Atmega328P, (Arduino Uno/Nano) connected with Bolt IoT using Serial Port and HC-05 Bluetooth Module using Software Serial. The data is stored in SD card in CSV format.
