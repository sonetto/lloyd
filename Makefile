GCC_OPTIONS=-g -Wall -Wextra -Wno-format -std=gnu11 -lvorbisfile -lvorbis -lopenal -lm

COMMON_HEADERS=src/include/*.h
COMMON_SOURCES=src/*.c
COMMON_FILES=$(COMMON_HEADERS) $(COMMON_SOURCES)

all: sine_test ogg_test lloyd_basic_test lloyd_fade_test lloyd_switch_test

sine_test: sine_test.c $(COMMON_FILES)
	gcc sine_test.c $(GCC_OPTIONS) -o build/sine_test

ogg_test: ogg_test.c $(COMMON_FILES)
	gcc ogg_test.c $(COMMON_SOURCES) $(GCC_OPTIONS) -o build/ogg_test

lloyd_basic_test: lloyd_basic_test.c $(COMMON_FILES)
	gcc lloyd_basic_test.c $(COMMON_SOURCES) $(GCC_OPTIONS) -o build/lloyd_basic_test

lloyd_fade_test: lloyd_fade_test.c $(COMMON_FILES)
	gcc lloyd_fade_test.c $(COMMON_SOURCES) $(GCC_OPTIONS) -o build/lloyd_fade_test

lloyd_switch_test: lloyd_switch_test.c $(COMMON_FILES)
	gcc lloyd_switch_test.c $(COMMON_SOURCES) $(GCC_OPTIONS) -o build/lloyd_switch_test
