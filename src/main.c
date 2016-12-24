#include <stdlib.h>          // atoi
#include <unistd.h>          // usleep
#include <stdio.h>          // printf

#include <gpio.h>          // bbb_gpio_export, bbb_gpio_set_dir, bbb_gpio_set_value
#include <pins.h>

int main(int        argc __attribute__( (unused) ),
         char const *argv[] __attribute__( (unused) )
         )
{
    #if 0
    unsigned char       gpio    = 0;
    unsigned char       i       = 0;

    if ( argc < 2 )
    {
        printf("Usage: %s <gpio-pin>\n", argv[0]);
        printf("Waits for a change in the GPIO pin voltage level or input on stdin\n");
        exit(-1);
    }

    gpio = atoi(argv[1]);

    bbb_gpio_export(gpio);
    bbb_gpio_set_direction(gpio, 0);

    for ( i = 0; i < 5; ++i )
    {
        bbb_gpio_set_value(gpio, 1);
        usleep(1000000);
        bbb_gpio_set_value(gpio, 0);
        usleep(1000000);
    }
    bbb_gpio_unexport(gpio);
    #endif

    printf("EHRPWM2B: %d\n", bbb_get_gpio_by_name("EHRPWM2B") );
    printf("P8_13   : %d\n", bbb_get_gpio_by_key("P8_13") );

    return (0);
}