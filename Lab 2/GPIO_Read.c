#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//================================================================
// VARIABLES AND FUNCTIONS PROTOTYPES
//================================================================

void GPIO_Init(int pin);
int GPIO_Read(int pin);
void GPIO_Unexport(int pin);

FILE* fd;
int gpio = 21;
int dutyCycle = 80;
int delayTime = 500000;
int result;

//================================================================
// MAIN FUNCTION
//================================================================

int main(int argc, char** argv) {
    GPIO_Init(gpio);

    while (1) {
        result = GPIO_Read(gpio);
        if (result == 1) {
            usleep(300000);
            printf("Button pushed \n");
        }
        usleep(500000);
    }
    GPIO_Unexport(gpio);

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
    fprintf(fd, "in");
    fclose(fd);
}

int GPIO_Read(int pin) {
    char buf[100];
    char value[1];

    // Open value file of GPIO
    sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
    fd = fopen(buf, "r");
    if (fd == -1) {
        printf("Fail to open GPIO for reading\n");
    }

    fscanf(fd, "%s", value);

    fclose(fd);
    
    return atoi(value);
} 

void GPIO_Unexport(int pin) {
    // Unexport GPIO pin
    fd = fopen("/sys/class/gpio/unexport", "w");
    fprintf(fd, "%d", pin);
    fclose(fd);
}