# Rhodium M / RhodiumOS

- Firmware folder has the PlatformIO project for Arduino / ESP32 firmware for the LiDAR RF version of the Panomicron Rhodium.
- CAD folder contains STEP file
- PCB folder contains Gerbers

### Credits:

- [Rhodium by Oscar Oweson / Panomicron](https://www.panomicron.com/rhodium)
- Modded by Mario over at [SPRKPLG](https://sprkplg.com/)

### Required hardware

- Adafruit Feather ESP32-S3 (5477)
- Adafruit 1.12" OLED (5297)
- TF Luna Lidar Sensor (search on AliExpress)
- [404R10KL.5 Linear Potentiometer](https://mou.sr/3EZ1Xdd)
- Adafruit BH1750 module (4681)
- Adafruit ADS1115 module (1085)
- Adafruit 5v 1A miniboost (4654)
- [LiPO battery](https://www.amazon.co.uk/dp/B082152887)
- 2x [8mm momentary push buttons](https://www.amazon.co.uk/dp/B07S1MNB8C)
- 1x [DPDT switch](https://www.amazon.co.uk/dp/B01N4OSKWE)
- 3x STEMMA QT cables
- 30x30x1.1mm 50T/50R beam splitter
- [20mm Dia. x 70mm FL Plano-Convex Lens](https://www.edmundoptics.co.uk/p/200mm-dia-x-700mm-fl-uncoated-plano-convex-lens/2705/)
- [25mm Dia. x -25 FL Plano-Concave Lens](https://www.edmundoptics.co.uk/p/250mm-dia-x25-fl-uncoated-plano-concave-lens/5542/)
  
### Quick, dirty wiring instructions:

1. STEMMA QT goes from OLED, to BH1750, to ADS1115, to ESP32
2. STEMMA QT power line goes to center pin of power switch , and left pin on one side (when the EN pin is pulled to GND to "switch off" the Feather, you want to kill power to the STEMMA boards as well to save power)
3. EN pin of Feather goes to right pin of power switch, and GND to center pin, on other side
4. 3V on Feather goes to VIN on Miniboost, and GND to GND
5. 5V from Miniboost goes to VIN on TF LUNA, and GND to GND
6. RX from TF Luna goes to TX on Feather, TX from TF Luna goes to RX on Feather
7. Center pin on 404 Linear Pot goes to A1 on ADS1115, and left and right to + and - (make sure you get this the right way around, when you move from infinity to close focus, the value should increase) 

