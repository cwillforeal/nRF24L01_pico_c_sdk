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
	uint8_t data;
	uint8_t status;

	// initialize stdio and wait for USB CDC connect
	stdio_init_all();

	while(!tud_cdc_connected())
	{
		tight_loop_contents();
	}
	printf("Starting Reciever Initalization...\n");

	nrf24_device(RECEIVER, RESET);

	while(1)
	{
		status = nrf24_receive(&data, 1);
		if(status == OPERATION_DONE)
		{
			printf("Data RXed\r\n");
		}
	}
}