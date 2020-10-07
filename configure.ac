dnl This source code is licensed under the MIT license found in the
dnl LICENSE file in the root directory of this source tree.

dnl autoconf script for Take care of me

AC_PREREQ([2.69])

AC_INIT([Take Care of Me], [0.0.1], [gabriele@gabrielebaldassarre.com], , [https://github.com/theclue/peacelily-caregiver])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

## ------------------ ##
## Generic variables. ##
## ------------------ ##
WIRINGPI_STUB_SOVERSION=1:0:0

AC_SUBST([LIBTOOL_DEPS])
AC_SUBST([WIRINGPI_STUB_SOVERSION])

TEMP_DIR="${TMPDIR:-/tmp}"

## ------------------------ ##
## Automake initialisation. ##
## ------------------------ ##
AM_INIT_AUTOMAKE([subdir-objects dist-xz -Wall -Werror])
AM_SILENT_RULES([yes])

AM_PROG_AR


## ----------------------- ##
## Libtool initialisation. ##
## ----------------------- ##
LT_INIT([disable-static shared])
LT_LANG([C++])

## ------------------------- ##
## Autobuild initialisation. ##
## ------------------------- ##

# You can set autobuild_mode at configure time to specify a "unique"
# string for this build.
: ${autobuild_mode=default}
AB_VERSION='AC_PACKAGE_VERSION'
AB_INIT([$autobuild_mode])

## -------------------------- ##
## C Compiler initialization. ##
## -------------------------- ##
AC_PROG_CC

AC_CONFIG_SRCDIR([src/wiringPi-stub/wiringPi.c])
AC_CONFIG_HEADERS([config.h])

# Checks for typedefs, structures, and compiler characteristics.
# FIXME: leave only the really needed ones
AC_C_INLINE
AC_TYPE_INT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset err errx])

# Checks for libraries.
AC_CHECK_LIB([m], [round])
AC_CHECK_LIB([pthread], [pthread_create])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h err.h])

AC_DEFINE_UNQUOTED([RELEASE], ["$PACKAGE_VERSION"], [convenience define used for release number in various point of the package])

## ----------------------------- ##
## R interpreter initialization. ##
## ----------------------------- ##
AC_CHECK_TOOL([RSCRIPT], [Rscript], [no])
AC_ASSERT_PROG([Rscript], [$RSCRIPT])

## ------------------------------- ##
## Host and Target initialization. ##
## ------------------------------- ##

# see https://stackoverflow.com/questions/714100/os-detecting-makefile
# but we do this in the configure for homogeneity

AC_CHECK_TOOL([GETCONF], [getconf], [no])

AC_CANONICAL_HOST
AS_CASE([$host_os],
        [linux*],
        [
           BUILD_PLATFORM=Linux
        ],
        [darwin*],
        [
           BUILD_PLATFORM=Darwin
           AS_IF([test x"$GETCONF" != x"no"], [TEMP_DIR=`"$GETCONF" DARWIN_USER_TEMP_DIR`])

        ],
        [cygwin*|mingw*],
        [
            BUILD_PLATFORM=Windows
        ],
        AC_MSG_ERROR(["OS $host_os is not yet supported"]))

AC_SUBST([BUILD_PLATFORM])
AC_SUBST([TEMP_DIR])

dnl This part is needed to ensure a proper build process under OSX

AC_CHECK_TOOL([XCODE_SELECT], [xcode-select], [no])
AS_IF([test "x$XCODE_SELECT" != "xno"], [XCODE_SELECT_OUT=`xcode-select -p`])

AC_ARG_VAR([XCODE_BASE], [Install location of xcode])
AS_IF(
  [test "x$XCODE_BASE" != "x"],
        [AC_CHECK_FILE($XCODE_BASE,[HAS_OBJC=yes],[HAS_OBJC=no])],
  [test "x$XCODE_SELECT" != "xno"],
        [XCODE_BASE=$XCODE_SELECT_OUT HAS_OBJC=yes],
  [HAS_OBJC=no])

AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AC_PROG_SED

dnl This is for a better OSX build experience
AC_CHECK_TOOL([BREW], [brew], [no])

dnl Check the number of available core here for
dnl faster building process
AC_MSG_CHECKING([the number of cpus the build host has])
AS_IF(
    [test "$GETCONF" != "no"],
    AS_IF(
        [test $("$GETCONF" _NPROCESSORS_ONLN)],
        [
            NCPU=$("$GETCONF" _NPROCESSORS_ONLN)
            AC_MSG_RESULT([$NCPU])
        ]),
    [
        NCPU=1
        AC_MSG_RESULT([failed, defaulting to 1])
    ])
AC_SUBST([NCPU])

AC_ARG_ENABLE(wiringpi-stub,
  AS_HELP_STRING([--disable-wiringpi-stub],
    [do not build the WiringPi Stub shared alibrary (default is to build it)]),
  ,
  enable_wiringpi_stub=yes)

## ---------------------- ##
## Automake conditionals. ##
## ---------------------- ##
AM_CONDITIONAL([BUILD_WIRINGPI_STUB], [test x"$enable_wiringpi-stub" = x"yes"])
AM_CONDITIONAL([WINDOWS_BUILD], [test x"$BUILD_PLATFORM" = x"Windows"])

AC_CONFIG_FILES([Makefile src/wiringPi-stub/libwiringPiStub.pc])

AC_OUTPUT
