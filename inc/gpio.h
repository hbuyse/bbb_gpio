#ifndef __GPIO_H__
#define __GPIO_H__

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define SYSFS_GPIO_EXPORT SYSFS_GPIO_DIR "/export"
#define SYSFS_GPIO_UNEXPORT SYSFS_GPIO_DIR "/unexport"
#define SYSFS_GPIO_VALUE SYSFS_GPIO_DIR "/gpio%d/value"
#define SYSFS_GPIO_DIRECTION SYSFS_GPIO_DIR "/gpio%d/direction"
#define SYSFS_GPIO_EDGE SYSFS_GPIO_DIR "/gpio%d/edge"


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
    direction_t direction;
    value_t value;
    edge_t edge;
} bbb_gpio_t;


/****************************************************************
* bbb_gpio_export
****************************************************************/
unsigned int bbb_gpio_export(unsigned int gpio);


/****************************************************************
* bbb_gpio_unexport
****************************************************************/
unsigned int bbb_gpio_unexport(unsigned int gpio);


/****************************************************************
* bbb_gpio_set_dir
****************************************************************/
unsigned int bbb_gpio_set_direction(unsigned int gpio, unsigned int out_flag);


/****************************************************************
* bbb_gpio_set_value
****************************************************************/
unsigned int bbb_gpio_set_value(unsigned int gpio, unsigned int value);


/****************************************************************
* bbb_gpio_get_value
****************************************************************/
unsigned int bbb_gpio_get_value(unsigned int gpio, unsigned int *value);


/****************************************************************
* bbb_gpio_set_edge
****************************************************************/

unsigned int bbb_gpio_set_edge(unsigned int gpio, char *edge);


/****************************************************************
* bbb_gpio_fd_open
****************************************************************/
unsigned int bbb_gpio_fd_open(unsigned int gpio, int *fd);


/****************************************************************
* bbb_gpio_fd_close
****************************************************************/
unsigned int bbb_gpio_fd_close(int *fd);


#endif          // __GPIO_H__