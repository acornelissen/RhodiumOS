// Functions to check and act on button presses
// ---------------------
void checkButtons()
{
    lbutton.update();
    if (lbutton.rose() && lbutton.previousDuration() < 1000)
    {
      lastActivityTime = millis();
      if (sleepMode == true) {
        sleepMode = false;
      }
      else {
        if (ui_mode == "main")
        {
          cycleApertures("down");
        }
        else if (ui_mode == "config")
        {
          config_step++;
          if (config_step > 5)
          {
            config_step = 0;
          }
        }
        else if (ui_mode == "calib")
        {
            calib_distance_set[current_calib_distance] = (getLensSensorReading() / 10) * 10;
            current_calib_distance++;
            if (current_calib_distance >= sizeof(CALIB_DISTANCES) / sizeof(CALIB_DISTANCES[0]))
            {
                for (int i = 0; i < sizeof(calib_distance_set) / sizeof(calib_distance_set[0]); i++)
                {
                lenses[selected_lens].sensor_reading[i] = calib_distance_set[i];
                }
                savePrefs();
                setLensDistance(true);
                ui_mode = "config";
            }
        }
      }
}

  rbutton.update();
  if (rbutton.isPressed() && rbutton.currentDuration() >= 3000) 
  {
    lastActivityTime = millis();
    if (ui_mode == "main")
    {
      ui_mode = "config";
    }
    else if (ui_mode == "config") // Reset all settings to default
    {
      clearPrefs();
    }
  }
  else if (rbutton.rose() && rbutton.previousDuration() < 1000)
  {
    lastActivityTime = millis();
    if (sleepMode == true) {
      sleepMode = false;
    }
    else {
        if (ui_mode == "main")
        {
          cycleApertures("up");
        }
        else if (ui_mode == "config")
        {
          if (config_step == 0)
          {
            cycleISOs();
          }
          else if (config_step == 1)
          {
            cycleFormats();
          }
          else if (config_step == 2)
          {
            cycleLenses();
          }
          else if (config_step == 3)
          {
            cycleDiopters();
          }
          else if (config_step == 4)
          {
            current_calib_distance = 0;
            memset(calib_distance_set, 0, sizeof(calib_distance_set));
            ui_mode = "calib";
          }
          else if (config_step == 5)
          {
            ui_mode = "main";
            config_step = 0;
          }
        }
        else if (ui_mode == "calib") {
            ui_mode = "config";
        }
    }
  }
}
// ---------------------