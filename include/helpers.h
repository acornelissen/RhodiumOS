

// Helper functions
// ---------------------

void loadPrefs()
{
  prefs.begin("mrf", false);

  if (prefs.isKey("iso")) {
    iso = prefs.getInt("iso", 400);
    iso_index = prefs.getInt("iso_idx", 5);

    byte tempLenses[sizeof(lenses)];
    prefs.getBytes("lenses", tempLenses, sizeof(lenses));
    memcpy(lenses, tempLenses, sizeof(lenses));

    selected_lens = prefs.getInt("lens", 1);
    selected_diopter = prefs.getInt("dptr", 0);

    aperture = prefs.getFloat("aperture", APERTURES[0]);
    aperture_index = prefs.getInt("aperture_idx", 0);

    lgmode = prefs.getBool("lgmode", false);

  }

  prefs.end();
}

void savePrefs()
{
  prefs.begin("mrf", false);
  prefs.putInt("iso", iso);
  prefs.putInt("iso_idx", iso_index);
  prefs.putFloat("aperture", aperture);
  prefs.putInt("aperture_idx", aperture_index);
  prefs.putInt("lens", selected_lens);
  prefs.putInt("dptr", selected_diopter);
  prefs.putBool("lgmode", lgmode);
  prefs.putBytes("lenses", (byte *)lenses, sizeof(lenses));
  prefs.end();
}


String cmToReadable(int cm)
{

  if (cm < 100)
  {
    return String(cm) + "cm";
  }
  else
  {
    return String(float(cm) / 100, 1) + "m";
  }
}

int calcMovingAvg(int index, int sensorVal)
{
  int readIndex = curReadIndex[index];
  sampleTotal[index] = sampleTotal[index] - (samples[index][readIndex]);

  samples[index][readIndex] = sensorVal;
  sampleTotal[index] = sampleTotal[index] + samples[index][readIndex];
  curReadIndex[index] = curReadIndex[index] + 1;

  if (curReadIndex[index] >= SMOOTHING_WINDOW_SIZE)
  {
    curReadIndex[index] = 0;
  }

  sampleAvg[index] = sampleTotal[index] / SMOOTHING_WINDOW_SIZE;
  return sampleAvg[index];
}

int_fast16_t getFocusRadius()
{
  int minRadius = 2;
  int maxRadius = 40;

  int radius = min(maxRadius, max(minRadius, abs(distance_display - lens_distance_raw)));

  return radius;
}


// Function to compute the constants a and b for d = a * ln(r) + b
typedef struct {
  float a;
  float b;
} VCNL4040LogFunctionConstants;

VCNL4040LogFunctionConstants computeLogConstants(int r1, float d1, int r2, float d2) {
  VCNL4040LogFunctionConstants constants;
  
  if (r1 <= 0 || r2 <= 0 || r1 == r2) {
      constants.a = 0;
      constants.b = 0;
      return constants; // Return zeros for invalid input
  }
  
  // Solve for a and b
  constants.a = (d2 - d1) / (log(r2) - log(r1));
  constants.b = d1 - constants.a * log(r1);
  
  return constants;
}
// ---------------------