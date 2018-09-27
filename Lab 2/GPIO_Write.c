#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ONE_PERIOD 10000

int calculatePWM(int dutyCycle);

int main(int argc, char** argv) {
    int gpio = 4;
    int dutyCycle = 80;
    int delayTime = 500000;
    char buf[100];

    FILE* fd = fopen("/sys/class/gpio/export", "w");
    fprintf(fd, "%d", gpio);
    fclose(fd);

    sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
    fd = fopen(buf, "w");
    fprintf(fd, "out");
    fclose(fd);

    sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
    fd = fopen(buf, "w");

    while (1) {
        fprintf(fd, "1");
        fflush(fd);
        // usleep(50000);
        usleep(calculatePWM(dutyCycle));
        fprintf(fd, "0");
        fflush(fd);
        // usleep(50000);
        usleep(ONE_PERIOD - calculatePWM(dutyCycle));
    }

    fclose(fd);
    
    return 0;
}

int calculatePWM(int dutyCycle) {
    return ONE_PERIOD * dutyCycle / 100;
}