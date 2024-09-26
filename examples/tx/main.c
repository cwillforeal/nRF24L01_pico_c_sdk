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
	uint8_t test_byte = 0xAA;
	uint8_t status;

	// initialize stdio and wait for USB CDC connect
	stdio_init_all();

	while(!tud_cdc_connected())
	{
		tight_loop_contents();
	}
	printf("Starting Transmitter Initalization...\n");

	nrf24_device(TRANSMITTER, RESET);

	while(1)
	{
		status = nrf24_transmit(&test_byte, 1, ACK_MODE);
		if(status == TRANSMIT_FAIL)
		{
			printf("Couldn't start transmit\r\n");
		}
		else
		{
			status = TRANSMIT_IN_PROGRESS;
			while(status == TRANSMIT_IN_PROGRESS)
			{
				status = nrf24_transmit_status();
			}
			if(status == TRANSMIT_DONE)
			{
				printf("Data sent successfully\r\n");
			}
			else
			{
				printf("Transmit timeout\r\n");
			}
		}

		sleep_ms(1000);
	}
}