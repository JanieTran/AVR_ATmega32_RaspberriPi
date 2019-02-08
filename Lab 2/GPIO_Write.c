#include <stdio.h>
#include <string.h>
#include <unistd.h>

//================================================================
// CONSTANTS, VARIABLES AND FUNCTIONS PROTOTYPES
//================================================================

#define ONE_PERIOD 10000

int gpio = 4;
int dutyCycle = 80;
int delayTime = 500000;
FILE* fd;

void GPIO_Init(int pin);
int GPIO_Write(int pin, int value);
void GPIO_Unexport(int pin);
int calculatePWM(int dutyCycle);

//================================================================
// MAIN FUNCTION
//================================================================

int main(int argc, char** argv) {
    GPIO_Init();

    while (1) {
        // Write 1 to value
        GPIO_Write(gpio, 1);
        // usleep(delayTime);
        usleep(calculatePWM(dutyCycle));

        // Write 0 to value
        GPIO_Write(gpio, 0);
        // usleep(delayTime);
        usleep(ONE_PERIOD - calculatePWM(dutyCycle));
    }

    fclose(fd);

    GPIO_Unexport();
    
    return 0;
}

//================================================================
// FUNCTION BODY
//================================================================

void GPIO_Init(int pin) {
    char buf[100];

    // Export GPIO pin
    fd = fopen("/sys/class/gpio/export", "w");
    fprintf(fd, "%d", pin);
    fclose(fd);

    // Set direction
    sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
    fd = fopen(buf, "w");
    fprintf(fd, "out");
    fclose(fd);
}

int GPIO_Write(int pin, int value) {
    char buf[100];

    // Open value file of GPIO
    sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
    fd = fopen(buf, "w");

    // Write value to file
    fprintf(fd, itoa(value));
    fflush(fd);

    fclose(fd);
} 

void GPIO_Unexport(int pin) {
    // Unexport GPIO pin
    fd = fopen("/sys/class/gpio/unexport", "w");
    fprintf(fd, "%d", pin);
    fclose(fd);
}

int calculatePWM(int dutyCycle) {
    return ONE_PERIOD * dutyCycle / 100;
}

