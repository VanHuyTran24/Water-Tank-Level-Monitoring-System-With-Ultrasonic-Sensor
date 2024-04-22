# Water-Tank-Level-Monitoring-System-With-Ultrasonic-Sensor

## Components used:
<ul>
  <li>Arduino Uno</li>
  <li>HC-SR04 Ultrasonic Sensor</li>
  <li>DHT11 Temperature and Humidity Sensor Module</li>
  <li>DS18B20 Temperature Sensor</li>
  <li>LCD Display LCD2004 Module Green Screen with I2C</li>
  <li>DC 12V 365 Motor Pump Large Flow Centrifugal Pump</li>
  <li>Module Relay 5V 10A</li>
</ul>

## Block Diagram of the model
![image](https://github.com/VanHuyTran24/Water-Tank-Level-Monitoring-System-With-Ultrasonic-Sensor/assets/166670555/b995b150-469b-4bef-810d-402885d45dfe)

## Actual Prototype
![image](https://github.com/VanHuyTran24/Water-Tank-Level-Monitoring-System-With-Ultrasonic-Sensor/assets/166670555/b6519ce3-f834-4e28-be8e-9c437eaeebc2)

## Working principle of the model 
This is a water pump system with 2 modes:

•	Auto mode: when the HC-SR04 ultrasonic sensor detects that the water level is below 25% of the tank, it will automatically start the water pump to pump water into the tank until it is full (>90%) and automatically stops the pump.

•	Manual mode: we can start the pump and stop it with the switch.
These 2 modes are switched by switch.
The system will monitor the water level and temperature of the water in the and output it to the screen including the water level, mode, pump status and water temperature in the tank.

## Pinout Diagram
![image](https://github.com/VanHuyTran24/Water-Tank-Level-Monitoring-System-With-Ultrasonic-Sensor/assets/166670555/cd2e35aa-72cb-4dbd-999d-01cf5bc35c18)


## Experiment
![image](https://github.com/VanHuyTran24/Water-Tank-Level-Monitoring-System-With-Ultrasonic-Sensor/assets/166670555/13029111-67c2-4713-8e7e-02617cc1bac1)

## Plot of water level versus time of pumping
![image](https://github.com/VanHuyTran24/Water-Tank-Level-Monitoring-System-With-Ultrasonic-Sensor/assets/166670555/59fcae6f-e66c-4746-baaf-3dd3ccee43f8)

Blue line – Noise-unfiltered

Orange line – Noise-filtered

## Report
Download report file (.docx) from [here](https://github.com/VanHuyTran24/Water-Tank-Level-Monitoring-System-With-Ultrasonic-Sensor/blob/main/PROJECT/Report.docx)

