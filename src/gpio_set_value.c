#include <fcntl.h>          // open, O_WRONLY
#include <unistd.h>          // close, write
#include <stdio.h>          // perror, snprintf
#include <string.h>          // strlen


#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64


int gpio_set_value(unsigned int gpio,
                   unsigned int value
                   )
{
    int         fd  = 0;
    int         err = 0;
    char        buf[MAX_BUF];


    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_WRONLY);

    if ( fd < 0 )
    {
        fprintf(stderr, "gpio/set-value");

        return (fd);
    }

    if ( value )
    {
        err = write(fd, "1", 2);
    }
    else
    {
        err = write(fd, "0", 2);
    }

    if ( err == -1 )
    {
        fprintf(stderr, "gpio/set-value");
    }

    close(fd);

    return (0);
}