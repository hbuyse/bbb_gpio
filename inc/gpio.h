#ifndef __GPIO_H__
#define __GPIO_H__


typedef enum {
    INPUT   = 0,
    OUTPUT  = 1
} direction_t;


typedef enum {
    LOW     = 0,
    HIGH    = 1
} value_t;


typedef enum {
    NONE    = 0,
    RISING  = 1,
    FALLING = 2,
    BOTH    = 3
} edge_t;


typedef struct bbb_gpio_s {
    unsigned char number;
    unsigned char exported;
    direction_t direction;
    value_t value;
    edge_t edge;
} bbb_gpio_t;


/****************************************************************
* bbb_gpio_export
****************************************************************/
unsigned int bbb_gpio_export(bbb_gpio_t *g);


/****************************************************************
* bbb_gpio_unexport
****************************************************************/
unsigned int bbb_gpio_unexport(bbb_gpio_t *g);


/****************************************************************
* bbb_gpio_set_dir
****************************************************************/
unsigned int bbb_gpio_set_direction(bbb_gpio_t *g);


/****************************************************************
* bbb_gpio_set_edge
****************************************************************/

unsigned int bbb_gpio_set_edge(bbb_gpio_t *g);


/****************************************************************
* bbb_gpio_set_value
****************************************************************/
unsigned int bbb_gpio_set_value(bbb_gpio_t *g);


/****************************************************************
* bbb_gpio_get_value
****************************************************************/
unsigned int bbb_gpio_get_value(bbb_gpio_t *g);


#endif          // __GPIO_H__