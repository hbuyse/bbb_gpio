lib_LTLIBRARIES = libbbbgpio.la
libbbbgpio_la_SOURCES = pins.c gpio.c
libbbbgpio_la_CFLAGS = -W -Wall -Wextra -Wno-unused-function -fmessage-length=0 -D_REENTRANT
libbbbgpio_la_LDFLAGS = -version-info 0:1:0


bin_PROGRAMS =  bbb_gpio.out
bbb_gpio_out_SOURCES = main.c
bbb_gpio_out_LDADD = libbbbgpio.la
