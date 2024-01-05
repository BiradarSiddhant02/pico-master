#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <math.h>
#include <stdint.h>
#include "hardware/spi.h"
#include "pico/binary_info.h"
#include "hardware/watchdog.h"
#include "hardware/gpio.h"
#include "master.h"

int main(){
	init_led();
	init_spi();
    stdio_init_all();

	double sample;
	uint8_t packed_sample[8], incoming[8], sample_num = 0;

	for (size_t i = 0; ; ++i) {
		light_led();

		sample = gen_sample(sample_num);
		convertDoubleToArray(sample, packed_sample);
		
		spi_write_read_blocking(spi_default, packed_sample, NULL, BUFFER_LEN);
		printf("%f\n", convertArrayToDouble(packed_sample));
		
		sample_num++;
	}	
	return 0;
}
