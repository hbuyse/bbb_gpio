#include <string.h>          // memset
#include <stdlib.h>          // atoi
#include <unistd.h>          // usleep
#include <stdio.h>          // printf

#include <gpio.h>          // bbb_gpio_export, bbb_gpio_set_dir, bbb_gpio_set_value
#include <pins.h>

int main(int        argc __attribute__( (unused) ),
         char const *argv[] __attribute__( (unused) )
         )
{
    bbb_gpio_t          *gpio   = NULL;
    unsigned char       i       = 0;


    memset(gpio, 0, sizeof(bbb_gpio_t) );

    if ( argc < 2 )
    {
        printf("Usage: %s <gpio-key>\n", argv[0]);
        printf("    Example of gpio-key: P8_3,...\n");
        printf("    Waits for a change in the GPIO pin voltage level or input on stdin\n");
        exit(-1);
    }

    gpio->number    = bbb_get_gpio_by_key(argv[1]);

    gpio->direction = OUTPUT;
    gpio->value     = LOW;
    gpio->edge      = NONE;

    bbb_gpio_export(gpio);
    bbb_gpio_set_direction(gpio);

    for ( i = 0; i < 5; ++i )
    {
        gpio->value = ( (gpio->value) ? LOW : HIGH);
        bbb_gpio_set_value(gpio);
        usleep(1000000);
    }

    bbb_gpio_unexport(gpio);

    return (0);
}