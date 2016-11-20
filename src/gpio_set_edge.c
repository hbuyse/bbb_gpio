#include <fcntl.h>          // open, O_WRONLY
#include <unistd.h>          // close, write
#include <stdio.h>          // perror, snprintf
#include <string.h>          // strlen


#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64


int gpio_set_edge(unsigned int  gpio,
                  char          *edge
                  )
{
    int         fd = 0;
    char        buf[MAX_BUF];


    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

    fd = open(buf, O_WRONLY);

    if ( fd < 0 )
    {
        fprintf(stderr, "gpio/set-edge");

        return (fd);
    }

    if ( write(fd, edge, strlen(edge) + 1) == -1 )
    {
        fprintf(stderr, "gpio/set-edge");
    }

    close(fd);

    return (0);
}