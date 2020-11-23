# Introduction

Watering plants or crop is the main problem we face these days. Much manual effort is kept in watering crops, and the motor should be kept on and off at regular intervals. If you are out of the station, it becomes a problem. Sometimes, we may not know whether a crop should be watered or not at that particular time. 

In this project, I developed a system where we can monitor the soil moisture values and also control the motor using the cloud. This project is designed to help farmers know their soil's moisture and water their crops from anywhere in the world. I used a soil moister sensor to get the moister values, and this data is sent to ESP-32, which uses its Wi-Fi module to transfer the data to the cloud. I used the Ubidots cloud service platform to view the data and control the motor. I used the MQTT protocol where the sensor works as a publisher, and the relay is a subscriber.

Following are components I used for building the smart sprinkler
1. ESP-32 board
2. Relay (4 – module)
3. Soil moister sensor
4. Ac motor
5. Jumper wires
6. Sprinklers
7. Pipes
8. Laptop


# Design

<p align = "center">
 <img src = "https://github.com/gvteja99/smart_sprinkler_system/blob/master/images/design.jpg"
      </p>

The soil moisture sensor is connected to the ESP32 module at pin 35. It sends analog data to the module, the data is then sent from the ESP32 Wi-Fi module to Ubidots Cloud, where we can monitor the dryness value and can switch on the relay connected at pin 23 from the internet using a computer/mobile, which then sends a signal to on the relay which lets power go through the submersible water pump which will pump the water from the tank to the sprinklers.


# Project Pictures

<p align = "center">
 <img src = "https://github.com/gvteja99/smart_sprinkler_system/blob/master/images/sprinkler_image.jpg"
      </p>

The sprinkler used in the project can also be controlled using the Ubidots application.

<p align = "center">
 <img src = "https://github.com/gvteja99/smart_sprinkler_system/blob/master/images/ESP32_image.jpg"
      </p>

This is an ESP-32 board (Wi-Fi and Bluetooth) that can send the data to the Ubidots cloud service platform.


# Project Architecture

<p align = "center">
 <img src = "https://github.com/gvteja99/smart_sprinkler_system/blob/master/images/architecture.png"
      </p>

1. The soil moisture sensor is connected to the ESP-32 board here for sensor input pin 17 is used.
2. Sensors VCC is connected to esp32 VCC and GND to GND.
3. Relay(at input 1 ) is connected to esp32 at PIN 28.
4. Relay VCC is connected to esp32 VCC and GND to GND.
5. Relay is connected to the motor at k1, the motor is given a power supply.
6. ESP-32 gets input data from the sensor, and then with the Wi-Fi module, it sends data to the cloud platform.


# Ubidots Platform

This cloud service platform provides us to operate and monitor the devices. They use the MQTT protocol for functioning. Ubidots technology and engineering stack were developed to deliver a secure, white-glove experience for the users. Device friendly APIs (accessed over HTTP/MQTT/TCP/UDP protocols) provides a simple and secure connection for sending and
retrieving data to and from the cloud service in real-time. Ubidots’ time-series backend services are performance optimized for IoT data storage, computation, and retrieval.
In the project, the sensor acts as a publisher, and the relay acts as a subscriber. We get data input from a sensor to the cloud, and we can control the relay, which is connected to the motor through the cloud.

<p align = "center">
 <img src = "https://github.com/gvteja99/smart_sprinkler_system/blob/master/images/ubidots_ss1.jpg"
      </p>

Relays 1 and 2 are connected to soil moisture sensors, and the controlling is done using the Ubidots cloud service application as shown above (relay 1 is turned on, and relay 2 is off).

<p align = "center">
 <img src = "https://github.com/gvteja99/smart_sprinkler_system/blob/master/images/ubidots_ss2.jpg"
      </p>

If the moisture in the soil is full, which indicates 0, and if there is no moisture, then it will show the maximum value that is 4095


# Conclusion

This project's main objective is to avoid wastage of water and increase irrigation efficiency by using Arduino-based irrigation system with the help of a soil moisture sensor and relay. This technology is easily deployable and can be controlled manually or automatically without a physical presence at the field. Likewise, this technology can also be integrated for home automation where the room temperature, gas leakage, etc., can also be measured through sensors, and data is sent to the cloud and can be controlled accordingly. GSM can be added for sending SMS to the concerned person. Likewise, pesticides and fertilizers can be added, ambient temperature, humidity, the light intensity can also be measured.
