/**
 * Simple example using the radio.
 */
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/spi.h"
#include "tusb.h"
#include "nrf24l01.h"

int main(void)
{
	// initialize stdio and wait for USB CDC connect
	stdio_init_all();

	while(!tud_cdc_connected())
	{
		tight_loop_contents();
	}
	printf("Starting Initalization...\n");

	nrf24_device(TRANSMITTER, RESET);

	while(1)
		;
}