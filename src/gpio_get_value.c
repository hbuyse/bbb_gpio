#include <fcntl.h>          // open, O_WRONLY
#include <unistd.h>          // close, write
#include <stdio.h>          // perror, snprintf


#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64


int gpio_get_value(unsigned int gpio,
                   unsigned int *value
                   )
{
    int         fd = 0;
    char        buf[MAX_BUF];
    char        ch;


    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_RDONLY);

    if ( fd < 0 )
    {
        fprintf(stderr, "gpio/get-value");

        return (fd);
    }

    if ( read(fd, &ch, 1) == -1 )
    {
        fprintf(stderr, "gpio/get-value");
    }
    else
    {
        if ( ch != '0' )
        {
            *value = 1;
        }
        else
        {
            *value = 0;
        }
    }

    close(fd);

    return (0);
}