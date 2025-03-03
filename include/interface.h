void drawMainUI()
{
  display.clearDisplay();

  u8g2.setFontMode(1);
  u8g2.setFontDirection(0);
  u8g2.setForegroundColor(BLACK);
  u8g2.setBackgroundColor(WHITE);
  u8g2.setFont(u8g2_font_4x6_mf);
  display.fillRect(0, 0, 128, 15, WHITE);
  display.drawLine(64, 0, 64, 128, BLACK);
  u8g2.setCursor(4, 7);
  u8g2.print(F("ISO"));
  u8g2.print(iso);
  u8g2.setCursor(46, 7);
  u8g2.print(F("f"));
  if (aperture == static_cast<int>(aperture))
  {
    u8g2.print(static_cast<int>(aperture));
  }
  else
  {
    u8g2.print(aperture, 1);
  }
  u8g2.setCursor(4, 14);
  u8g2.print(shutter_speed);
  u8g2.setCursor(68, 7);
  u8g2.print(F("Dist:"));
  u8g2.print(distance_cm);
  u8g2.setCursor(68, 14);

  if (selected_diopter > 0) {
    u8g2.print(F("Lens+"));
    u8g2.print(selected_diopter);
    u8g2.print(F(":"));
  }
  else {
    u8g2.print(F("Lens:"));
  }
  u8g2.print(lens_distance_cm);

  u8g2.setForegroundColor(WHITE);
  u8g2.setCursor(4, 21);
  if (lgmode)
  {
    u8g2.print(F("LG"));
  }
  else
  {
    u8g2.print(F("4X5"));
  }

  u8g2.setCursor(111, 21);
  u8g2.print(bat_per);
  u8g2.print(F("%"));

  int framelines_1 = lenses[selected_lens].framelines[0];
  int framelines_2 = lenses[selected_lens].framelines[1];
  int framelines_3 = lenses[selected_lens].framelines[2];
  int framelines_4 = lenses[selected_lens].framelines[3];

  if (lgmode)
  {
    framelines_1 = lenses[selected_lens].lg_framelines[0];
    framelines_2 = lenses[selected_lens].lg_framelines[1];
    framelines_3 = lenses[selected_lens].lg_framelines[2];
    framelines_4 = lenses[selected_lens].lg_framelines[3];
  }
  
  display.drawRect( 
    framelines_1,
    framelines_2,
    framelines_3,
    framelines_4,
    WHITE
  );

  display.fillCircle(CIRCLE_X, CIRCLE_Y, 2, WHITE);
  display.drawCircle(CIRCLE_X, CIRCLE_Y, getFocusRadius(), WHITE);

  display.display();
}

void drawTextUI(const char* text) {
  display.clearDisplay();

  u8g2.setFontMode(1);
  u8g2.setFontDirection(0);
  u8g2.setForegroundColor(WHITE);
  u8g2.setFont(u8g2_font_4x6_mf);
  
  // Calculate the width of the text to be centered
  int16_t textWidth = u8g2.getUTF8Width(text);

  // Calculate the x position to center the text
  int16_t x = (SCREEN_WIDTH - textWidth) / 2;

  // Set the cursor to the calculated position
  u8g2.setCursor(x, SCREEN_HEIGHT / 2);
  u8g2.print(F(text));

  display.display();
}


void drawConfigUI()
{
  display.clearDisplay();

  u8g2.setFontMode(1);
  u8g2.setFontDirection(0);
  u8g2.setForegroundColor(WHITE);
  u8g2.setBackgroundColor(BLACK);

  u8g2.setFont(u8g2_font_9x15_mf);
  u8g2.setCursor(3, 15);
  u8g2.print(F("Setup"));

  u8g2.setFont(u8g2_font_4x6_mf);
  u8g2.setCursor(3, 26);

  if (config_step == 0)
  {
    u8g2.setBackgroundColor(WHITE);
    u8g2.setForegroundColor(BLACK);
  }
  else
  {
    u8g2.setBackgroundColor(BLACK);
    u8g2.setForegroundColor(WHITE);
  }
  u8g2.print(F(" ISO:"));
  u8g2.print(iso);
  u8g2.print(F(" "));

  if (config_step == 1)
  {
    u8g2.setBackgroundColor(WHITE);
    u8g2.setForegroundColor(BLACK);
  }
  else
  {
    u8g2.setBackgroundColor(BLACK);
    u8g2.setForegroundColor(WHITE);
  }
  u8g2.setCursor(3, 37);
  u8g2.print(F(" Format:"));
  if (lgmode)
  {
    u8g2.print(F("Lomograflok"));
  }
  else {
    u8g2.print(F("4X5"));
  }
  u8g2.print(F(" "));

  if (config_step == 2)
  {
    u8g2.setBackgroundColor(WHITE);
    u8g2.setForegroundColor(BLACK);
  }
  else
  {
    u8g2.setBackgroundColor(BLACK);
    u8g2.setForegroundColor(WHITE);
  }
  u8g2.setCursor(3, 48);
  u8g2.print(F(" Lens:"));
  u8g2.print(lenses[selected_lens].name);
  u8g2.print(F(" "));

  if (config_step == 3)
  {
    u8g2.setBackgroundColor(WHITE);
    u8g2.setForegroundColor(BLACK);
  }
  else
  {
    u8g2.setBackgroundColor(BLACK);
    u8g2.setForegroundColor(WHITE);
  }
  u8g2.setCursor(3, 59);
  u8g2.print(F(" Diopter:"));
  u8g2.print(selected_diopter);
  u8g2.print(F(" "));

  if (config_step == 4)
  {
    u8g2.setBackgroundColor(WHITE);
    u8g2.setForegroundColor(BLACK);
  }
  else
  {
    u8g2.setBackgroundColor(BLACK);
    u8g2.setForegroundColor(WHITE);
  }
  u8g2.setCursor(3, 70);
  u8g2.print(F(" RF Calib. > "));

  if (config_step == 5)
  {
    u8g2.setBackgroundColor(WHITE);
    u8g2.setForegroundColor(BLACK);
  }
  else
  {
    u8g2.setBackgroundColor(BLACK);
    u8g2.setForegroundColor(WHITE);
  }
  u8g2.setCursor(3, 81);
  u8g2.print(F(" Exit >> "));

  u8g2.setBackgroundColor(BLACK);
  u8g2.setForegroundColor(WHITE);

  u8g2.setFont(u8g2_font_micro_mr);
  u8g2.setCursor(3, 95);
  u8g2.print(F(" [Top] to Select"));
  u8g2.setCursor(3, 105);
  u8g2.print(F(" [Bottom] to Cycle"));

  u8g2.setFont(u8g2_font_4x6_mf);
  u8g2.setCursor(3, 120);
  u8g2.print(F(" IDENTIDEM.design RhodiumOS "));
  u8g2.print(FWVERSION);

  display.display();
}

void drawCalibUI()
{
  display.clearDisplay();

  u8g2.setFontMode(1);
  u8g2.setFontDirection(0);
  u8g2.setForegroundColor(WHITE);
  u8g2.setBackgroundColor(BLACK);

  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.setCursor(3, 15);
  u8g2.print(F("Calibrate"));

  u8g2.setFont(u8g2_font_4x6_mf);
  u8g2.setCursor(3, 47);

  u8g2.print(F(" "));
  u8g2.print(CALIB_DISTANCES[current_calib_distance]);
  u8g2.print(F(": "));
  u8g2.print((getLensSensorReading() / 10) * 10);
  u8g2.print(F(" "));

  u8g2.setBackgroundColor(BLACK);
  u8g2.setForegroundColor(WHITE);

  u8g2.setCursor(3, 70);
  u8g2.print(F(" [Top] to Cancel"));
  u8g2.setCursor(3, 81);
  u8g2.print(F(" [Bottom] to Select"));

  display.display();
}