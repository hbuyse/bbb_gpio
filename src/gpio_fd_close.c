#include <unistd.h>          // close


int gpio_fd_close(int fd)
{
    return (close(fd) );
}