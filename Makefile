GCC_OPTIONS=-g -Wall -Wextra -Wno-format -std=gnu11 -lvorbisfile -lvorbis -lopenal -lm

COMMON_FILES=src/include/*.h

all: sine_test ogg_test

sine_test: sine_test.c $(COMMON_FILES)
	gcc sine_test.c $(GCC_OPTIONS) -o build/sine_test

ogg_test: ogg_test.c $(COMMON_FILES)
	gcc ogg_test.c $(GCC_OPTIONS) -o build/ogg_test
