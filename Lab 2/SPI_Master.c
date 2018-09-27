#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <string.h>
#include <linux/types.h>

int fd;
uint8_t data[2] = {0x8A, 0x3F};
uint8_t result;
uint8_t spi_mode;
uint8_t spi_bpw;
uint32_t speed;

uint8_t transfer(uint8_t txDat);
void SPI_Init(void);

int main(void) {
    fd = open("/dev/spidev0.0", O_RDWR);

    speed = 93750;
    spi_mode = SPI_MODE_0;
    spi_bpw = 8;

    while (1) {
        for (int i = 0; i < sizeof(data); i++) {
            printf("Transferring %x \n", data[1]);
            result = transfer(data[1]);
            printf("Received %x \n", result);
            usleep(1000000);
        }
    }

    close(fd);
}

uint8_t transfer(uint8_t txDat) {
    uint8_t tx[1] = {txDat};
    uint8_t rx[1] = {0};

    struct spi_ioc_transfer spi;

    memset(&spi, 0, sizeof(spi));

    spi.tx_buf = (unsigned long) &tx;
    spi.rx_buf = (unsigned long) &rx;

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi);
    if (ret < 1)
		printf("can't send spi message \n");

    return rx;
}

void SPI_Init(void) {
    int ret;

	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &spi_mode);
	if (ret == -1) {
		printf("can't set spi mode \n");
    }

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bpw);
	if (ret == -1) {
		printf("can't set bits per word \n");
    }

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1) {
		printf("can't set max speed hz \n");
    }

	printf("spi mode: %d\n", spi_mode);
	printf("bits per word: %d\n", spi_bpw);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
}