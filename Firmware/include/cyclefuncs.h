// Functions to cycle values
// ---------------------
void cycleApertures(String direction)
{
  if (direction == "up")
  {
    aperture_index++;
    if (aperture_index >= sizeof(APERTURES) / sizeof(APERTURES[0]))
    {
      aperture_index = 0;
    }
    if (APERTURES[aperture_index] == 0)
    {
      cycleApertures("up");
    }
  }
  else if (direction == "down")
  {
    aperture_index--;
    if (aperture_index < 0)
    {
      aperture_index = sizeof(APERTURES) / sizeof(APERTURES[0]) - 1;
    }
    if (APERTURES[aperture_index] == 0)
    {
      cycleApertures("down");
    }
  }

  aperture = APERTURES[aperture_index];

  savePrefs();
}

void cycleISOs()
{
  iso_index++;
  if (iso_index >= sizeof(ISOS) / sizeof(ISOS[0]))
  {
    iso_index = 0;
  }

  iso = ISOS[iso_index];
  savePrefs();
}

void cycleLenses()
{
  selected_lens++;
  if (selected_lens >= sizeof(lenses) / sizeof(lenses[0]))
  {
    selected_lens = 0;
  }
  savePrefs();
}

void cycleDiopters()
{
  selected_diopter++;
  if (selected_diopter >= sizeof(DIOPTERS) / sizeof(DIOPTERS[0]))
  {
    selected_diopter = 0;
  }
  savePrefs();
}

void cycleFormats()
{
  if (lgmode)
  {
    lgmode = false;
  }
  else
  {
    lgmode = true;
  }
  savePrefs();
}
