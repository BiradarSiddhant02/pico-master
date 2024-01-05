#define BUFFER_LEN 8
#define SAMPLE_RATE 500
#define FUNDAMENTAL_FREQUENCY 2
#define NOISE_FREQUENCY 100

#define MISO 16
#define CS   17
#define SCLK 18
#define MOSI 19
#define SPI_PORT spi0
#define LED_PIN 25

double gen_sample(double sample_num);
void convertDoubleToArray(double value, uint8_t result[BUFFER_LEN]);
double convertArrayToDouble(uint8_t array[BUFFER_LEN]);
void reverseArray(uint8_t arr[8]);
void printbuf(uint8_t buf[8], double num);
void reboot_pico();
void init_led();
void light_led();
void init_spi();
