# Prelude
AC_PREREQ(2.52)

AC_INIT(bbb_gpio, 1.0.0, henri.buyse@gmail.com, bbb_gpio, https://github.com/hbuyse/bbb_gpio)
AM_INIT_AUTOMAKE(foreign)

AC_PROG_MAKE_SET

# foreign ignores some GNU Coding Standards like
# * Makefile.am: installing './INSTALL'
# * Makefile.am: error: required file './NEWS' not found
# * Makefile.am: error: required file './README' not found
# * Makefile.am: error: required file './AUTHORS' not found
# * Makefile.am: error: required file './ChangeLog' not found

# enable silent build by default
AM_SILENT_RULES(yes)

AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CC

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([errno.h])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([unistd.h])
AC_CONFIG_HEADERS(config.h)

# Checks for libraries.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T
AC_CHECK_TYPE(ssize_t, int)

# Checks for library functions.
AC_FUNC_VPRINTF
AC_FUNC_MEMCMP
AC_CHECK_FUNCS([open])
AC_CHECK_FUNCS([write])
AC_CHECK_FUNCS([fprintf])
AC_CHECK_FUNCS([snprintf])
AC_CHECK_FUNCS([strerror])
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([usleep])
AC_CHECK_FUNCS([printf])
AC_CHECK_FUNCS([strcmp])

LT_INIT

# AX_COMPILE_CHECK_SIZEOF(int)
# AX_COMPILE_CHECK_SIZEOF(long)
# AX_COMPILE_CHECK_SIZEOF(size_t, [#include <stdint.h>])

AC_CONFIG_FILES(Makefile src/Makefile)

# Output files.
AC_OUTPUT