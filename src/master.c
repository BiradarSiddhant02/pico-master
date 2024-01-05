#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include <string.h>
#include <math.h>
#include "hardware/spi.h"
#include "hardware/watchdog.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "master.h"

union DoubleToUint8 {
    double doubleValue;
    uint8_t uint8Array[BUFFER_LEN];
};

void convertDoubleToArray(double value, uint8_t result[8]) {
    uint8_t *bytePointer = (uint8_t *)&value;

    for (int i = 0; i < sizeof(double); i++) {
        result[i] = bytePointer[i];
    }
}

double convertArrayToDouble(uint8_t array[8]) {
    double result;
    uint8_t *bytePointer = (uint8_t *)&result;

    for (int i = 0; i < sizeof(double); i++) {
        bytePointer[i] = array[i];
    }

    return result;
}

void reverseArray(uint8_t arr[8]) {
    uint8_t start = 0;
    uint8_t end = BUFFER_LEN - 1;

    while (start < end) {
        // Swap elements at start and end indices
        uint8_t temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // Move indices toward the center
        start++;
        end--;
    }
}

void printbuf(uint8_t buf[8], double num) {
    int i;
    for (i = 0; i < BUFFER_LEN; ++i) {
        printf("%02x ", buf[i]);
    }
    printf("%f", num);
    printf("\n");
}
void reboot_pico() {
    watchdog_hw->scratch[0] = 0x4e4f; // Set the watchdog scratch register to trigger a reset
    watchdog_hw->scratch[1] = 0x5245;
    watchdog_hw->ctrl = WATCHDOG_CTRL_TRIGGER_BITS;

    // Add a delay after watchdog reset to allow the reset to complete
}

double gen_sample(double sample_num){
	return sin(2 * M_PI * FUNDAMENTAL_FREQUENCY * sample_num / SAMPLE_RATE) + sin(2 * M_PI * NOISE_FREQUENCY * sample_num / SAMPLE_RATE) ; 
}

void init_led(){
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}
void light_led(){
    gpio_put(LED_PIN, 1);
}

void init_spi(){
    #if !defined(spi_default) || !defined(PICO_DEFAULT_SPI_SCK_PIN) || !defined(PICO_DEFAULT_SPI_TX_PIN) || !defined(PICO_DEFAULT_SPI_RX_PIN) || !defined(PICO_DEFAULT_SPI_CSN_PIN)
	
    #warning spi/spi_master example requires a board with SPI pins
    puts("Default SPI pins were not defined");
	
    #else
    	// Enable SPI 0 at 1 MHz and connect to GPIOs
    	spi_init(spi_default, SAMPLE_RATE);
    	gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    	gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    	gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    	gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);
    	// Make the SPI pins available to picotool
    	bi_decl(bi_4pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI));
    #endif
}