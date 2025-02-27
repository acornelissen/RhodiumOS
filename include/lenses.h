struct Lens
{
  int id;
  float focal_length;
  String name;
  int sensor_reading[7];
  int framelines[4];
  int lg_framelines[4];
};

// Lens and film format definitions
Lens lenses[] = {
    {135, 135.00, "135mm", {1470, 1720}, {0, 24, 128, 102}, {19, 49, 99, 79}},
    {150, 150.00, "150mm", {1470, 1720}, {0, 24, 128, 102}, {19, 49, 99, 79}},
    {180, 180.00, "180mm", {1470, 1720}, {0, 24, 128, 102}, {19, 49, 99, 79}},
};