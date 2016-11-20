#include <fcntl.h>          // open, O_WRONLY
#include <unistd.h>          // close, write
#include <stdio.h>          // perror, snprintf
#include <string.h>          // strlen


#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64


int gpio_unexport(unsigned int gpio)
{
    int         fd  = 0;
    int         len = 0;
    char        buf[MAX_BUF];


    fd  = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);

    if ( fd < 0 )
    {
        fprintf(stderr, "gpio/export");

        return (fd);
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);

    if ( write(fd, buf, len) == -1 )
    {
        fprintf(stderr, "gpio/export");
    }

    close(fd);

    return (0);
}