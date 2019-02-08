#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

//================================================================
// VARIABLES AND FUNCTIONS PROTOTYPES
//================================================================

int fd;
uint8_t data[] = {0x8a, 0x3f};
uint8_t mode;
uint8_t bits = 8;
uint8_t index = 0;
uint32_t speed = 500000;
uint16_t delay;

void SPI_Init(void);
void SPI_Transfer(int fd, uint8_t txDat);

//================================================================
// MAIN FUNCTION
//================================================================

int main(int argc, char *argv[])
{
	fd = open("/dev/spidev0.0", O_RDWR);
	if (fd < 0)
		printf("can't open device");

	SPI_Init();

	while (1) {
		SPI_Transfer(fd, data[index]);
		usleep(1000000);
		index = !index;
	}
	
	close(fd);
}

//================================================================
// FUNCTION BODY
//================================================================

void SPI_Init(void) {
	int ret;
	
	// SPI Mode
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		printf("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		printf("can't get spi mode");

	// Bits per word
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		printf("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		printf("can't get bits per word");

	// Max speed
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		printf("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		printf("can't get max speed hz");

	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
}


void SPI_Transfer(int fd, uint8_t txDat)
{
	uint8_t tx[] = {txDat};
	uint8_t rx[sizeof(tx)] = {0, };

	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = sizeof(tx),
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	printf("Transferring %.2x", txDat);
	int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
		printf("can't send spi message");

	for (int ret = 0; ret < sizeof(tx); ret++) {
		if (!(ret % 6))
			puts("");
		printf("Received %.2x ", rx[ret]);
	}
	puts("");
	puts("");
}