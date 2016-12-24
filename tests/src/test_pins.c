/**
 * @file: main.c
 * @author: hbuyse
 *
 * @brief Testing program for pins functions
 */

#include <pins.h>

#include "../minunit/minunit.h"

#define USR_NAME "USR0"
#define USR_KEY "USR0"
#define USR_PIN_NUMBER 53
#define GPIO_NAME "GPIO1_6"
#define GPIO_KEY "P8_3"
#define GPIO_PIN_NUMBER 38
#define PWM_NAME "EHRPWM2B"
#define PWM_KEY "P8_13"
#define PWM_PIN_NUMBER 23
#define AIN_NAME "AIN0"
#define AIN_KEY "P9_39"
#define AIN_PIN_NUMBER 0
#define VDD_NAME "VDD_ADC"
#define VDD_KEY "P9_32"
#define VDD_PIN_NUMBER 0
#define GND_NAME "DGND"
#define GND_KEY "P9_43"
#define GND_PIN_NUMBER 0
#define TOTO_NAME "TOTO"
#define TOTO_KEY "TOTO"
#define TOTO_PIN_NUMBER -1


MU_TEST(test_bbb_get_gpio_by_name)
{
    mu_assert_int_eq(bbb_get_gpio_by_name(USR_NAME), USR_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_name(GPIO_NAME), GPIO_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_name(PWM_NAME), PWM_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_name(AIN_NAME), AIN_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_name(VDD_NAME), VDD_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_name(GND_NAME), GND_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_name(TOTO_NAME), TOTO_PIN_NUMBER);
}


MU_TEST(test_bbb_get_gpio_by_key)
{
    mu_assert_int_eq(bbb_get_gpio_by_key(USR_KEY), USR_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_key(GPIO_KEY), GPIO_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_key(PWM_KEY), PWM_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_key(AIN_KEY), AIN_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_key(VDD_KEY), VDD_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_key(GND_KEY), GND_PIN_NUMBER);
    mu_assert_int_eq(bbb_get_gpio_by_key(TOTO_KEY), TOTO_PIN_NUMBER);
}


MU_TEST(test_bbb_is_pin_pwm)
{
    mu_assert_int_eq(bbb_is_pin_pwm(USR_PIN_NUMBER), 0);
    mu_assert_int_eq(bbb_is_pin_pwm(GPIO_PIN_NUMBER), 0);
    mu_assert_int_eq(bbb_is_pin_pwm(PWM_PIN_NUMBER), 1);
    mu_assert_int_eq(bbb_is_pin_pwm(AIN_PIN_NUMBER), 0);
    mu_assert_int_eq(bbb_is_pin_pwm(VDD_PIN_NUMBER), 0);
    mu_assert_int_eq(bbb_is_pin_pwm(GND_PIN_NUMBER), 0);
    mu_assert_int_eq(bbb_is_pin_pwm(TOTO_PIN_NUMBER), -1);
}


MU_TEST(test_bbb_is_pin_allocated_by_default)
{
    mu_assert_int_eq(bbb_is_pin_allocated_by_default(USR_PIN_NUMBER), 1);
    mu_assert_int_eq(bbb_is_pin_allocated_by_default(GPIO_PIN_NUMBER), 1);
    mu_assert_int_eq(bbb_is_pin_allocated_by_default(PWM_PIN_NUMBER), 0);
    mu_assert_int_eq(bbb_is_pin_allocated_by_default(AIN_PIN_NUMBER), -1);
    mu_assert_int_eq(bbb_is_pin_allocated_by_default(VDD_PIN_NUMBER), -1);
    mu_assert_int_eq(bbb_is_pin_allocated_by_default(GND_PIN_NUMBER), -1);
    mu_assert_int_eq(bbb_is_pin_allocated_by_default(TOTO_PIN_NUMBER), -2);
}


MU_TEST_SUITE(test_pins)
{
    fprintf(stdout, "\n\e[1m[test_bbb_get_gpio_by_name]\e[0m\t");
    MU_RUN_TEST(test_bbb_get_gpio_by_name);
    fprintf(stdout, "\n\e[1m[test_bbb_get_gpio_by_key]\e[0m\t");
    MU_RUN_TEST(test_bbb_get_gpio_by_key);
    fprintf(stdout, "\n\e[1m[test_bbb_is_pin_pwm]\e[0m\t");
    MU_RUN_TEST(test_bbb_is_pin_pwm);
    fprintf(stdout, "\n\e[1m[test_bbb_is_pin_allocated_by_default]\e[0m\t");
    MU_RUN_TEST(test_bbb_is_pin_allocated_by_default);
}


unsigned char main_pins(void)
{
    // Launch the test suites
    MU_RUN_SUITE(test_pins);


    // Print the report
    MU_REPORT();

    return ( (minunit_fail == 0) ? 0 : 1);
}