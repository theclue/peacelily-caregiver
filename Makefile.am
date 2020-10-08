ACLOCAL_AMFLAGS = -I m4 --install

lib_LTLIBRARIES =

if BUILD_WIRINGPI_STUB
    lib_LTLIBRARIES += libwiringPiStub.la

    # Stubbed wiringPi headers to be installed
    include_HEADERS = \
    src/wiringPi-stub/wiringPi.h
endif

LIBTOOL_DEPS = @LIBTOOL_DEPS@

# libwiringPiStub.{so,a}
libwiringPiStub_la_LDFLAGS = -rpath '$(libdir)' -version-info $(WIRINGPI_STUB_SOVERSION)
libwiringPiStub_la_SOURCES = src/wiringPi-stub/wiringPi.c

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/wiringPi-stub/libwiringPiStub.pc
