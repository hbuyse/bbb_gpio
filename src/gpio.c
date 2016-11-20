#include <fcntl.h>          // open, O_WRONLY
#include <unistd.h>          // close, write
#include <stdio.h>          // perror, snprintf
#include <string.h>          // strlen


#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64


int gpio_export(unsigned int gpio)
{
    int         fd  = 0;
    int         len = 0;
    char        buf[MAX_BUF];


    fd  = open(SYSFS_GPIO_DIR "/export", O_WRONLY);

    if ( fd < 0 )
    {
        fprintf(stderr, "gpio/export\n");

        return (fd);
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);

    if ( write(fd, buf, len) == -1 )
    {
        fprintf(stderr, "gpio/export\n");
    }

    close(fd);

    return (0);
}



int gpio_unexport(unsigned int gpio)
{
    int         fd  = 0;
    int         len = 0;
    char        buf[MAX_BUF];


    fd  = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);

    if ( fd < 0 )
    {
        fprintf(stderr, "gpio/export\n");

        return (fd);
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);

    if ( write(fd, buf, len) == -1 )
    {
        fprintf(stderr, "gpio/export\n");
    }

    close(fd);

    return (0);
}



int gpio_fd_open(unsigned int gpio)
{
    int         fd = 0;
    char        buf[MAX_BUF];


    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_RDONLY | O_NONBLOCK);

    if ( fd < 0 )
    {
        fprintf(stderr, "gpio/fd_open\n");
    }

    return (fd);
}



int gpio_fd_close(int fd)
{
    return (close(fd) );
}



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
        fprintf(stderr, "gpio/get-value\n");

        return (fd);
    }

    if ( read(fd, &ch, 1) == -1 )
    {
        fprintf(stderr, "gpio/get-value\n");
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



int gpio_set_dir(unsigned int   gpio,
                 unsigned int   out_flag
                 )
{
    int         fd  = 0;
    int         err = 0;
    char        buf[MAX_BUF];


    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);

    if ( fd < 0 )
    {
        fprintf(stderr, "gpio/direction\n");

        return (fd);
    }

    if ( out_flag )
    {
        err = write(fd, "in", 3);
    }
    else
    {
        err = write(fd, "out", 4);
    }

    if ( err == -1 )
    {
        fprintf(stderr, "gpio/direction\n");
    }

    close(fd);

    return (0);
}



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
        fprintf(stderr, "gpio/set-edge\n");

        return (fd);
    }

    if ( write(fd, edge, strlen(edge) + 1) == -1 )
    {
        fprintf(stderr, "gpio/set-edge\n");
    }

    close(fd);

    return (0);
}



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
        fprintf(stderr, "gpio/set-value\n");

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
        fprintf(stderr, "gpio/set-value\n");
    }

    close(fd);

    return (0);
}