// Constants
#define FWVERSION "1.5"
#define SLEEPTIMEOUT 100000

#define RXD2 RX
#define TXD2 TX

#define LENS_ADC_PIN 1 // Lens position sensor pin used on the ADS1115

#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 128        // OLED display height, in pixels
#define OLED_RESET -1           // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D     // OLED display address

const int SMOOTHING_WINDOW_SIZE = 15;

// Light meter constants
const int K = 20; // Calibration constant
const int ISOS[] = {25, 50, 80, 100, 125, 200, 400, 500, 640, 800, 1600, 3200, 6400};
const float APERTURES[] = {5.6, 8, 11, 16, 22, 32, 45};


// LiDAR constants
#define LIDAR_OFFSET 50 // Offset in mm from the LiDAR sensor to the film plane
#define DISTANCE_MIN 15 // Minimum distance in cm (usually the same for TFLuna, TFMini, etc.)
#define DISTANCE_MAX 800 // Maximum distance in cm (depends on your LiDAR sensor)

// Lens and RF constants
#define LENS_MOVEMENT_MM_MAX 30  // Lens movement in mm - this is actually the max amount that the RF arm moves
#define LENS_MOVEMENT_MM_MIN 0  // Lens movement in mm - this is actually the min amount that the RF arm moves
#define LENS_MOVEMENT_MULTIPLIER 8  // This is the actual max range of movement at the lens board
const int DIOPTERS[] = {0, 1, 2, 3, 4};  // Diopter values
const String CALIB_DISTANCES[] = {"Inf.", "Close"}; // Calibration distances

// Lomograflok rangefinder constants and variables
#define LOMOGRAFLOK_OFFSET 15 // LG offset - technically 19mm, but slightly less for this camera / setup

// UI constants
#define CIRCLE_X 68
#define CIRCLE_Y 80