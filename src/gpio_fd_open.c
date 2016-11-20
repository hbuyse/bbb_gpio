#include <fcntl.h>          // open, O_RDONLY, O_NONBLOCK
#include <stdio.h>          // perror, snprintf


#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64


int gpio_fd_open(unsigned int gpio)
{
    int         fd = 0;
    char        buf[MAX_BUF];


    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_RDONLY | O_NONBLOCK);

    if ( fd < 0 )
    {
        fprintf(stderr, "gpio/fd_open");
    }

    return (fd);
}