GCC_OPTIONS=-g -Wall -Wextra -Wno-format -std=gnu11 -lvorbisfile -lvorbis -lopenal -lm

COMMON_HEADERS=src/include/*.h
COMMON_SOURCES=src/*.c
COMMON_FILES=$(COMMON_HEADERS) $(COMMON_SOURCES)

all: build/sine_test build/ogg_test build/lloyd_basic_test build/lloyd_fade_test build/lloyd_switch_test build/lloyd_slave_test build/lloyd_slave_test_cli.sh

clean:
	rm -rf build/*

build/sine_test: sine_test.c $(COMMON_FILES)
	gcc sine_test.c $(GCC_OPTIONS) -o build/sine_test

build/ogg_test: ogg_test.c $(COMMON_FILES)
	gcc ogg_test.c $(COMMON_SOURCES) $(GCC_OPTIONS) -o build/ogg_test

build/lloyd_basic_test: lloyd_basic_test.c $(COMMON_FILES)
	gcc lloyd_basic_test.c $(COMMON_SOURCES) $(GCC_OPTIONS) -o build/lloyd_basic_test

build/lloyd_fade_test: lloyd_fade_test.c $(COMMON_FILES)
	gcc lloyd_fade_test.c $(COMMON_SOURCES) $(GCC_OPTIONS) -o build/lloyd_fade_test

build/lloyd_switch_test: lloyd_switch_test.c $(COMMON_FILES)
	gcc lloyd_switch_test.c $(COMMON_SOURCES) $(GCC_OPTIONS) -o build/lloyd_switch_test

build/libslave/libslave.h:
	mkdir -p build/libslave
	libslavegen -h >build/libslave/libslave.h

build/libslave/libslave.c: lloyd_slave_test.json build/libslave/libslave.h
	mkdir -p build/libslave
	libslavegen lloyd_slave_test.json >build/libslave/libslave.c

build/lloyd_slave_test: build/libslave/libslave.c lloyd_slave_test.c $(COMMON_FILES)
	gcc lloyd_slave_test.c build/libslave/libslave.c $(COMMON_SOURCES) $(GCC_OPTIONS) -o build/lloyd_slave_test

build/lloyd_slave_test_cli.sh: lloyd_slave_test.json build/lloyd_slave_test
	libslavegen -i lloyd_slave_test.json >build/lloyd_slave_test_cli.sh
	chmod a+x build/lloyd_slave_test_cli.sh
