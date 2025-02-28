#include <cmath>

// Functions to read values from sensors and set variables
// ---------------------
void setDistance()
{

  // Get data from the sensor
  tfluna.getData(distance);

  if (distance)
  { // Get data from Lidar
    distance_display = distance + LIDAR_OFFSET;
    if ( distance_display != prev_distance)
    {
      if ( distance_display >= DISTANCE_MAX)
      {
         distance_cm = "> " + String(DISTANCE_MAX / 100) + "m";
      }
      else if ( distance_display < DISTANCE_MIN)
      {
        distance_cm = "< " + String(DISTANCE_MIN) + "cm";
      }
      else {
        distance_cm = cmToReadable( distance_display);
      }
      prev_distance =  distance_display;
    }
  }
  else {
    distance_cm = "...";
  }
}


int getLensSensorReading()
{
  int sensorVal = ads1115.readADC_SingleEnded(LENS_ADC_PIN);
  return calcMovingAvg(0, sensorVal) / 10;
}

void setLensDistance(bool force_refresh = false)
{

  // Get the lens sensor reading and constrain it to the min and max values
  lens_sensor_reading = constrain(getLensSensorReading(), lenses[selected_lens].sensor_reading[0], lenses[selected_lens].sensor_reading[1]);
  
  
  // Perform linear interpolation to get the lens distance in mm, and round to 1 decimal place
  float lens_movement_mm = map(lens_sensor_reading, lenses[selected_lens].sensor_reading[0], lenses[selected_lens].sensor_reading[1], LENS_MOVEMENT_MM_MIN * 1000, LENS_MOVEMENT_MM_MAX * 1000) / 1000.00;
  lens_movement_mm = (LENS_MOVEMENT_MULTIPLIER * lens_movement_mm) / LENS_MOVEMENT_MM_MAX;

  if (lgmode) {
    lens_movement_mm = (LOMOGRAFLOK_OFFSET * lens_movement_mm) / LENS_MOVEMENT_MM_MAX;
    lens_movement_mm = lens_movement_mm + LOMOGRAFLOK_OFFSET;
  }


  lens_distance_raw = 9999999;
  if (lens_movement_mm > 0) {
    lens_distance_raw = ((lenses[selected_lens].focal_length * lenses[selected_lens].focal_length + 2 * lens_movement_mm * lenses[selected_lens].focal_length) / lens_movement_mm) / 10;
  
    if (selected_diopter > 0) {
     lens_distance_raw = ((lenses[selected_lens].focal_length / 1000) * selected_diopter) * lens_distance_raw;
    }
  }

  if (lens_sensor_reading != prev_lens_sensor_reading || force_refresh) {
    
    if (abs(lens_sensor_reading - prev_lens_sensor_reading) > 2) {
        lastActivityTime = millis();
    }
    
    prev_lens_sensor_reading = lens_sensor_reading;
    if (lens_sensor_reading  <= lenses[selected_lens].sensor_reading[1]) {
      lens_sensor_reading  = lenses[selected_lens].sensor_reading[1];
    }
        
    else if (lens_sensor_reading  >= lenses[selected_lens].sensor_reading[0]) {
      lens_sensor_reading  = lenses[selected_lens].sensor_reading[0];
    }

  if (lens_distance_raw >=  9999999 && lgmode == false && selected_diopter == 0) {
        lens_distance_cm = "Inf.";
    }
    else {
      lens_distance_cm = cmToReadable(lens_distance_raw);
    }
  }
   
}

void setVoltage()
{
  bat_per = maxlipo.cellPercent();
  if (bat_per > 100)
  {
    bat_per = 100;
  }

  if (bat_per != prev_bat_per)
  {
    prev_bat_per = bat_per;
  }
}

void setLightMeter()
{
  lux = lightMeter.readLightLevel();

  if (lux != prev_lux)
  {
    prev_lux = lux;
    if (lux <= 0)
    {
      shutter_speed = "Dark!";
    }
    else
    {

      if (aperture == 0)
      {
        cycleApertures("up");
      }

      float speed = round(((aperture * aperture) * K) / (lux * iso) * 1000.0) / 1000.0;

      struct SpeedRange
      {
        float lower;
        float upper;
        const char *print_speed_range;
      };

      SpeedRange speed_ranges[] = {
          {0.001, 0.002, "1/1000"},
          {0.002, 0.004, "1/500"},
          {0.004, 0.008, "1/250"},
          {0.008, 0.016, "1/125"},
          {0.016, 0.033, "1/60"},
          {0.033, 0.066, "1/30"},
          {0.066, 0.125, "1/15"},
          {0.125, 0.250, "1/8"},
          {0.250, 0.500, "1/4"},
          {0.500, 1, "1/2"}};

      char print_speed[10];
      dtostrf(speed, 4, 1, print_speed);

      for (int i = 0; i < sizeof(speed_ranges) / sizeof(speed_ranges[0]); i++)
      {
        if (speed_ranges[i].lower <= speed && speed < speed_ranges[i].upper)
        {
          strcpy(print_speed, speed_ranges[i].print_speed_range);
          break;
        }
      }

     
      if (speed >= 1)
      {
        char print_speed_raw[10];
        dtostrf(speed, 4, 2, print_speed_raw);
        shutter_speed = strcat(print_speed_raw, " sec.");
      }
      else {
         shutter_speed = strcat(print_speed, " sec.");
      }
       
    }
  }
}

void toggleLidar()
{
  if (sleepMode && lidarOn)
  {
    tfluna.sendCommand(DISABLE_OUTPUT, 0);
    lidarOn = false;
  }
  else if (!sleepMode && !lidarOn)
  {
    tfluna.sendCommand(ENABLE_OUTPUT, 0);
    lidarOn = true;
  }
}
// ---------------------