GCC_OPTIONS=-g -Wall -Wextra -Wno-format -std=gnu11 -lvorbisfile -lvorbis -lopenal -lm

all: sine_test ogg_test

sine_test: sine_test.c
	gcc sine_test.c $(GCC_OPTIONS) -o build/sine_test

ogg_test: ogg_test.c
	gcc ogg_test.c $(GCC_OPTIONS) -o build/ogg_test
