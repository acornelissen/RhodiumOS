#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_MAX1704X.h>
#include <Adafruit_ADS1X15.h>
#include <TFMPlus.h>
#include <BH1750.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <Bounce2.h>
#include <Preferences.h>
#include <math.h>


#include "driver/rtc_io.h"
#include "esp_wifi.h"
#include "esp_bt.h"

#include <constants.h>
#include <lenses.h>
#include <globals.h>
#include <hardware.h>
#include <helpers.h>
#include <cyclefuncs.h>
#include <setfuncs.h>
#include <interface.h>
#include <inputs.h>

void setup() {

  Serial.begin(115200);

  esp_wifi_stop(); // Stop WiFi to save power
  esp_bt_controller_disable(); // Stop Bluetooth to save power

  loadPrefs();

  lbutton.attach(10, INPUT_PULLUP);
  lbutton.interval(5);
  lbutton.setPressedState(LOW);
  rbutton.attach(9, INPUT_PULLUP);
  rbutton.interval(5);
  rbutton.setPressedState(LOW);

  delay(1000); // Slight delay or the displays won't work
  display.begin(0x3D, true); // Address 0x3D default
  display.oled_command(0xC8);
  display.setRotation(1);
  u8g2.begin(display);
  display.clearDisplay();
  display.display();


  lidarSerial.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(20);
  tfluna.begin(&lidarSerial);

  ads1115.begin();

  // Clear the moving average arrays
  for (int i = 0; i < SMOOTHING_WINDOW_SIZE; i++)
  {
    samples[0][i] = 0;
    samples[1][i] = 0;
  }

  // Start up the light meter
  maxlipo.begin();
  lightMeter.begin();

}

void loop() {

  checkButtons();

  if (millis() - lastActivityTime > SLEEPTIMEOUT) { // Step 3
    sleepMode = true;
  }

  if (sleepMode)
  {
    toggleLidar();
    drawSleepUI();
  }
  else {
    toggleLidar();
    setDistance();
    setLensDistance();
    setVoltage();
    setLightMeter();

    if (ui_mode == "main") {
      drawMainUI();
    }
    else if (ui_mode == "config") {
      drawConfigUI();
      setLensDistance(true);
    }
    else if (ui_mode == "calib") {
      drawCalibUI();
    }
    
  }
}
