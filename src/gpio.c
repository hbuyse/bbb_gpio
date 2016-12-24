#include <fcntl.h>          // open, O_WRONLY
#include <unistd.h>          // close, write
#include <stdio.h>          // perror, snprintf
#include <string.h>          // strlen, strerror
#include <errno.h>          // errno

#include <gpio.h>           // bbb_gpio_t


#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define SYSFS_GPIO_EXPORT SYSFS_GPIO_DIR "/export"
#define SYSFS_GPIO_UNEXPORT SYSFS_GPIO_DIR "/unexport"
#define SYSFS_GPIO_VALUE SYSFS_GPIO_DIR "/gpio%d/value"
#define SYSFS_GPIO_DIRECTION SYSFS_GPIO_DIR "/gpio%d/direction"
#define SYSFS_GPIO_EDGE SYSFS_GPIO_DIR "/gpio%d/edge"

#define MAX_BUF 64


unsigned int bbb_gpio_export(bbb_gpio_t *g)
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
    len     = snprintf(buf, sizeof(buf), "%d", g->number);
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



unsigned int bbb_gpio_unexport(bbb_gpio_t *g)
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
    len     = snprintf(buf, sizeof(buf), "%d", g->number);
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



unsigned int bbb_gpio_set_direction(bbb_gpio_t *g)
{
    unsigned int        ret = 0;
    int                 fd  = 0;
    int                 err = 0;
    char                buf[MAX_BUF];


    // Create the path to the file that handle the GPIO's direction
    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIRECTION, g->number);


    // Open the file that handles the GPIO's direction
    fd = open(buf, O_WRONLY);

    if ( fd == -1 )
    {
        ret = 1;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );

        return (ret);
    }

    switch ( g->direction )
    {
        case INPUT:
            err = write(fd, "in", 3);
            break;

        case OUTPUT:
            err = write(fd, "out", 4);
            break;

        default:
            ret = 3;
            fprintf(stderr, "Unknown direction (direction: %d)", g->direction);
    }

    if ( err == -1 )
    {
        ret = 4;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }


    // Close the file that handles the unexportation
    if ( close(fd) )
    {
        ret = 2;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }

    return (0);
}



unsigned int bbb_gpio_set_edge(bbb_gpio_t *g)
{
    unsigned int        ret = 0;
    int                 fd  = 0;
    int                 err = 0;
    char                buf[MAX_BUF];


    // Create the path to the file that handle the GPIO's edge
    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIRECTION, g->number);


    // Open the file that handles the GPIO's edge
    fd = open(buf, O_WRONLY);

    if ( fd == -1 )
    {
        ret = 1;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );

        return (ret);
    }

    switch ( g->edge )
    {
        case NONE:
            err = write(fd, "none", 4);
            break;

        case RISING:
            err = write(fd, "rising", 6);
            break;

        case FALLING:
            err = write(fd, "falling", 7);
            break;

        case BOTH:
            err = write(fd, "both", 4);
            break;

        default:
            ret = 3;
            fprintf(stderr, "Unknown edge (edge: %d)", g->edge);
    }

    if ( err == -1 )
    {
        ret = 4;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }


    // Close the file that handles the unexportation
    if ( close(fd) )
    {
        ret = 2;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }

    return (0);
}



unsigned int bbb_gpio_set_value(bbb_gpio_t *g)
{
    unsigned int        ret = 0;
    int                 fd  = 0;
    int                 err = 0;
    char                buf[MAX_BUF];


    // Create the path to the file that handle the GPIO's value
    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIRECTION, g->number);


    // Open the file that handles the GPIO's value
    fd = open(buf, O_WRONLY);

    if ( fd == -1 )
    {
        ret = 1;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );

        return (ret);
    }

    switch ( g->value )
    {
        case LOW:
            err = write(fd, "0", 1);
            break;

        case HIGH:
            err = write(fd, "1", 1);
            break;

        default:
            ret = 3;
            fprintf(stderr, "Unknown value (value: %d)", g->value);
    }

    if ( err == -1 )
    {
        ret = 4;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }


    // Close the file that handles the unexportation
    if ( close(fd) )
    {
        ret = 2;
        fprintf(stderr, "[%s] %s\n", __func__, strerror(errno) );
    }

    return (0);
}



unsigned int bbb_gpio_get_value(bbb_gpio_t *g)
{
    unsigned int        ret         = 0;
    int                 fd          = 0;
    char                buf[MAX_BUF];
    char                ch;
    ssize_t             bytes_read  = 0;


    // Create the path to the file that handle the GPIO's value
    snprintf(buf, sizeof(buf), SYSFS_GPIO_VALUE, g->number);


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
            g->value    = 0;
            break;

        case '1':
            g->value    = 1;
            break;

        default:
            ret         = 4;
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