Bounce2::Button lbutton = Bounce2::Button();
Bounce2::Button rbutton = Bounce2::Button();

BH1750 lightMeter;

TFMPlus tfluna;
HardwareSerial lidarSerial(2); // Using serial port 2

Adafruit_SH1107 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 1000000, 1000000);
U8G2_FOR_ADAFRUIT_GFX u8g2;

Adafruit_ADS1115 ads1115;

// Battery gauge
Adafruit_MAX17048 maxlipo;