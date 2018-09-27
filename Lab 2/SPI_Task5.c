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

// GPIO
//---------------------------------

FILE* gpioFd;
int gpio = 21;
int gpioResult;

int GPIO_Init(int pin);
int GPIO_Read(int pin);
void GPIO_Unexport(int pin);

// SPI
//---------------------------------

int spiFd;
int startSPI;
uint8_t spiResult;
uint8_t data[] = {0xA5, 0xB6};
uint8_t mode;
uint8_t bits = 8;
uint8_t index = 0;
uint32_t speed = 500000;

void SPI_Init(void);
void SPI_Transfer(int fd, uint8_t txDat);

//================================================================
// MAIN FUNCTION
//================================================================

int main(int argc, char *argv[])
{
	// SPI Initialisation

	startSPI = 0;

	spiFd = open("/dev/spidev0.0", O_RDWR);
	if (spiFd < 0)
		printf("Can't open device\n");

	SPI_Init();

	// GPIO Initialisation

	GPIO_Init(gpio);

	while (1) {
		gpioResult = GPIO_Read(gpio);

		if (gpioResult == 1) {
			usleep(300000);
            printf("Button pushed \n");
			startSPI = !startSPI;
			SPI_Transfer(spiFd, 0x19);
		}

		if (startSPI) {
			SPI_Transfer(spiFd, 0x00);
		}

		usleep(200000);
	}
	
	close(spiFd);
	GPIO_Unexport(gpio);
}

//================================================================
// FUNCTION BODY
//================================================================

// SPI
//---------------------------------

void SPI_Init(void) {
	int ret;

	// SPI mode
	ret = ioctl(spiFd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		printf("Can't set spi mode");

	ret = ioctl(spiFd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		printf("Can't get spi mode");

	// Bit per word
	ret = ioctl(spiFd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		printf("Can't set bits per word");

	ret = ioctl(spiFd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		printf("Can't get bits per word");

	// Max speed
	ret = ioctl(spiFd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		printf("Can't set max speed hz");

	ret = ioctl(spiFd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		printf("Can't get max speed hz");

	printf("SPI mode: %d\n", mode);
	printf("Bits per word: %d\n", bits);
	printf("Max speed: %d Hz (%d KHz)\n", speed, speed/1000);
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

	int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
		printf("Can't send SPI message\n");

	printf("Value from POT: %d\n", rx[0]);
}

// GPIO
//---------------------------------

int GPIO_Init(int pin) {
    char buf[100];

    // Export GPIO pin
    gpioFd = fopen("/sys/class/gpio/export", "w");
    fprintf(gpioFd, "%d", pin);
    fclose(gpioFd);

    // Set direction
    sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
    gpioFd = fopen(buf, "w");
    fprintf(gpioFd, "in");
    fclose(gpioFd);
}

int GPIO_Read(int pin) {
    char buf[100];
    char value[1];

    // Open value file of GPIO
    sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
    gpioFd = fopen(buf, "r");
    if (gpioFd == -1) {
        printf("Fail to open GPIO for reading\n");
    }

    fscanf(gpioFd, "%s", value);

    fclose(gpioFd);
    
    return atoi(value);
} 

void GPIO_Unexport(int pin) {
    // Unexport GPIO pin
    gpioFd = fopen("/sys/class/gpio/unexport", "w");
    fprintf(gpioFd, "%d", pin);
    fclose(gpioFd);
}