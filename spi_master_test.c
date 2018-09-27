#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <string.h>

int fd;
unsigned char hello[] = {'H','e','l','l','o',' ','W','o','r','l','d'};
unsigned char result;

int spiTxRx(unsigned char txDat);

int main(void)
{
	fd = open("/dev/spidev0.0", O_RDWR);

	unsigned int speed = 100000;
	unsigned int spi_mode = SPI_MODE_0;
	unsigned int spi_bpw = 8;

	ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	ioctl(fd, SPI_IOC_WR_MODE, &spi_mode);
	ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bpw);
	
	while(1)
	{
		for(int i=0; i<sizeof(hello); i++)
		{
			result = spiTxRx(hello[i]);
			usleep(10);
			printf("%c", result);
		}
	}

	close(fd);
}

int spiTxRx(unsigned char txDat)
{
	unsigned char rxDat;

	struct spi_ioc_transfer spi;

	memset(&spi, 0, sizeof(spi));

	spi.tx_buf = (unsigned long)&txDat;
	spi.rx_buf = (unsigned long)&rxDat;
	spi.len = 1;

	ioctl(fd, SPI_IOC_MESSAGE(1), &spi);
	
	return rxDat;
}
