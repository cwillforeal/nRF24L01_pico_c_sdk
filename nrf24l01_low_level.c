#include "hardware/spi.h"
#include "nrf24l01.h"
#include "pico/stdlib.h"
#include "pico/time.h"

// Change these defines to fit your build
#define SPI_INST spi0
#define PIN_MISO (16)
#define PIN_CSN (17)
#define PIN_SCK (18)
#define PIN_MOSI (19)
#define PIN_CE (20)
#define PIN_IRQ (21)

#define SPI_BAUD 5000000 /*0-10MHz per data sheet */
/*start of low level functions, specific to the mcu and compiler*/

/*delay in miliseconds*/
void delay_function(uint32_t duration_ms)
{
	sleep_ms(duration_ms);
}

/*contains all SPI configuations, such as pins and control registers*/
/*SPI control: master, interrupts disabled, clock polarity low when idle, clock
 * phase falling edge, clock up tp 1 MHz*/
void SPI_Initializer()
{
	// SPI init
	spi_init(SPI_INST, SPI_BAUD); /* TODO: Whats the default clock pol and pha settings */
	gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
	gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
	gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
}

/*contains all CSN and CE pins gpio configurations, including setting them as
 * gpio outputs and turning SPI off and CE '1'*/
void pinout_Initializer()
{
	// Setup the IRQ
	gpio_init(PIN_IRQ);
	gpio_set_dir(PIN_IRQ, GPIO_IN);

	// Disable SPI
	gpio_init(PIN_CSN);
	gpio_set_dir(PIN_CSN, GPIO_OUT);
	nrf24_SPI(SPI_OFF);

	// Drive CS pin high
	gpio_init(PIN_CE);
	gpio_set_dir(PIN_CE, GPIO_OUT);
	nrf24_CE(CE_ON);
}

/*CSN pin manipulation to high or low (SPI on or off)*/
void nrf24_SPI(uint8_t input)
{
	if(input == SPI_ON)
	{
		gpio_put(PIN_CSN, 0);
	}
	else
	{
		gpio_put(PIN_CSN, 1);
	}
}

/*1 byte SPI shift register send and receive routine*/
uint8_t SPI_send_command(uint8_t command)
{
	uint8_t read_byte;

	spi_write_read_blocking(SPI_INST, &command, &read_byte, 1);

	return read_byte;
}

/*CE pin maniplation to high or low*/
void nrf24_CE(uint8_t input)
{
	if(input == CE_ON)
	{
		gpio_put(PIN_CE, 1);
	}
	else
	{
		gpio_put(PIN_CE, 0);
	}
}
