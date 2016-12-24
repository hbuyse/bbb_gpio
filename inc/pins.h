#ifndef __PINS_H__
#define __PINS_H__


/**
 * @brief Describe a pin
 * @details Gives a description of a pin:
 *          * by its name,
 *          * by its key,
 *          * by its GPIO number,
 *          * if it is a PWM pin (if yes, gives the PWM mux mode)
 *          * if it is a analog input (if yes, gives the AIN number)
 *          * tells if allocated by default
 */
typedef struct bbb_pin_s {
    const char *name;          // Name of the pin (GPIOX_X, EHRPWMXX, ...)
    const char *key;          // Key on the board (PX_X)
    unsigned int gpio;          // Unique GPIO number
    int pwm_mux_mode;          // Mux mode of the pin that enables pwm
    int ain;          // Analog input number
    int is_allocated_by_default;          // Allocation by default ? (0 -> no, 1 -> yes, -1 -> impossible to change)
} bbb_pin_t;



/**
 * @brief Get the GPIO number from its name
 *
 * @param name GPIO's name
 * @return On success: the GPIO number.
 *         On error: -1.
 */
int bbb_get_gpio_by_name(const char *name);


/**
 * @brief Get the GPIO number from its key
 *
 * @param name GPIO's key
 * @return On success: the GPIO number.
 *         On error: -1.
 */
int bbb_get_gpio_by_key(const char *key);


/**
 * @brief Check if the pin is an analog input
 *
 * @param gpio The GPIO's number
 * @return True: 1, false: 0.
 */
unsigned int bbb_is_pin_pwm(const unsigned int gpio);


/**
 * @brief Check if the pin is an analog input
 *
 * @param gpio The GPIO's number
 * @return True: 1, false: 0, error: -1.
 */
int bbb_is_pin_allocated_by_default(const unsigned int gpio);




#endif          // __PINS_H__