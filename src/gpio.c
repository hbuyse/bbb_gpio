#include <fcntl.h>          // open, O_WRONLY
#include <unistd.h>          // close, write
#include <stdio.h>          // perror, snprintf
#include <string.h>          // strlen, strerror
#include <errno.h>          // errno

#include <gpio.h>              // SYSFS_GPIO_DIR, SYSFS_GPIO_EXPORT, SYSFS_GPIO_UNEXPORT, SYSFS_GPIO_VALUE,
                               // SYSFS_GPIO_DIRECTION, SYSFS_GPIO_EDGE


#define MAX_BUF 64


unsigned int bbb_gpio_export(unsigned int gpio)
{
    unsigned int        ret     = 0;
    int                 fd      = 0;
    size_t              len     = 0;
    char                buf[MAX_BUF];
    ssize_t             written = 0;


    // Open the file that handles the exportation
    fd = open(SYSFS_GPIO_EXPORT, O_WRONLY);

    if ( fd == -1 )
    {
        ret = 1;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );

        return (ret);
    }


    // Write the GPIO's number in that file
    len     = snprintf(buf, sizeof(buf), "%d", gpio);
    written = write(fd, buf, len);

    if ( written == -1 )
    {
        ret = 3;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }
    else if ( ( (size_t) written) != len )
    {
        ret = 4;
        fprintf(stderr,
                "[%s] Only %ld bytes were written in %s (%ld on %lu bytes).\n",
                __func__,
                written,
                SYSFS_GPIO_DIR "/export",
                written,
                len);
    }


    // Close the file that handles the exportation
    if ( close(fd) )
    {
        ret = 2;
        fprintf(stderr,
                "[%s] Only %ld bytes were written in %s (%ld on %lu bytes).\n",
                __func__,
                written,
                SYSFS_GPIO_DIR "/export",
                written,
                len);
    }

    return (ret);
}



unsigned int bbb_gpio_unexport(unsigned int gpio)
{
    unsigned int        ret     = 0;
    int                 fd      = 0;
    size_t              len     = 0;
    char                buf[MAX_BUF];
    ssize_t             written = 0;


    // Open the file that handles the unexportation
    fd = open(SYSFS_GPIO_UNEXPORT, O_WRONLY);

    if ( fd == -1 )
    {
        ret = 1;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );

        return (ret);
    }


    // Write the GPIO's number in that file
    len     = snprintf(buf, sizeof(buf), "%d", gpio);
    written = write(fd, buf, len);

    if ( written == -1 )
    {
        ret = 2;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }
    else if ( ( (size_t) written) != len )
    {
        ret = 3;
        fprintf(stderr,
                "[%s] Only %ld bytes were written in %s (%ld on %lu bytes).\n",
                __func__,
                written,
                SYSFS_GPIO_DIR "/unexport",
                written,
                len);
    }


    // Close the file that handles the unexportation
    if ( close(fd) )
    {
        ret = 4;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }

    return (ret);
}



unsigned int bbb_gpio_fd_open(unsigned int  gpio,
                              int           *fd
                              )
{
    unsigned int        ret = 0;
    char                buf[MAX_BUF];


    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    *fd = open(buf, O_RDONLY | O_NONBLOCK);

    if ( *fd < 0 )
    {
        ret = 1;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }

    return (ret);
}



unsigned int bbb_gpio_fd_close(int *fd)
{
    unsigned int     ret = 0;


    // Close the given file descriptor
    if ( close(*fd) )
    {
        ret = 1;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }

    return (ret);
}



unsigned int bbb_gpio_get_value(unsigned int    gpio,
                                unsigned int    *value
                                )
{
    unsigned int        ret         = 0;
    int                 fd          = 0;
    char                buf[MAX_BUF];
    char                ch;
    ssize_t             bytes_read  = 0;


    // Create the path to the file that handle the GPIO's value
    snprintf(buf, sizeof(buf), SYSFS_GPIO_VALUE, gpio);


    // Open the file that handles the GPIO's value
    fd = open(buf, O_WRONLY);

    if ( fd == -1 )
    {
        ret = 1;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );

        return (ret);
    }


    // Read one character in the file (it should be either 0 or 1)
    bytes_read = read(fd, &ch, 1);

    switch ( bytes_read )
    {
        case -1:
            fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
            break;

        case 0:
            fprintf(stderr, "[%s] %s is an empty file.\n", __func__, buf);
            break;

        case 1:
            break;

        default:
            ret = 3;
            fprintf(stderr, "[%s] %s had a unexpected error\n", __func__, buf);
    }


    // Check if the character is either 1 or 0
    switch ( ch )
    {
        case '0':
            *value  = 0;
            break;

        case '1':
            *value  = 1;
            break;

        default:
            ret     = 4;
            fprintf(stderr, "[%s] Value not supported: %c\n", __func__, ch);
    }


    // Close the file that handles the GPIO's value
    if ( close(fd) )
    {
        ret = 2;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }

    return (ret);
}



unsigned int bbb_gpio_set_direction(unsigned int    gpio,
                                    unsigned int    out_flag
                                    )
{
    unsigned int        ret = 0;
    int                 fd  = 0;
    int                 err = 0;
    char                buf[MAX_BUF];


    // Create the path to the file that handle the GPIO's direction
    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIRECTION, gpio);


    // Open the file that handles the GPIO's direction
    fd = open(buf, O_WRONLY);

    if ( fd == -1 )
    {
        ret = 1;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );

        return (ret);
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



unsigned int bbb_gpio_set_edge(unsigned int gpio,
                               char         *edge
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



unsigned int bbb_gpio_set_value(unsigned int    gpio,
                                unsigned int    value
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