#include <gpio.h>          // gpio_export, gpio_set_dir, gpio_set_value
#include <stdlib.h>          // atoi
#include <unistd.h>          // usleep
#include <stdio.h>          // printf


int main(int        argc,
         char const *argv[]
         )
{
    unsigned char       gpio    = 0;
    unsigned char       i       = 0;


    if ( argc < 2 )
    {
        printf("Usage: %s <gpio-pin>\n", argv[0]);
        printf("Waits for a change in the GPIO pin voltage level or input on stdin\n");
        exit(-1);
    }

    gpio = atoi(argv[1]);

    gpio_export(gpio);
    gpio_set_dir(gpio, 0);

    for ( i = 0; i < 5; ++i )
    {
        gpio_set_value(gpio, 1);
        usleep(1000000);
        gpio_set_value(gpio, 0);
        usleep(1000000);
    }

    gpio_unexport(gpio);

    return (0);
}