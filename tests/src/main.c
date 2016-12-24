/**
 * @file: main.c
 * @author: hbuyse
 *
 * @brief Testing program
 */
#include <stdio.h>          // fprintf

#include <test_pins.h>


int main(void)
{
    unsigned char     res = 1;


    fprintf(stdout, "\e[1m############################################################\e[0m\n");
    fprintf(stdout, "\e[1m#                         PINS.OUT                         #\e[0m\n");
    fprintf(stdout, "\e[1m############################################################\e[0m\n");
    res |= main_pins();


    return (res);
}